#if !defined  _TREE_BINARY
#define _TREE_BINARY

#include "TreeInterface.hpp"

namespace tree{

	/**
	 * @brief Árvore binaria de Busca para números inteiros.
	 * @version Bin Mark IV
	 */

	class BinaryTree : public Tree{

	protected:

		/**
		 * @brief Valor do nó.
		 * @details Ponteiro para o valor do nó, caso seja <b>NULL</b>, o nó está vazio.
		 */
		int *value;

		/**
		 * @brief Filho da esquerda.
		 */
		BinaryTree *left;

		/**
		 * @brief Filho da direita.
		 */
		BinaryTree *right;


		/**
		 * @brief Define ou altera o nó da esquerda.
		 * 
		 * @param node Nó que será o filho da esquerda.
		 * @return Referência do nó atual.
		 */
		virtual BinaryTree *setLeft(BinaryTree *node);

		/**
		 * @brief Define ou altera o nó da direita.
		 * 
		 * @param node Nó que será o filho da direita.
		 * @return Referência do nó atual.
		 */
		virtual BinaryTree *setRight(BinaryTree *node);

		/**
		 * @brief Define ou altera o valor do nó.
		 * 
		 * @param value Valor que será definido para o nó.
		 * @return Referência do nó atual.
		 */
		virtual BinaryTree *setValue(int value);

		/**
		 * @brief Conta quantos filhos o nó tem.
		 * @return Total de filhos.
		 */
		unsigned int countChildren();

		/**
		 * @brief Procura e caso ache, remove o valor da árvore.
		 * 
		 * @param value Valor que será procurado e removido.
		 * @param parent Referência do nó pai, caso seja <b>NULL</b>, o nó é a raiz.
		 * 
		 * @return <b>TRUE</b> caso o valor tenha sido removido, e <b>FALSE</b> para caso não tenha encontrado o valor.
		 */
		bool remove(int value, BinaryTree *parent);

		/**
		 * @brief Imprime apenas o valor do nó.
		 * @details Formato: (<valor>)
		 */
		virtual void printNodeValue();

		/**
		 * @brief Percorre nó por nó imprimindo toda a árvore.
		 * 
		 * @param spaces Quantidades de espaços para recuo para direita.
		 */
		void print(int spaces);

	public:

		/**
		 * @brief Contrutor padrão.
		 * @details Cria uma árvore vazia.
		 */
		BinaryTree();
		
		/**
		 * @brief Contrutor de inicialização.
		 * @details Cria uma árvore inicializando com um valor
		 * 
		 * @param value Valor da raiz.
		 */
		BinaryTree(int value);

		/**
		 * @brief Destrutor padrão
		 */
		virtual ~BinaryTree();


		/**
		 * @brief Insere um novo valor na árvore.
		 * @details A inserção de um novo valor respeita as regras de uma árvore binária de busca:
		 * <ul>
		 * 	<li>Valores menores ficam a esquerda;</li>
		 * 	<li>Valores maiores ficam a direita;</li>
		 * 	<li>Não se permite valores repetidos;</li>
		 * </ul>
		 * 
		 * @param value Valor que será inserido.
		 * @return Referência do novo nó.
		 */	
		virtual BinaryTree *insert(int value);

		/**
		 * @brief Procura e caso ache, remove o valor da árvore.
		 * 
		 * @param value Valor que será procurado e removido.
		 * @return <b>TRUE</b> caso o valor tenha sido removido, e <b>FALSE</b> para caso não tenha encontrado o valor.
		 */
		virtual bool remove(int value);

		/**
		 * @brief Procura um valor na árvore.
		 * 
		 * @param value Valor que será procurado.
		 * @param history Vetor contendo os valores dos nós consultados.
		 * 
		 * @return <b>TRUE</b> caso o valor tenha sido encontrado, e <b>FALSE</b> para caso não tenha encontrado o valor.
		 */
		bool search(int value, collection& history);

		/**
		 * @brief Percorre cada elemento da árvore.
		 * @details Percorre a árvore toda pela ordem desejada, passando o valor de cada nó para a função anônima definida.
		 * A função anônima deve ser no formado <b>void (int)</b>. Exemplo de código:
		 * @code
		 * 	BinaryTree arvore;
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
		 * @param handle Função anônima que será executada para cada nó
		 * @param order Tipo de ordem que a a árvore será percorrida:
		 * <ul>
		 * 	<li><b>tree::RED_ORDER</b>: Pré-Ordem (Raiz-Esquerda-Direita)</li>
		 * 	<li><b>tree::ERD_ORDER</b>: Em-Ordem (Esquerda-Raiz-Direita)</li>
		 * 	<li><b>tree::EDR_ORDER</b>: Pós-Ordem (Esquerda-Direita-Raiz)</li>
		 * </ul>
		 */
		void each(std::function<void(int)> handle, char order = tree::RED_ORDER);

		/**
		 * @brief Retorna a subárvore da esquerda.
		 * @return Referência do nó da subárvore da esquerda. Caso não exista, retorna um nó vazio.
		 */
		virtual BinaryTree *getLeft();

		/**
		 * @brief Retorna a subárvore da direita.
		 * @return Referência do nó da subárvore da direita. Caso não exista, retorna um nó vazio.
		 */
		virtual BinaryTree *getRight();

		/**
 		 * @brief Retorna o valor do nó.
 		 * @return Valor do nó, caso o nó seja vazio, retona <i>0</i>.
 		 */
		int getValue();

		/**
		 * @brief Retorna a subárvore contendo o sucessor do nó atual.
		 * @details Retorna o nó mais a esqueda da subárvore da direita.
		 * @return Referêncida do nó sucessor.
		 */
		BinaryTree *getSucessor();

		/**
		 * @brief Retorna a subárvore contendo o antecessor do nó atual.
		 * @details Retorna o nó mais a direita da subárvore da esqueda.
		 * @return Referêncida do nó antecessor.
		 */
		BinaryTree *getPredecessor();

		/**
		 * @brief Verifica se o nó é vazio.
		 * @return TRUE para vazio, FALSE para não vazio.
		 */
		bool isEmpty();

		/**
		 * @brief Verifica se o nó é uma folha.
		 * @details Verifica se o nó não tem filhos e se encontra nas extremidades da árvore.
		 * @return TRUE se for folha, FALSE se for um galho ou raiz com pelo menos um filho.
		 */
		bool isLeaf();

		/**
		 * @brief Método que libera os recuros da árvore e subárvores.
		 * @details Libera os recuros e limpa todos nos nós da árvore, deixando-a vazia.
		 */
		void clear();

		/**
		 * @brief Calcula a altura da árvore.
		 * @details Calcula e retorna o tamanho do maior caminho da árvore.
		 * @return Altura da árvore.
		 */
		int height();

		/**
		 * @brief Percorre nó por nó imprimindo toda a árvore.
		 */
		void print();

	};
}
#endif