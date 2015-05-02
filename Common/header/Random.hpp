/*
    Edwino Stein - 1201324411
*/

#if !defined  _COMMON_RANDOM
#define _COMMON_RANDOM

#include <random>

namespace common {


    /**
     * @brief Classe singleton responsavel por gerar valores aleatórios.
     */
	class _Random {
        
		private:

        /**
         * @brief Contrutor padrão privado.
         */
		_Random(){}

        /**
         * @brief Contrutor de copia privado.
         */
		_Random(_Random const&);

        /**
         * @brief Operador de atribuição privado.
         */
        void operator=(_Random const&);

        /**
         * @brief Instância de um gerador Mersenne Twister 19937
         */
        std::mt19937 generator;

        /**
         * @brief Gera interios aleatórios.
         * @details Método responsável por gerar inteiros aleatoriamente utilizando o
         * gerador <b>Mersenne Twister 19937</b> dentro do intervalo informado. Similar ao rand().
         * 
         * @param min Menor valor possivel a ser gerado.
         * @param max Maior valor possivel a ser gerado.
         * 
         * @return Valor gerado aleatoriamente
         */
        int rand(int min, int max);

		public:

        /**
         * @brief Recupera a instância de _Random.
         * @return Referência para a instância singleton de _Random.
         */
        static _Random* getInstance();

        /**
         * @brief Gera um número inteiro aleatoriamente.
         * @details Método responsável por gerar valores inteiros aleatoriamente dentro do intervalo informado.
         * 
         * @param min Menor valor inteiro possivel a ser gerado.
         * @param max Maior valor inteiro possivel a ser gerado.
         * 
         * @return Valor inteiro gerado aleatoriamente.
         */
        int getInt(int max = 99, int min = 0);

        /**
         * @brief Gera um caractere aleatoriamente
         * @details Método responsável por gerar um caractere ASCII aleatoriamente.
         * 
         * @param printableOnly Define que serão gerados apenas caracteres imprimiveis (do 33 ao 126).
         * @return Caractere gerado aleatoriamente.
         */
        char getChar(bool printableOnly = true);

        /**
         * @brief Gera um valor double aleatoriamente
         * @details Método responsável por gerar valores double aleatoriamente.
         * Os valores gerados sempre serão positivos e proximos de zero.
         * 
         * @return Valor double gerado aleatoriamente.
         */
        double getDouble();

        /**
         * @brief Gera um valor booleano aleatoriamente
         * @details Método responsável por gerar valores booleano aleatoriamente.
         * As chances sempre serão de 50% para os dois valores possiveis (TRUE ou FALSE).
         * 
         * @return Valor booleano gerado aleatoriamente.
         */
        bool getBool();

    };

    typedef _Random* Random;
}
#endif
