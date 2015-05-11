#if !defined  _TREE_BINARY
#define _TREE_BINARY

#include "TreeInterface.hpp"

namespace tree{

	/**
	 * @todo: Documentar
	 * 
	 * @ver Bin Mark IV
	 */

	class BinaryTree : public Tree{

	protected:

		int *value;
		BinaryTree *left;
		BinaryTree *right;

		virtual BinaryTree *setLeft(BinaryTree *node);

		virtual BinaryTree *setRight(BinaryTree *node);

		virtual BinaryTree *setValue(int value);

		unsigned int countChildren();

		bool remove(int value, BinaryTree *parent);

		virtual void printNodeValue();

		void print(int spaces);

	public:

		BinaryTree();
		
		BinaryTree(int value);

		virtual ~BinaryTree();

		virtual BinaryTree *insert(int value);

		virtual bool remove(int value);

		bool search(int value, collection& history);

		void each(std::function<void(int)> handle, char order = tree::RED_ORDER);

		virtual BinaryTree *getLeft();

		virtual BinaryTree *getRight();

		int getValue();

		BinaryTree *getSucessor();

		BinaryTree *getPredecessor();

		bool isEmpty();

		bool isLeaf();

		void clear();

		int height();

		void print();

	};
}
#endif