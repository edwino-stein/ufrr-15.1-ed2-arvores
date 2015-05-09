#if !defined  _TREE_B
#define _TREE_B

#include "TreeInterface.hpp"
#include "BTreePage.hpp"

namespace tree{

	/*
		CHECKLIST:
		* Inserção [X]
		* Remoção [X]
		* Busca	[X]
		* Percurso [X]
		* Impressão [X]
	*/

	class BTree : public Tree{

	public:

		const unsigned int order;
		const unsigned int maxKeys;
		const unsigned int maxBranches;

		BTreePage *root;

		BTree(unsigned int order) : order(order), maxKeys(2 * order), maxBranches(2 * order + 1){
			this->root = new BTreePage();
		}

		BTree(unsigned int order, int value): BTree(order){
			this->insert(value);
		}

		~BTree(){
			this->clear();
		}

		void clear(){
			return;
		}

		BTree *insert(int value){

			if(this->insert(value, this->root) && this->root->countKeys() > this->maxKeys){
				this->root->split(this->root->countKeys()/2);
			}

			return this;
		}

		bool insert(int value, BTreePage *page){

			if(page->hasKey(value)){
				return false;
			}

			unsigned int index;
			if(!page->isLeaf()){
				index = page->getIndex(value);

				if(!this->insert(value, page->getBranche(index)))
					return false;
			}
			else{
				page->addKey(value);
				return true;
			}

			if(page->getBranche(index)->countKeys() > this->maxKeys){

				BTreePage *child = page->getBranche(index);
				child->split(child->countKeys()/2);

				page->addKey(child->getKey(0));
				page->setBranche(index, child->getBranche(0));
				page->insertBranche(index, child->getBranche(1), false);

				child->setBranche(0, NULL);
				child->setBranche(1, NULL);
				delete child;
			}

			return true;
		}

		bool remove(int value){

			bool result = this->remove(value, this->root);

			if(result && this->root->countBranches() == 1){
				BTreePage *oldRoot = this->root;
				this->root = oldRoot->getBranche(0);
				oldRoot->setBranche(0, NULL);
				delete oldRoot;
			}

			return result;
		}

		bool remove(int value, BTreePage *page){

			unsigned int index = page->getIndex(value);
			bool result = false;

			if(page->hasKey(value)){

				if(page->isLeaf()){
					page->removeKey(index);
					return true;
				}

				else{
					int sucessor = this->getSucessor(value, page);
					page->setKey(index, sucessor);
					result = this->remove(sucessor, page->getBranche(++index));
				}
			}
			else if(!page->isLeaf()) result = this->remove(value, page->getBranche(index));
			else return false;

			if(result) this->redistribute(index, page);
			return result;
		}

		void redistribute(unsigned int index, BTreePage *page){

			BTreePage *child = page->getBranche(index);
			if(child->countKeys() >= this->order)
				return;

			BTreePage *left = index > 0 ? page->getBranche(index - 1) : NULL;
			BTreePage *right = index < page->countBranches() - 1 ? page->getBranche(index + 1) : NULL;

			if((left != NULL) && (left->countKeys() > this->order) && (left->isLeaf())){

				child->addKey(page->getKey(index - 1));
				page->removeKey(index - 1);
				page->addKey(left->getKey(left->countKeys() - 1));
				left->removeKey(left->countKeys() - 1);
			}

			else if((right != NULL) && (right->countKeys() > this->order) && (right->isLeaf())){

				child->addKey(page->getKey(index));
				page->removeKey(index);
				page->addKey(right->getKey(0));
				right->removeKey(0);
			}

			else if((left != NULL) && (left->countKeys() == this->order)){

				child->addKey(page->getKey(index - 1));
				page->removeKey(index - 1);
				page->removeBranche(index - 1, false);

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

				delete left;
			}

			else if((right != NULL) && (right->countKeys() == this->order)){

				child->addKey(page->getKey(index));
				page->removeKey(index);
				page->removeBranche(index + 1, false);

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

			 	delete right;
			}

			else{

				if(left != NULL){

					child->addKey(page->getKey(index - 1));
					page->removeKey(index - 1);
					page->addKey(left->getKey(left->countKeys() - 1));
					left->removeKey(left->countKeys() - 1);

					if(!left->isLeaf()){
						child->insertBranche(0, left->getBranche(left->countBranches() - 1));
						left->removeBranche(left->countBranches() - 1, false);
					}
				}

				else{

					child->addKey(page->getKey(index));
					page->removeKey(index);
					page->addKey(right->getKey(0));
					right->removeKey(0);

					if(!right->isLeaf()){
						right->insertBranche(0, right->getBranche(0));
						right->removeBranche(0, false);
					}
				}

			}

		}

		bool search(int value, collection& history){
			return this->search(value, history, this->root);
		}

		bool search(int value, collection& history, BTreePage *page){

			if(page->isEmpty())
				return false;

			unsigned int index = page->getIndex(value);
			history.push_back(page->getKey(index));

			if(value == page->getKey(index))
				return true;

			if(!page->isLeaf())
				return this->search(value, history, page->getBranche(index));

			return false;
		}

		void each(std::function<void(int)> handle,  char order = tree::RED_ORDER){

			if(this->isEmpty())
				return;

			switch(order){

				case tree::ERD_ORDER:
					this->root->eachInOrder(handle);
				break;

				case tree::EDR_ORDER:
					this->root->eachPostOrder(handle);
				break;

				case tree::RED_ORDER:
				default:
					this->root->eachPreOrder(handle);
			}
		}

		int height(){

			BTreePage *page = this->root;
			int height = page->isEmpty() ? (-1) : 0;

			while(!page->isLeaf()){
				height++;
				page = page->getBranche(0);
			}

			return height;
		}

		bool isEmpty(){
			return this->root->isEmpty();
		}

		void print(){
			out->put("R:");
			BTreePage::printPage(this->root, 0);
		}

		int getSucessor(int value, BTreePage *page){

			if(page == NULL || page->isEmpty())
				return 0;

			unsigned int index = page->getIndex(value);
			if(page->isLeaf())
				return page->getKey(index);

			page = page->getBranche(index + 1);
			while(!page->isLeaf())
				page = page->getBranche(0);

			return page->getKey(0);
		}
	};
}

#endif