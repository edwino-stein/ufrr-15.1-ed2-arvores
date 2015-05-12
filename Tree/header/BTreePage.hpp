
#if !defined  _TREE_B_PAGE
#define _TREE_B_PAGE

#include "TreeInterface.hpp"

namespace tree{

	/**
	 * @brief Página da árvore B
	 */
	class BTreePage : public Object{

		friend class BTree;

	protected:

		/**
		 * @brief Chaves da página
		 */
		std::vector<int> keys;

		/**
		 * @brief Filhos da página
		 */
		std::vector<BTreePage *> branches;

		/**
		 * @brief Destrutor padrão
		 */
		~BTreePage();

		/**
		 * @brief Insere uma chave em um local especifico da página.
		 * 
		 * @param value Valor da chave que será inserida.
		 * @param unsigned int Índice da posição em que a cahve será inserida.
		 * @param before Flag que indentidica se a chave será inserida antes ou depois do índice fornecido.
		 */
		void insertKey(int value, unsigned int index, bool before = true);

		/**
		 * @brief Adiciona uma chave ordenadamente na página.
		 * @details Procura a posição ordenada e insere a chave.
		 * 
		 * @param value Valor da chave que será adicionada.
		 */
		void addKey(int value);

		/**
		 * @brief Remove uma chave da página.
		 * @details Remove a chave presente na posição informada.
		 * 
		 * @param unsigned int Índice da posição da que chave será removida.
		 * @return <b>TRUE</b> caso a chave tenha sido removida, e <b>FALSE</b> para caso a chave não exista na página.
		 */
		bool removeKey(unsigned int index);

		/**
		 * @brief Insere um filho em um local especifico da página.
		 * 
		 * @param unsigned int Índice da posição em que o filho será inserida.
		 * @param page Referência da página. 
		 * @param before Flag que indentidica se a página será inserida antes ou depois do índice fornecido.
		 */
		void insertBranche(unsigned int index, BTreePage *page, bool before = true);

		/**
		 * @brief Remove um filho da página.
		 * @details Remove o filho presente na posição informada.
		 * 
		 * @param unsigned int Índice da posição do filho que será removida.
		 * @return <b>TRUE</b> caso o filho tenha sido removido, e <b>FALSE</b> para caso o filho não exista na página.
		 */		
		bool removeBranche(unsigned int index, bool autoFree = true);

		/**
		 * @brief Percorre a página e seus filhos em Pré-Ordem.
		 * @param handle Função anônima que será executada para cada chave.
		 */
		void eachPreOrder(std::function<void(int)> handle);

		/**
		 * @brief Percorre a página e seus filhos Em-Ordem.
		 * @param handle Função anônima que será executada para cada chave.
		 */
		void eachInOrder(std::function<void(int)> handle);

		/**
		 * @brief Percorre a página e seus filhos em Pós-Ordem.
		 * @param handle Função anônima que será executada para cada chave.
		 */
		void eachPostOrder(std::function<void(int)> handle);

		/**
		 * @brief Pega o índice do valor o do seu sucessor na página.
		 * @details Busca a chave na página e retorna seu índice, caso não a encontre, retorna o índice do seu sucessor.
		 * 
		 * @param valor Valor da chave que será procurada.
		 * @return Índice da chave na página.
		 */
		unsigned int getIndex(int valor);

		/**
		 * @brief Retorna o valor de uma chave da página.
		 * 
		 * @param unsigned int Índice da posição de que chave.
		 * @return Valor da chave.
		 */
		int getKey(unsigned int index);

		/**
		 * @brief Retorna a referência de um filho da página.
		 * 
		 * @param unsigned int Índice da posição do filho.
		 * @return Referência da página filho.
		 */
		BTreePage *getBranche(unsigned int index);

		/**
		 * @brief Define o valor de uma chave da página.
		 * 
		 * @param unsigned int Índice da posição de que chave.
		 */
		void setKey(unsigned int index, int value);

		/**
		 * @brief Define a referência de um filho da página.
		 * 
		 * @param unsigned int Índice da posição do filho.
		 */
		void setBranche(unsigned int index, BTreePage *page);

		/**
		 * @brief Verifica se a chave existe na página.
		 * 
		 * @param value Valor da chave que será buscada.
		 * @return <b>TRUE</b> caso a chave tenha sido encontrada, e <b>FALSE</b> para caso a chave não exista na página.
		 */
		bool hasKey(int value);

		/**
		 * @brief Verifica se a página está vazio.
		 * @return TRUE para vazio, FALSE para não vazio.
		 */
		bool isEmpty();

		/**
		 * @brief Verifica se a página é uma folha.
		 * @details Verifica se a página não tem filhos.
		 * @return TRUE se for folha, FALSE se tiver filhos.
		 */
		bool isLeaf();

		/**
		 * @brief Método que libera os recuros da página e filhos.
		 * @details Libera os recuros e limpa todas as chaves página e seus filhos, deixando-a vazia.
		 */
		void clear();

		/**
		 * @brief Conta quantas chaves existem na página.
		 * @return Total de chaves.
		 */
		unsigned int countKeys();

		/**
		 * @brief Conta quantos filhos existem na página.
		 * @return Total de filhos.
		 */
		unsigned int countBranches();
		
		/**
		 * @brief Divide a página em duas sub-páginas, onde na página quebrada resta apenas a chave pivô.
		 * @param unsigned int Índice da posição da chave que será o pivô.
		 */
		void split(unsigned int pivot);

		/**
		 * @brief Imprime a lista de chaves da página.
		 */
		void printList();

		/**
		 * @brief Percorre chave por chave imprimindo toda a página e suas filhas.
		 * @param page Referência da página.
		 * @param spaces Quantidades de espaços para recuo para direita.
		 */
		static void printPage(BTreePage *page, int spaces);

	};
}

#endif