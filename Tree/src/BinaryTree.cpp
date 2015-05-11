/*
	Edwino Stein - 1201324411
*/

/* *************************************************************** */
/* ******************* Implementação BinaryTree ****************** */
/* *************************************************************** */

#include "../header/BinaryTree.hpp"
using namespace tree;

/* ******************* CONSTRUTORES E DESTRUTORES ******************* */

BinaryTree::BinaryTree(){
	//Inicializa os ponteiros
	this->value = NULL;
	this->left = NULL;
	this->right = NULL;
}

BinaryTree::BinaryTree(int value) : BinaryTree(){
	//Insere o primeiro valor na árvore
	this->insert(value);
}

BinaryTree::~BinaryTree(){
	//Limpa toda a árvore
	this->clear();
}

/* ******************* OPERAÇÕES ******************* */

/* Inserção */
BinaryTree *BinaryTree::insert(int value){

	//Se for vazia, apenas inicializa o nó
	if(this->isEmpty())
		this->setValue(value);

	//Se for menor, vai para esquerda
	else if(value < this->getValue())
		return this->getLeft()->insert(value);

	//Se for maior, vai para direita
	else if(value > this->getValue())
		return this->getRight()->insert(value);

	//Se for igual, apenas retorna o nó
	return this;
}

/* Remoção publica */
bool BinaryTree::remove(int value){
	return this->remove(value, NULL);
}

/* Remoção protegida */
bool BinaryTree::remove(int value, BinaryTree *parent){

	//Se for vazia, não há o que remover
	if(this->isEmpty())
		return false;

	//Se for menor, vai para esquerda
	if(value < this->getValue())
		return this->getLeft()->remove(value, this);

	//Se for maior, vai para direita
	else if(value > this->getValue())
		return this->getRight()->remove(value, this);

	//Se não achar o número
	else if(value != this->getValue())
		return false;

	//Caso o nó seja uma folha
	if(this->isLeaf()){
		this->clear();
	}

	//Caso tenha apenas um filho
	else if(this->countChildren() == 1){

		//Verifica qual lado está o filho
		BinaryTree *child;
		child = !this->getLeft()->isEmpty() ? this->getLeft() : this->getRight();

		//Passa os dados do filho para o pai
		this->setValue(child->getValue())
			->setLeft(child->getLeft())
			->setRight(child->getRight());

		//Corta as relaçoes com os filhos do filho
		child->setLeft(NULL)
			 ->setRight(NULL);

		//Libera memoria do filho
		delete child;
	}

	//Caso o nó tenha dois filhos
	else{

		//Procura o substituto mais proximo (sucessor ou antecessor)
		int substitute;
		substitute = this->getLeft()->height() <= this->getRight()->height() ?
					 this->getPredecessor()->getValue() : this->getSucessor()->getValue();

		//Troca o valor do nó pelo do substituto deletando-o
		this->remove(substitute, this);
		this->setValue(substitute);
	}

	return true;
}

/* Busca */
bool BinaryTree::search(int value, collection& history){

	//Se o nó for vazio, não há o que procurar
	if(this->isEmpty())
		return false;

	//Guarda valor do nó no histórico
	history.push_back(this->getValue());

	//Se for menor, vai para esquerda
	if(value < this->getValue())
		return this->getLeft()->search(value, history);

	//Se for maior, vai para direita
	else if(value > this->getValue())
		return this->getRight()->search(value, history);

	//Se for igual, achou o valor
	else if(value == this->getValue())
		return true;

	//Se for diferente, apenas termina.
	return false;

}

/* Percuso */
void BinaryTree::each(std::function<void(int)> handle, char order){

	if(this->isEmpty())
		return;

	switch(order){

		//Em-ordem
		case ERD_ORDER:
			this->getLeft()->each(handle, order);
			handle(this->getValue());
			this->getRight()->each(handle, order);
		break;

		//Pós-ordem
		case EDR_ORDER:
			this->getLeft()->each(handle, order);
			this->getRight()->each(handle, order);
			handle(this->getValue());
		break;

		//Pré-ordem
		case RED_ORDER:
		default:
			handle(this->getValue());
			this->getLeft()->each(handle, order);
			this->getRight()->each(handle, order);
	}

}

/* ******************* GETTERS ******************* */

/* Esquerdo */
BinaryTree *BinaryTree::getLeft(){

	//Se não existir nó a esquerda, cria um vazio
	if(this->left == NULL)
		this->setLeft(new BinaryTree());

	return this->left;
}

/* Direito */
BinaryTree *BinaryTree::getRight(){
	
	//Se não existir nó a direita, cria um vazio
	if(this->right == NULL)
		this->setRight(new BinaryTree());

	return this->right;
}

/* Valor */
int BinaryTree::getValue(){
	return this->value != NULL ? *this->value : 0;
}

/* Sucessor */
BinaryTree *BinaryTree::getSucessor(){

	//Se for uma folha, ou for fazio ou não tiver filho na direita, apenas retorna
	if(this->isLeaf() || this->isEmpty() || this->getRight() == NULL)
		return this;

	//Guada o filho da direita e navega até o ultimo filho da esquerda
	BinaryTree *node = this->getRight();
	while(!node->getLeft()->isEmpty())
		node = node->getLeft();

	return node;
}

/* Antecessor */
BinaryTree *BinaryTree::getPredecessor(){

	//Se for uma folha, ou for fazio ou não tiver filho na esquerda, apenas retorna
	if(this->isLeaf() || this->isEmpty() || this->getLeft() == NULL)
		return this;

	//Guada o filho da esquerda e navega até o ultimo filho da direita
	BinaryTree *node = this->getLeft();
	while(!node->getRight()->isEmpty())
		node = node->getRight();

	return node;
}

/* ******************* SETTERS ******************* */

/* Esquerdo */
BinaryTree *BinaryTree::setLeft(BinaryTree *node){
	this->left = node;
	return this;
}

/* Direito */
BinaryTree *BinaryTree::setRight(BinaryTree *node){
	this->right = node;
	return this;
}

/* Valor */
BinaryTree *BinaryTree::setValue(int value){

	if(this->value != NULL)
		delete this->value;

	this->value = new int(value);
	return this;
}

/******************** CHECADORES ******************* */

/* Vazia */
bool BinaryTree::isEmpty(){
	return this->value == NULL;
}

/* Folha */
bool BinaryTree::isLeaf(){
	return this->countChildren() == 0;
}

/* ******************* OUTROS ******************* */

/* Conta os filhos */
unsigned int BinaryTree::countChildren(){

	unsigned int total = 0;

	if(!this->getLeft()->isEmpty())
		total++;

	if(!this->getRight()->isEmpty())
		total++;

	return total;
}

/* Limpador */
void BinaryTree::clear(){

	if(this->isEmpty())
		return;

	//Libera memória do valor
	delete this->value;
	this->value = NULL;

	//Libera memória do nó da esquerda
	if(this->left != NULL){
		this->left->clear();
		delete this->left;
		this->left = NULL;
	}

	//Libera memória do nó da direita
	if(this->right != NULL){
		this->right->clear();
		delete this->right;
		this->right = NULL;
	}
}

/* Calcula a altura */
int BinaryTree::height(){

	//Se for vazia, altura é negativa
	if(this->isEmpty())
		return (-1);

	//Pegas as alturas dos filhos
	int heightLeft = this->getLeft()->height();
	int heightRight = this->getRight()->height();

	//Retorna a maior incrementada
	return (heightLeft >= heightRight ? heightLeft : heightRight) + 1;
}

/* Imprime o valor do nó */
void BinaryTree::printNodeValue(){
	//Formato: (<valor>)
	out ->put("(")->put(this->getValue())->put(')', true);
}

/* Imprimi a arvore publica */
void BinaryTree::print(){
	this->print(0);
}

/* Imprimi a arvore protegida */
void BinaryTree::print(int spaces){

	if(this->isEmpty())
		return;

	//Imprime o valor do nó
	this->printNodeValue();

	if(this->isLeaf())
		return;

	//Se tiver esquerda, impreme a arvore da esquerda
	Tree::printSpaces(spaces + 1);
	out->put('L');
	if(!this->getLeft()->isEmpty())
		this->getLeft()->print(spaces + 1);
	else
		out->put("( )", true);

	//Se tiver direita, impreme a arvore da direita
	Tree::printSpaces(spaces + 1);
	out->put('R');
	if(!this->getRight()->isEmpty())
		this->getRight()->print(spaces + 1);
	else
		out->put("( )", true);

}

/* ******************* TREE ******************* */

void Tree::printSpaces(int spaces){
	for(int i = 1; i <= spaces; i++)
		out->put((i == spaces) ? " - " : "  ");
}
