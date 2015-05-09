#if !defined  _TREE_B
#define _TREE_B

#include "TreeInterface.hpp"
#include "BTreePage.hpp"

namespace tree{

	/**
	 * @todo: Documentar
	 * 
	 * @ver B Mark IV
	 */

	class BTree : public Tree{

	protected:

		const unsigned int order;
		const unsigned int maxKeys;
		const unsigned int maxBranches;

		BTreePage *root;

		bool insert(int value, BTreePage *page);

		bool remove(int value, BTreePage *page);

		bool search(int value, collection& history, BTreePage *page);

		int getSucessor(int value, BTreePage *page);

		void redistribute(unsigned int index, BTreePage *page);

	public:

		BTree(unsigned int order);

		BTree(unsigned int order, int value);

		~BTree();

		BTree *insert(int value);

		bool remove(int value);

		bool search(int value, collection& history);

		void each(std::function<void(int)> handle, char order = tree::RED_ORDER);

		bool isEmpty();

		void clear();

		int height();

		void print();

	};
}

#endif