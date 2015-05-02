/*
	Edwino Stein - 1201324411
*/

#if !defined  _COMMON_APPLICATION
#define _COMMON_APPLICATION

namespace common {

	/**
	 * @brief Classe base da aplicação.
	 * @details Para que a aplicação rode, é necessario realizar a implementação do metodo main() em algum aquivo do projeito contento o código do programa.
	 * 
	 * @code
	 * 
	 * int Application::main(){
	 * 
	 * 		//O código do programa...
	 * 		
	 * 		return 0;
	 * }
	 * 
	 * @endcode
	 */
	class Application{

		private:

		/**
         * @brief Contrutor padrão privado.
         */
		Application(){}

		/**
         * @brief Contrutor de copia privado.
         */
		Application(Application const&);

		/**
         * @brief Operador de atribuição privado.
         */
        void operator=(Application const&);

		public:

		/**
         * @brief Recupera a instância de Application.
         * @return Referência para a instância singleton de Application.
         */
		static Application* getInstance();


		/**
		 * @brief Entrypoint do programa.
		 * @details Este método deve ser implementado com o código a ser executado na aplicação;
		 * @return Resultado da execução do programa que será retornado ao sistema operacional.
		 */
        static int main();
	};
}

#endif
