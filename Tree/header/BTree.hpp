#if !defined  _TREE_B
#define _TREE_B

#include "TreeInterface.hpp"
#include "BTreePage.hpp"

namespace tree{

	/*
		CHECKLIST:
		* Inserção [X]
		* Remoção [ ]
		* Busca	[ ]
		* Percurso [ ]
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
			return false;
		}

		bool search(int value, collection& history){
			return false;
		}

		int height(){
			return 0;
		}

		bool isEmpty(){
			return true;
		}

		void print(){
			out->put("R:");
			BTreePage::printPage(this->root, 0);
		}
	};
}

#endif