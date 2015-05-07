/*
	Edwino Stein - 1201324411
*/

/* *************************************************************** */
/* ******************* Implementação AvlTree ****************** */
/* *************************************************************** */

#include "../header/AvlTree.hpp"
using namespace tree;

/* ******************* CONSTRUTORES E DESTRUTORES ******************* */

AvlTree::AvlTree() : BinaryTree(){}
AvlTree::AvlTree(int value) : BinaryTree(value){}
AvlTree::~AvlTree(){ this->clear(); }

/* ******************* OPERAÇÕES ******************* */

/* Inserção */
AvlTree *AvlTree::insert(int value){
	//Chama o método de inserir do pai
	AvlTree *node = (AvlTree *) BinaryTree::insert(value);

	//Balanceia a árvore após a inserção
	this->doBalance();
	return node;
}

/* Remoção */
bool AvlTree::remove(int value){

	//Chama o método de remoção do pai
	bool result = BinaryTree::remove(value);

	//Se houve remoção, balanceia a árvore
	if(result)
		this->doBalance();

	return result;
}

/* ******************* GETTERS ******************* */

/* Esquerdo */
AvlTree *AvlTree::getLeft(){

	//Se não existir nó a esquerda, cria um vazio
	if(this->left == NULL)
		this->setLeft(new AvlTree());

	return (AvlTree *) this->left;
}

/* Direito */
AvlTree *AvlTree::getRight(){

	//Se não existir nó a direita, cria um vazio
	if(this->right == NULL)
		this->setRight(new AvlTree());

	return (AvlTree *) this->right;
}

/* Calcula o fator de balanceamento */
int AvlTree::getBalanceFactor(){
	return this->getRight()->height() - this->getLeft()->height();
}

/* ******************* SETTERS ******************* */

/* Valor */
AvlTree *AvlTree::setValue(int value){
	return (AvlTree *) BinaryTree::setValue(value);
}

/* Esquerdo */
AvlTree *AvlTree::setLeft(BinaryTree *node){
	return (AvlTree *) BinaryTree::setLeft(node);
}
/* Direito */
AvlTree *AvlTree::setRight(BinaryTree *node){
	return (AvlTree *) BinaryTree::setRight(node);
}

/* ******************* OUTROS ******************* */

/* Balanceia a árvore */
void AvlTree::doBalance(){

	//Se tiver vazio, não há o que balancear
	if(this->isEmpty())
		return;

	int balanceFactor = 0;

	//Loop infinito que garante que só suba na pilha até que esteja realmente balanceado
	while(true){

		//Balanceia os filhos e calcula o fator de balanceamento
		this->getLeft()->doBalance();
		this->getRight()->doBalance();
		balanceFactor = this->getBalanceFactor();

		//Se tiver entre -1 e 1, está balanceada
		if(balanceFactor >= (-1) && balanceFactor <= 1 )
			return;

		//Se tiver menor ou igual a -2, está desbalanceada para esquerda
		if(balanceFactor <= (-2)){

			//Rotação simples para direita
			if(this->getLeft()->getBalanceFactor() == (-1)){
				this->rotationToRight();
			}

			//Dupla rotação: simples para esquerda e uma simples para direita
			else{
				this->getLeft()->rotationToLeft();
				this->rotationToRight();
			}
		}

		//Se tiver menor ou igual a 2, está desbalanceada para direita
		else if(balanceFactor >= 2){

			//Rotação simples para esquerda
			if(this->getRight()->getBalanceFactor() == 1){
				this->rotationToLeft();
			}

			//Dupla rotação: simples para direita e uma simples para esquerda
			else{
				this->getRight()->rotationToRight();
				this->rotationToLeft();
			}
		}
	}
}

/* Rotacionar para direita */
void AvlTree::rotationToRight(){

	//Pega o filho da esquerda e verifica se é possivel rotacionar
	AvlTree *leftChild = this->getLeft();
	if(this->isLeaf() || leftChild->isEmpty())
		return;

	//Cria um nó novo e transfere os dados do nó que será retornado
	AvlTree *temp = new AvlTree(this->getValue());
	temp->setLeft(leftChild->getRight())
		->setRight(this->getRight());

	//Transfere os dados do filho da esquerda para o nó que será rotacionado
	this->setValue(leftChild->getValue())
		->setLeft(leftChild->getLeft())
		->setRight(temp);

	//Libera a memória do nó da esquerda
	leftChild->setLeft(NULL)
			  ->setRight(NULL);
	delete leftChild;
}

/* Rotacionar para esquerda */
void AvlTree::rotationToLeft(){

	//Pega o filho da direita e verifica se é possivel rotacionar
	AvlTree *rightChild = this->getRight();
	if(this->isLeaf() || rightChild->isEmpty())
		return;

	//Cria um nó novo e transfere os dados do nó que será retornado
	AvlTree *temp = new AvlTree(this->getValue());
	temp->setLeft(this->getLeft())
		->setRight(rightChild->getLeft());

	//Transfere os dados do filho da direita para o nó que será rotacionado
	this->setValue(rightChild->getValue())
		->setLeft(temp)
		->setRight(rightChild->getRight());

	//Libera a memória do nó da direita
	rightChild->setLeft(NULL)
			  ->setRight(NULL);
	delete rightChild;
}

void AvlTree::printNodeValue(){

	//Formato (<valor>, <fat_balancemento>)
	out ->put("(")
		->put(this->getValue())
		->put(", ")
		->put(this->getBalanceFactor())
		->put(')',true);
}
