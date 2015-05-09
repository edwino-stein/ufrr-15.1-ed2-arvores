
#if !defined  _TREE_B_PAGE
#define _TREE_B_PAGE

#include "TreeInterface.hpp"

namespace tree{

	class BTreePage : public Object{

		friend class BTree;

	protected:

		std::vector<int> keys;
		std::vector<BTreePage *> branches;

		~BTreePage();

		void insertKey(int value, unsigned int index, bool before = true);

		void addKey(int value);

		bool removeKey(unsigned int index);

		void insertBranche(unsigned int index, BTreePage *page, bool before = true);

		bool removeBranche(unsigned int index, bool autoFree = true);

		void eachPreOrder(std::function<void(int)> handle);

		void eachInOrder(std::function<void(int)> handle);

		void eachPostOrder(std::function<void(int)> handle);


		unsigned int getIndex(int valor);

		int getKey(unsigned int index);

		BTreePage *getBranche(unsigned int index);


		void setKey(unsigned int index, int value);

		void setBranche(unsigned int index, BTreePage *page);


		bool hasKey(int value);

		bool isEmpty();

		bool isLeaf();


		void clear();

		unsigned int countKeys();

		unsigned int countBranches();
		
		void split(unsigned int pivot);

		void printList();

		static void printPage(BTreePage *page, int spaces);

	};
}

#endif