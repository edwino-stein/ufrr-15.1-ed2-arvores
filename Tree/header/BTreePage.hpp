
#if !defined  _TREE_B_PAGE
#define _TREE_B_PAGE

#include "TreeInterface.hpp"

namespace tree{

	class BTreePage : public Object{
		friend class BTree;

		std::vector<int> keys;
		std::vector<BTreePage *> branches;

		unsigned int getIndex(int valor){

			unsigned int i;

			for (i = 0; i < this->countKeys(); ++i)
				if(valor <= this->getKey(i)) break;

			return i;
		}

		void insertKey(int value, unsigned int index, bool before = true){

			if((index >= this->countKeys() && !before) || this->isEmpty()){
				this->keys.push_back(value);
				return;
			}

			this->keys.insert(
				this->keys.begin() + index + (before ? 0 : 1),
				value
			);
		}

		void addKey(int value){

			if(this->isEmpty()){
				this->keys.push_back(value);
				return;
			}

			unsigned int index = this->getIndex(value);
			this->insertKey(value, index, value <= this->getKey(index));
		}

		bool removeKey(unsigned int index){

			if(this->keys.empty())
				return false;

			this->keys.erase(this->keys.begin() + index);

			return true;
		}

		int getKey(unsigned int index){

			if(this->isEmpty())
				return 0;

			if(index >= this->countKeys())
				return this->keys[this->countKeys() - 1];

			return this->keys[index];
		}

		void setKey(unsigned int index, int value){

			if(this->isEmpty())
				return;

			if(index >= this->countKeys())
				index = this->countKeys() - 1;

			this->keys[index] = value;
		}

		bool hasKey(int value){
			unsigned int index = this->getIndex(value);
			return value == this->getKey(index);
		}

		BTreePage *getBranche(unsigned int index){

			if(index >= this->countBranches())
				return this->branches[this->countBranches() - 1];

			return this->branches[index];
		}

		void setBranche(unsigned int index, BTreePage *page){

			if(index >= this->countBranches())
				return;

			this->branches[index] = page;
		}

		void insertBranche(unsigned int index, BTreePage *page, bool before = true){

			if((index >= this->countBranches() && !before) || this->isLeaf()){
				this->branches.push_back(page);
				return;
			}

			this->branches.insert(
				this->branches.begin() + index + (before ? 0 : 1),
				page
			);

		}

		void split(unsigned int pivot){

			if(this->isEmpty())
				return;

			int pivotValue = this->getKey(pivot);
			BTreePage *left = new BTreePage();
			BTreePage *right = new BTreePage();

			unsigned int i = 0;
			while(this->countKeys() > 1){

				if(pivotValue == this->getKey(i)) i++;

				if(this->getKey(i) < pivotValue)
					left->addKey(this->getKey(i));
				else
					right->addKey(this->getKey(i));

				this->removeKey(i);
			}

			if(!this->isLeaf()){

				for(i = 0; i < this->countBranches(); i++){

					if(i <= pivot)
						left->insertBranche(i, this->getBranche(i), false);
					else
						right->insertBranche(i, this->getBranche(i), false);

					this->setBranche(i, NULL);
				}
			}

			this->branches.clear();
			this->insertBranche(0, left, true);
			this->insertBranche(0, right, false);
		}

		unsigned int countKeys(){
			return this->keys.size();
		}

		unsigned int countBranches(){
			return this->branches.size();
		}

		bool isEmpty(){
			return this->keys.empty();
		}

		bool isLeaf(){
			return this->branches.empty();
		}

		void printList(){

			out->put("(");

			unsigned int totalKeys = this->countKeys();

			for(unsigned int i = 0; i < totalKeys; i++){

				out->put(this->getKey(i));

				if(i < totalKeys - 1) out->put(", ");
			}

			out->put(")");
		}

		static void printPage(BTreePage *page, int spaces){

			if(page->isEmpty())
				return;

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
	};
}

#endif