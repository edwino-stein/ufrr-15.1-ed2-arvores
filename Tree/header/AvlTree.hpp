#if !defined  _TREE_AVL
#define _TREE_AVL

#include "BinaryTree.hpp"

namespace tree{

	/**
	 * @brief Árvore binaria de Busca auto balanceável (AVL) para números inteiros.
	 * @version Avl Mark II
	 */

	class AvlTree : public BinaryTree{

	protected:

		/**
		 * @brief Define ou altera o valor do nó.
		 * 
		 * @param value Valor que será definido para o nó.
		 * @return Referência do nó atual.
		 */
		AvlTree *setValue(int value);

		/**
		 * @brief Define ou altera o nó da esquerda.
		 * 
		 * @param node Nó que será o filho da esquerda.
		 * @return Referência do nó atual.
		 */
		AvlTree *setLeft(BinaryTree *node);

		/**
		 * @brief Define ou altera o nó da direita.
		 * 
		 * @param node Nó que será o filho da direita.
		 * @return Referência do nó atual.
		 */
		AvlTree *setRight(BinaryTree *node);


		/**
		 * @brief Calcula o fator de balanceamento.
		 * @details O fator de balanceamento é o parâmetro utilizado para definir se a árvore está ou não balanceada.
		 * 
		 * O calculo é realizado da seguinte forma:
		 * 	<b>fb</b> = <i>altura_da_subárvore_da_direita</i> -- <i>altura_da_subárvore_da_esquerda</i>.
		 * 
		 * @return Fator de balanceamento segue o seguinte padrão:
		 * <ul>
		 * 		<li>Valores no intervalo -1 <= <b>fb</b> <= 1, significa que a árvore está balancada.</li>
		 * 		<li>Valores nos intervalos -2 <= <b>fb</b> ou <b>fb</b> fb >= 2, significa que a árvore não está balancada.</li>
		 * 		<li>Valores negativos signifca que a árvore está desbalanceada para esquerda.</li>
		 * 		<li>Valores positivos signifca que a árvore está desbalanceada para direita.</li>
		 * 		<li>Valor zero signifca que a árvore está perfeitamente balanceada.</li>
		 * </ul>
		 */
		int getBalanceFactor();

		/**
		 * @brief Balanceia a árvore.
		 * @details Percorre toda a árvore realiznado o balanceamento. 
		 */
		void doBalance();

		/**
		 * @brief Rotaciona o nó para direita.
		 * @details Realiza uma rodação simples do nó no sentido da esquerda para a diteira.
		 */
		void rotationToRight();

		/**
		 * @brief Rotaciona o nó para esquerda.
		 * @details Realiza uma rodação simples do nó no sentido da diteira para a esquerda.
		 */
		void rotationToLeft();

		/**
		 * @brief Imprime apenas o valor do nó.
		 * @details Formato: (<valor>, <fat_balanceamento>)
		 */
		void printNodeValue();

	public:

		/**
		 * @brief Contrutor padrão.
		 * @details Cria uma árvore vazia.
		 */
		AvlTree();

		/**
		 * @brief Contrutor de inicialização.
		 * @details Cria uma árvore inicializando com um valor
		 * 
		 * @param value Valor da raiz.
		 */
		AvlTree(int value);

		/**
		 * @brief Destrutor padrão
		 */
		~AvlTree();

		/**
		 * @brief Insere um novo valor na árvore.
		 * @details A inserção de um novo valor respeita as regras de uma árvore binária de busca:
		 * <ul>
		 * 	<li>Valores menores ficam a esquerda;</li>
		 * 	<li>Valores maiores ficam a direita;</li>
		 * 	<li>Não se permite valores repetidos;</li>
		 * </ul>
		 * 
		 * A cada novo nó adicionado, a árvore se auto balanceia.
		 * 
		 * @param value Valor que será inserido.
		 * @return Referência do novo nó.
		 */	
		AvlTree *insert(int value);

		/**
		 * @brief Procura e caso ache, remove o valor da árvore.
		 * @details A cada novo nó adicionado, a árvore se auto balanceia.
		 * 
		 * @param value Valor que será procurado e removido.
		 * @return <b>TRUE</b> caso o valor tenha sido removido, e <b>FALSE</b> para caso não tenha encontrado o valor.
		 */
		bool remove(int value);

		/**
		 * @brief Retorna a subárvore da esquerda.
		 * @return Referência do nó da subárvore da esquerda. Caso não exista, retorna um nó vazio.
		 */
		AvlTree *getLeft();

		/**
		 * @brief Retorna a subárvore da direita.
		 * @return Referência do nó da subárvore da direita. Caso não exista, retorna um nó vazio.
		 */
		AvlTree *getRight();

	};
}

#endif