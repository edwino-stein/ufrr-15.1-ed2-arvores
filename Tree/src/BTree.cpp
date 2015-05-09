/*
	Edwino Stein - 1201324411
*/

/* *************************************************************** */
/* ********************** Implementação BTree ******************** */
/* *************************************************************** */

#include "../header/BTree.hpp"
using namespace tree;

/* ******************* CONSTRUTORES E DESTRUTORES ******************* */

BTree::BTree(unsigned int order) : order(order), maxKeys(2 * order), maxBranches(2 * order + 1){
	//Intancia a raiz vazia
	this->root = new BTreePage();
}

BTree::BTree(unsigned int order, int value): BTree(order){
	//Inicializa a raiz
	this->insert(value);
}

BTree::~BTree(){

	//Remove todos os filhos
	this->clear();

	//Libera raiz
	delete this->root;
}

/* ******************* OPERAÇÕES ******************* */

/* Inserção publica */
BTree *BTree::insert(int value){

	//Insere a nova chave, e divide a raiz se necessário
	if(this->insert(value, this->root) && this->root->countKeys() > this->maxKeys){
		this->root->split(this->root->countKeys()/2);
	}

	return this;
}

/* Inserção protegida */
bool BTree::insert(int value, BTreePage *page){

	//Se já existir a chave, cancela a inserção
	if(page->hasKey(value)){
		return false;
	}

	//Se não for uma folha, acha a página filha ideal e o insere
	unsigned int index;
	if(!page->isLeaf()){

		index = page->getIndex(value);
		if(!this->insert(value, page->getBranche(index)))
			return false;
	}

	//Se for uma folha, apenas adiciona a nova chave
	else{
		page->addKey(value);
		return true;
	}

	//Caso ocorra overflow na página filha
	if(page->getBranche(index)->countKeys() > this->maxKeys){

		//Pega a página onde a chave foi adicionada e a divide
		BTreePage *child = page->getBranche(index);
		child->split(child->countKeys()/2);

		//Passa a chave restante e os dois ganhos para o pai
		page->addKey(child->getKey(0));
		page->setBranche(index, child->getBranche(0));
		page->insertBranche(index, child->getBranche(1), false);

		//Libera memória da página
		child->setBranche(0, NULL);
		child->setBranche(1, NULL);
		delete child;
	}

	return true;
}

/* Remoção publica */
bool BTree::remove(int value){

	//Remove a chave
	bool result = this->remove(value, this->root);

	//Se houve remoção e ocorreu um underflow na raiz altera a raiz para seu filho
	if(result && this->root->countBranches() == 1){
		BTreePage *oldRoot = this->root;
		this->root = oldRoot->getBranche(0);
		oldRoot->setBranche(0, NULL);
		delete oldRoot;
	}

	return result;
}

/* Remoção protegida */
bool BTree::remove(int value, BTreePage *page){

	//Guarda o index mais proximo do valor
	unsigned int index = page->getIndex(value);
	bool result = false;

	//Caso a página contém a chave
	if(page->hasKey(value)){

		//Se for uma folha, a remove a chave
		if(page->isLeaf()){
			page->removeKey(index);
			return true;
		}

		//Se for um nó interno, substitui pelo sucessor e remove o sucessor
		else{
			int sucessor = this->getSucessor(value, page);
			page->setKey(index, sucessor);
			result = this->remove(sucessor, page->getBranche(++index));
		}
	}

	//Caso a página não contenha a chave, procura na próxima filha 
	else if(!page->isLeaf()) result = this->remove(value, page->getBranche(index));

	//Se não, a chave não existe na árvore
	else return false;

	//Se houve remoção, realiza a redistribuição das chaves para deixar a árvore balanceada
	if(result) this->redistribute(index, page);
	return result;
}

/* Busca publica */
bool BTree::search(int value, collection& history){
	return this->search(value, history, this->root);
}

/* Busca protegida */
bool BTree::search(int value, collection& history, BTreePage *page){

	//Se tiver a página estiver vazia, não existe a chave
	if(page->isEmpty())
		return false;

	//Guarda o valor da chave átual
	unsigned int index = page->getIndex(value);
	history.push_back(page->getKey(index));

	//Caso seja igual, achou o a chave
	if(value == page->getKey(index))
		return true;

	//Se não, procura na próxima página
	if(!page->isLeaf())
		return this->search(value, history, page->getBranche(index));

	return false;
}

/* Percuso */
void BTree::each(std::function<void(int)> handle, char order){

	if(this->isEmpty())
		return;

	switch(order){

		//Em-ordem
		case tree::ERD_ORDER:
			this->root->eachInOrder(handle);
		break;

		//Pós-ordem
		case tree::EDR_ORDER:
			this->root->eachPostOrder(handle);
		break;

		//Pré-ordem
		case tree::RED_ORDER:
		default:
			this->root->eachPreOrder(handle);
	}
}

/* ******************* GETTERS ******************* */

/* Sucessor */
int BTree::getSucessor(int value, BTreePage *page){

	//Se a página for fazia, apenas retorna
	if(page == NULL || page->isEmpty())
		return 0;

	//Procura pelo sucessor ná propria página
	unsigned int index = page->getIndex(value);
	if(page->isLeaf())
		return page->getKey(index);

	//Se tiver filhos, procura na primeira chave da página mais a esquerda da páginda da direita
	page = page->getBranche(index + 1);
	while(!page->isLeaf())
		page = page->getBranche(0);

	return page->getKey(0);
}

/******************** CHECADORES ******************* */

/* Vazia */
bool BTree::isEmpty(){
	return this->root->isEmpty();
}

/* ******************* OUTROS ******************* */

/* Limpador */
void BTree::clear(){

	this->root->clear();
	return;
}

/* Calcula a altura */
int BTree::height(){

	//Verifica se a raiz está vazia
	BTreePage *page = this->root;
	int height = page->isEmpty() ? (-1) : 0;

	//Conta quantos filhos existem pela esquerda
	while(!page->isLeaf()){
		height++;
		page = page->getBranche(0);
	}

	return height;
}

/* Imprimi a arvore */
void BTree::print(){
	out->put("R:");
	BTreePage::printPage(this->root, 0);
}

/* Redistribui chaves entre pai e irmãos de uma página em underflow*/
void BTree::redistribute(unsigned int index, BTreePage *page){

	//Pega o filho com underflow
	BTreePage *child = page->getBranche(index);
	if(child->countKeys() >= this->order)
		return;

	//Pega os irmãos vizinhos
	BTreePage *left = index > 0 ? page->getBranche(index - 1) : NULL;
	BTreePage *right = index < page->countBranches() - 1 ? page->getBranche(index + 1) : NULL;

	//Se o irmão da esquerda tiver chaves suficiente
	if((left != NULL) && (left->countKeys() > this->order) && (left->isLeaf())){

		//Passa a chave separadora para o filho
		child->addKey(page->getKey(index - 1));
		page->removeKey(index - 1);

		//Passa a última chave do irmão da esquerda para o pai
		page->addKey(left->getKey(left->countKeys() - 1));
		left->removeKey(left->countKeys() - 1);
	}

	//Se o irmão da direita tiver chaves suficientes
	else if((right != NULL) && (right->countKeys() > this->order) && (right->isLeaf())){

		//Passa a chave separadora para o filho
		child->addKey(page->getKey(index));
		page->removeKey(index);

		//Passa a primeira chave do irmão da direita para o pai
		page->addKey(right->getKey(0));
		right->removeKey(0);
	}

	//Se o irmão da esquerda não tiver chaves suficiente
	else if((left != NULL) && (left->countKeys() == this->order)){

		//Passa a chave separadora para o filho e remove o irmão da esquerda
		child->addKey(page->getKey(index - 1));
		page->removeKey(index - 1);
		page->removeBranche(index - 1, false);

		//Passa todas as chaves e filhos do irmão da esquerda para a página com underflow
		unsigned int i;
		unsigned int totalKeys = left->countKeys();
		for(i = 0; i < totalKeys; i++){
			child->addKey(left->getKey(i));

			if(!child->isLeaf()){
				child->insertBranche(i, left->getBranche(i));
				left->setBranche(i, NULL);
			}
		}

		if(!child->isLeaf()){
			child->insertBranche(i, left->getBranche(i));
			left->setBranche(i, NULL);
		}

		//Libera a memória do irmão da esquerda
		delete left;
	}

	//Se o irmão da direita não tiver chaves suficiente
	else if((right != NULL) && (right->countKeys() == this->order)){

		//Passa a chave separadora para o filho e remove o irmão da direita
		child->addKey(page->getKey(index));
		page->removeKey(index);
		page->removeBranche(index + 1, false);

		//Passa todas as chaves e filhos do irmão da direita para a página com underflow
		unsigned int i;
		unsigned int totalKeys = right->countKeys();
		for(i = 0; i < totalKeys; i++){
			child->addKey(right->getKey(i));

			if(!child->isLeaf()){
				child->insertBranche(totalKeys + i, right->getBranche(i), false);
				right->setBranche(i, NULL);
			}
		}

		if(!child->isLeaf()){
			child->insertBranche(totalKeys + i, right->getBranche(i), false);
			right->setBranche(i, NULL);
		}

		//Libera a memória do irmão da direita
	 	delete right;
	}

	//Caso não haja chaves entre os irmãos e o pai
	else{

		//Se o irmão for da esquerda
		if(left != NULL){

			//Passa a chave separadora para o filho
			child->addKey(page->getKey(index - 1));
			page->removeKey(index - 1);

			//Passa a última chave do irmão da esquerda para o pai
			page->addKey(left->getKey(left->countKeys() - 1));
			left->removeKey(left->countKeys() - 1);

			//Passa o filhos para o irmão, caso haja
			if(!left->isLeaf()){
				child->insertBranche(0, left->getBranche(left->countBranches() - 1));
				left->removeBranche(left->countBranches() - 1, false);
			}
		}

		//Se o irmão for da direita
		else{

			//Passa a chave separadora para o filho
			child->addKey(page->getKey(index));
			page->removeKey(index);

			//Passa a última chave do irmão da esquerda para o pai
			page->addKey(right->getKey(0));
			right->removeKey(0);

			//Passa o filhos para o irmão, caso haja
			if(!right->isLeaf()){
				right->insertBranche(0, right->getBranche(0));
				right->removeBranche(0, false);
			}
		}
	}
}

/* ******************************************************************* */
/* ********************** Implementação BTreePage ******************** */
/* ******************************************************************* */

/* ******************* CONSTRUTORES E DESTRUTORES ******************* */

BTreePage::~BTreePage(){
	this->clear();
}

/* ******************* OPERAÇÕES ******************* */

/* Insere uma chave em posição especifica */
void BTreePage::insertKey(int value, unsigned int index, bool before){

	//Se a página estiver vazia, ou a posição for depois da última chave
	if((index >= this->countKeys() && !before) || this->isEmpty()){
		this->keys.push_back(value);
		return;
	}

	//Insere a chave ná página
	this->keys.insert(
		this->keys.begin() + index + (before ? 0 : 1),
		value
	);
}

/* Insere uma chave */
void BTreePage::addKey(int value){

	//Caso esteja vázia
	if(this->isEmpty()){
		this->keys.push_back(value);
		return;
	}

	//Verifica a posição que a chave deve ficar e a insere
	unsigned int index = this->getIndex(value);
	this->insertKey(value, index, value <= this->getKey(index));
}

/* Remove uma chave */
bool BTreePage::removeKey(unsigned int index){

	//Se tiver vázia, não há o que remover
	if(this->keys.empty())
		return false;

	//Se estiver no final da lista
	if(index >= this->countKeys())
		this->keys.pop_back();

	//Se estiver no meio ou início da lista
	else
		this->keys.erase(this->keys.begin() + index);

	return true;
}

/* Insere um galho em posição especifica */
void BTreePage::insertBranche(unsigned int index, BTreePage *page, bool before){

	//Se a página não tiver filhos, ou a posição for depois da último galho
	if((index >= this->countBranches() && !before) || this->isLeaf()){
		this->branches.push_back(page);
		return;
	}

	//Insere o galho ná página
	this->branches.insert(
		this->branches.begin() + index + (before ? 0 : 1),
		page
	);

}

/* Remove um galho */
bool BTreePage::removeBranche(unsigned int index, bool autoFree){

	//Se não tiver galho
	if(this->isLeaf())
		return false;

	//Se precisar liberar a memória do galho
	if(autoFree && this->getBranche(index) != NULL)
		delete this->getBranche(index);

	//Se estiver no final da lista
	if(index >= this->countBranches())
		this->branches.pop_back();

	//Se estiver no meio ou início da lista
	else
		this->branches.erase(this->branches.begin() + index);

	return true;
}

/* Percuso Pre-Ordem */
void BTreePage::eachPreOrder(std::function<void(int)> handle){

	if(this->isEmpty())
		return;

	unsigned int i;
	unsigned int totalKeys = this->countKeys();
	for(i = 0; i < totalKeys; i++){
		
		handle(this->getKey(i));
		if(!this->isLeaf())
			this->getBranche(i)->eachPreOrder(handle);
	}

	if(!this->isLeaf())
		this->getBranche(i)->eachPreOrder(handle);
}

/* Percuso Em-Ordem */
void BTreePage::eachInOrder(std::function<void(int)> handle){

	if(this->isEmpty())
		return;

	unsigned int i;
	unsigned int totalKeys = this->countKeys();
	for(i = 0; i < totalKeys; i++){

		if(!this->isLeaf())
			this->getBranche(i)->eachInOrder(handle);
		
		handle(this->getKey(i));
	}

	if(!this->isLeaf())
		this->getBranche(i)->eachInOrder(handle);
}

/* Percuso Pos-Ordem */
void BTreePage::eachPostOrder(std::function<void(int)> handle){

	if(this->isEmpty())
		return;

	if(!this->isLeaf())
		this->getBranche(0)->eachPostOrder(handle);

	unsigned int i;
	unsigned int totalKeys = this->countKeys() + 1;
	for(i = 1; i < totalKeys; i++){

		if(!this->isLeaf())
			this->getBranche(i)->eachPostOrder(handle);

		handle(this->getKey(i - 1));
	}
}

/* ******************* GETTERS ******************* */

/* Pega o index de uma chave, ou de seus sucessor mais proximo */
unsigned int BTreePage::getIndex(int valor){

	unsigned int i;

	for (i = 0; i < this->countKeys(); i++)
		if(valor <= this->getKey(i)) break;

	return i;
}

/* Pega o valor de uma chave */
int BTreePage::getKey(unsigned int index){

	if(this->isEmpty())
		return 0;

	if(index >= this->countKeys())
		return this->keys[this->countKeys() - 1];

	return this->keys[index];
}

/* Pega a referencia de um galho */
BTreePage *BTreePage::getBranche(unsigned int index){

	if(index >= this->countBranches())
		return this->branches[this->countBranches() - 1];

	return this->branches[index];
}	

/* ******************* SETTERS ******************* */

/* Define o valor de uma chave existente */
void BTreePage::setKey(unsigned int index, int value){

	if(this->isEmpty())
		return;

	if(index >= this->countKeys())
		index = this->countKeys() - 1;

	this->keys[index] = value;
}

/* Define a referencia de um galho já existente */
void BTreePage::setBranche(unsigned int index, BTreePage *page){

	if(index >= this->countBranches())
		return;

	this->branches[index] = page;
}

/******************** CHECADORES ******************* */

/* Verifica se a chave existe */
bool BTreePage::hasKey(int value){
	unsigned int index = this->getIndex(value);
	return value == this->getKey(index);
}

/* Verifica se a página está vazia */
bool BTreePage::isEmpty(){
	return this->keys.empty();
}

/* Verifica e existem galhos ná página */
bool BTreePage::isLeaf(){
	return this->branches.empty();
}

/* ******************* OUTROS ******************* */
	
void BTreePage::clear(){

	if(this->isEmpty())
		return;

	//Limpa lista de chaves
	this->keys.clear();

	//Limpa lista de galhos
	while(!this->branches.empty()){

		//Caso haja referência, libera a memória
		if(this->branches[0] != NULL){
			this->branches[0]->clear();
			delete this->branches[0];
		}

		this->branches.erase(this->branches.begin());
	}
}

/* Conta as chaves */
unsigned int BTreePage::countKeys(){
	return this->keys.size();
}

/* Conta os galhos */
unsigned int BTreePage::countBranches(){
	return this->branches.size();
}

/* Devie a página em 3 páginas */
void BTreePage::split(unsigned int pivot){

	if(this->isEmpty())
		return;

	//Pega o valor do pivô e instancia os filhos 
	int pivotValue = this->getKey(pivot);
	BTreePage *left = new BTreePage();
	BTreePage *right = new BTreePage();

	//Passa distribui as chaves entre os filhos
	unsigned int i = 0;
	while(this->countKeys() > 1){

		//Ignora o pivô
		if(pivotValue == this->getKey(i)) i++;

		//Menores para esquerda
		if(this->getKey(i) < pivotValue)
			left->addKey(this->getKey(i));

		//Maiores para direita
		else
			right->addKey(this->getKey(i));

		//Remoe a chave dá página
		this->removeKey(i);
	}

	//Se tiver filhos, distribui também
	if(!this->isLeaf()){

		for(i = 0; i < this->countBranches(); i++){

			//Antes do pivô para esquerda
			if(i <= pivot)
				left->insertBranche(i, this->getBranche(i), false);

			//Depois do pivô para direita
			else
				right->insertBranche(i, this->getBranche(i), false);

			//Desaponta para o galho
			this->setBranche(i, NULL);
		}
	}

	//Limpa os galhos átuais e adiciona os dois novos
	this->branches.clear();
	this->insertBranche(0, left, true);
	this->insertBranche(0, right, false);
}

/* Impre lista de chaves */
void BTreePage::printList(){

	//Formato: (<key[0]>, <key[1]>, ...,<key[n - 1]>)

	out->put("(");

	unsigned int totalKeys = this->countKeys();
	for(unsigned int i = 0; i < totalKeys; i++){

		out->put(this->getKey(i));

		if(i < totalKeys - 1) out->put(", ");
	}

	out->put(")");
}

/* Imprime toda a págia e suas filhas */
void BTreePage::printPage(BTreePage *page, int spaces){

	page->printList();
	out->putNewLine();

	if(page->isLeaf())
		return;

	unsigned int totalKeys = page->countBranches();
	for (unsigned int i = 0; i < totalKeys; i++){
		Tree::printSpaces(spaces+1);
		out->put(i)->put(':');
		BTreePage::printPage(page->getBranche(i), spaces+1);
	}
}
