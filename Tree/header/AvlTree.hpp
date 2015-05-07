#if !defined  _TREE_AVL
#define _TREE_AVL

#include "BinaryTree.hpp"

namespace tree{

	/**
	 * @todo: Documentar
	 * 
	 * @ver Avl Mark II
	 */

	class AvlTree : public BinaryTree{

	protected:

		AvlTree *setValue(int value);

		AvlTree *setLeft(BinaryTree *node);

		AvlTree *setRight(BinaryTree *node);

		int getBalanceFactor();

		void doBalance();

		void rotationToRight();

		void rotationToLeft();

		void printNodeValue();

	public:

		AvlTree();

		AvlTree(int value);

		~AvlTree();

		AvlTree *insert(int value);

		bool remove(int value);

		AvlTree *getLeft();

		AvlTree *getRight();

	};
}

#endif