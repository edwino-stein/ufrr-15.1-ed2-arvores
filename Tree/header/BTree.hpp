#if !defined  _TREE_B
#define _TREE_B

#include "TreeInterface.hpp"
#include "BTreePage.hpp"

namespace tree{

	/**
	 * @brief Árvore B para números inteiros.
	 * 
	 * @version B Mark IV
	 */
	class BTree : public Tree{

	protected:

		/**
		 * @brief Ordem (m) da árvore.
		 */
		const unsigned int order;

		/**
		 * @brief Número maximo de chaves que uma página pode ter (2*m).
		 */
		const unsigned int maxKeys;

		/**
		 * @brief Número maximo de filhos que uma página pode ter (2*m + 1).
		 */
		const unsigned int maxBranches;

		/**
		 * @brief Referência para raiz da árvore
		 */
		BTreePage *root;

		/**
		 * @brief Insere um valor na árvore
		 * @details Método recursivo da inserção, pois percorre toda a árvore procurando uma folha que o valor pode ser inserido.
		 * A inserção de uma nova chave deve respeitar as regras de uma árvore B:
		 * <ul>
		 * 	<li>Valores menores ficam a esquerda;</li>
		 * 	<li>Valores maiores ficam a direita;</li>
		 * 	<li>Não se permite valores repetidos;</li>
		 * 	<li>As páginas não podem ter mais que 2*m chaves;</li>
		 * 	<li>As páginas não podem ter menos que m chaves;</li>
		 * 	<li>A raiz pode ter no mínimo 1 chave;</li>
		 * </ul> 
		 * 
		 * @param value Valor que será inserido.
		 * @param page Referência da página pai.
		 * 
		 * @return <b>TRUE</b> caso o valor tenha sido inserido, e <b>FALSE</b> para caso o valor já exista na árvore.
		 */
		bool insert(int value, BTreePage *page);

		/**
		 * @brief Procura e caso ache, remove o valor da árvore.
		 * @details Método recursivo que realiza a remoção de uma chave de uma página da árvore.
		 * 	
		 * @param value Valor que será procurado e removido.
		 * @param page Referência da página pai.
		 * 
		 * @return <b>TRUE</b> caso o valor tenha sido removido, e <b>FALSE</b> para caso não tenha encontrado o valor.
		 */
		bool remove(int value, BTreePage *page);

		/**
		 * @brief Procura um valor na árvore.
		 * @details Método recursivo que realiza uma busca de uma chave da árvore.
		 * 
		 * @param value Valor que será procurado.
		 * @param history Vetor contendo os valores dos nós consultados.
		 * @param page Referência da página pai.
		 * 
		 * @return <b>TRUE</b> caso o valor tenha sido encontrado, e <b>FALSE</b> para caso não tenha encontrado o valor.
		 */
		bool search(int value, collection& history, BTreePage *page);

		/**
		 * @brief Busca o valor do sucessor de um valor da página.
		 * @details Retorna o primeiro valor da página mais a esquerda da página da direita do valor.
		 * 
		 * @param value Valor da página.
		 * @param page Referência da página.
		 * @return Valor do sucessor.
		 */
		int getSucessor(int value, BTreePage *page);

		/**
		 * @brief Redistribui chaves entre páginas.
		 * @details Método responsavel por realizar distribuição entre páginas para manter o equilíbrio da árvore após uma remoção.
		 * 
		 * @param unsigned int Índice da página filho que está desequilibrada.
		 * @param page Referência da página pai.
		 */
		void redistribute(unsigned int index, BTreePage *page);

	public:

		/**
		 * @brief Contrutor padrão.
		 * @details Cria uma árvore vazia.
		 * 
		 * @param unsigned int Ordem (m) da árvore.
		 */
		BTree(unsigned int order);

		/**
		 * @brief Contrutor de inicialização.
		 * @details Cria uma árvore inicializando com um valor.
		 * 
		 * @param unsigned int Ordem (m) da árvore.
		 * @param value Valor da raiz.
		 */
		BTree(unsigned int order, int value);

		/**
		 * @brief Destrutor padrão
		 */
		~BTree();

		/**
		 * @brief Insere um valor na árvore
		 * @details Método público da inserção, chama o método recusivo passando a raiz como parâmetro.
		 * A inserção de uma nova chave deve respeitar as regras de uma árvore B:
		 * <ul>
		 * 	<li>Valores menores ficam a esquerda;</li>
		 * 	<li>Valores maiores ficam a direita;</li>
		 * 	<li>Não se permite valores repetidos;</li>
		 * 	<li>As páginas não podem ter mais que 2*m chaves;</li>
		 * 	<li>As páginas não podem ter menos que m chaves;</li>
		 * 	<li>A raiz pode ter no mínimo 1 chave;</li>
		 * </ul> 
		 * 
		 * @param value Valor que será inserido.
		 * 
		 * @return <b>TRUE</b> caso o valor tenha sido inserido, e <b>FALSE</b> para caso o valor já exista na árvore.
		 */
		BTree *insert(int value);

		/**
		 * @brief Procura e caso ache, remove o valor da árvore.
		 * @details Método público que realiza a remoção de uma chave de uma página da árvore.
		 * 	
		 * @param value Valor que será procurado e removido.
		 * 
		 * @return <b>TRUE</b> caso o valor tenha sido removido, e <b>FALSE</b> para caso não tenha encontrado o valor.
		 */
		bool remove(int value);

		/**
		 * @brief Procura um valor na árvore.
		 * @details Método público que realiza uma busca de uma chave da árvore.
		 * 
		 * @param value Valor que será procurado.
		 * @param history Vetor contendo os valores consultados.
		 * 
		 * @return <b>TRUE</b> caso o valor tenha sido encontrado, e <b>FALSE</b> para caso não tenha encontrado o valor.
		 */
		bool search(int value, collection& history);

		/**
		 * @brief Percorre cada elemento da árvore.
		 * @details Percorre a árvore toda pela ordem desejada, passando o valor de cada página para a função anônima definida.
		 * A função anônima deve ser no formado <b>void (int)</b>. Exemplo de código:
		 * @code
		 * 	BTree arvore;
		 * 
		 * 	//...
		 *
		 * 	int soma = 0;
		 * 
		 * 	arvore.each([&soma](int valorDoNo){
		 * 		soma += valorDoNo;
		 * 	});
		 * 
		 * @endcode
		 * 
		 * @param handle Função anônima que será executada para cada chave.
		 * @param order Tipo de ordem que a a árvore será percorrida:
		 * <ul>
		 * 	<li><b>tree::RED_ORDER</b>: Pré-Ordem (Raiz-Esquerda-Direita)</li>
		 * 	<li><b>tree::ERD_ORDER</b>: Em-Ordem (Esquerda-Raiz-Direita)</li>
		 * 	<li><b>tree::EDR_ORDER</b>: Pós-Ordem (Esquerda-Direita-Raiz)</li>
		 * </ul>
		 */
		void each(std::function<void(int)> handle, char order = tree::RED_ORDER);

		/**
		 * @brief Verifica árvore está vazia.
		 * @return TRUE para vazio, FALSE para não vazio.
		 */
		bool isEmpty();

		/**
		 * @brief Método que libera os recuros da árvore e subárvores.
		 * @details Libera os recuros e limpa todos as páginas da árvore, deixando-a vazia.
		 */
		void clear();

		/**
		 * @brief Calcula a altura da árvore.
		 * @details Calcula e retorna a altura da árvore.
		 * @return Altura da árvore.
		 */
		int height();

		/**
		 * @brief Percorre página por página imprimindo todas as chaves da árvore.
		 */
		void print();

	};
}

#endif