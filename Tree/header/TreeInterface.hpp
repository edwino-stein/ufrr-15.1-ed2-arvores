/*
	Edwino Stein - 1201324411
*/

#if !defined  _TREE_INTERFACE
#define _TREE_INTERFACE

#include "../../Common/Common.hpp"
#include <vector>

namespace tree {

	/**
	 * @todo: Documentar
	 */

	typedef std::vector<int> collection;

	//Pré-Ordem
	static const char RED_ORDER = 0;

	//Em-Ordem
	static const char ERD_ORDER = 1;

	//Pós-Ordem
	static const char EDR_ORDER = 2;

	class Tree : public Object{

	public:

		virtual ~Tree(){}

		virtual void clear()=0;

		virtual Tree *insert(int value)=0;

		virtual bool remove(int value)=0;

		virtual bool search(int value, collection& history)=0;

		virtual int height()=0;

		virtual bool isEmpty()=0;

		static void printSpaces(int spaces);

	};

}

#endif