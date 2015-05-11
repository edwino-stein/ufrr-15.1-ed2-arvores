/*
	Edwino Stein - 1201324411
*/

#if !defined  _TREE_INTERFACE
#define _TREE_INTERFACE

#include "../../Common/Common.hpp"
#include <vector>
#include <functional>

namespace tree {

	/**
	 * @brief: Tipo de uma coleção de valores da árvore.
	 */
	typedef std::vector<int> collection;

	/**
	 * @brief Constante Pré-Ordem (Raiz-Esquerda-Direita)
	 */
	static const char RED_ORDER = 0;

	/**
	 * @brief Constante Em-Ordem (Esquerda-Raiz-Direita)
	 */
	static const char ERD_ORDER = 1;

	/**
	 * @brief Constante Pós-Ordem (Esquerda-Direita-Raiz)
	 */
	static const char EDR_ORDER = 2;


	/**
	 * @brief Interface básica de uma árvore
	 */
	class Tree : public Object{

	public:

		/**
		 * @brief Destrutor padrão
		 */
		virtual ~Tree();

		/**
		 * @brief Protótipo do método de limpeza.
		 */
		virtual void clear()=0;

		/**
		 * @brief Protótipo do método de inserção.
		 */
		virtual Tree *insert(int value)=0;

		/**
		 * @brief Protótipo do método de remoção.
		 */
		virtual bool remove(int value)=0;

		/**
		 * @brief Protótipo do método de busca.
		 */
		virtual bool search(int value, collection& history)=0;

		/**
		 * @brief Protótipo do método de percurso.
		 */
		virtual void each(std::function<void(int)> handle, char order) =0;

		/**
		 * @brief Protótipo do método de impressão.
		 */
		virtual void print()=0;

		/**
		 * @brief Protótipo do método de calculo da altura.
		 */
		virtual int height()=0;

		/**
		 * @brief Protótipo do método que verifica se a árvore está vazia.
		 */
		virtual bool isEmpty()=0;

		/**
		 * @brief Imprime espaços para recuo.
		 * @param spaces Quantidade de espaços.
		 */
		static void printSpaces(int spaces);

	};

}

#endif