/*
	Edwino Stein - 1201324411
*/

#if !defined  _COMMON_CONSOLE
#define _COMMON_CONSOLE

#if defined WIN32
	#include <windows.h>
#endif

namespace common {

	/**
	 * @brief Inteface com o console e o sistema operacional
	 * @details Classe singleton que fornece uma interface com o console e o sistema operacional.
	 */
	class _Console {

		private:
		/**
		 * @brief Contrutor padrão privado.
		 */
		_Console(){}

		/**
		 * @brief Contrutor de copia privado.
		 */
		_Console(_Console const&);

		/**
		 * @brief Operador de atribuição privado.
		 */
        void operator=(_Console const&);

		public:

		/**
		 * @brief Recupera a instância de _Console.
		 * @return Referência para a instância singleton de _Console.
		 */
		static _Console* getInstance();

		/**
		 * @brief Executa um comando do sistema operacional.
		 * @details Similar ao std::system() e system().
		 * 
		 * @param cmd String contendo o comando para ser executado.
		 */
        void exec(std::string cmd);

        /**
         * @brief Limpa a tela do console.
         */
        void clear();

        /**
         * @brief Pausa a execução do programa e aguarda um sinal do usuário para continuar.
         */
        void pause();

        /**
         * @brief Posiciona o cursor do console nas coordenadas informadas
         * @param x Coluna desejada 
         * @param y Linha desejada
         */
        void gotoXY(int x, int y);

	};

	typedef _Console *Console;
}
#endif
