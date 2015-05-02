/*
	Edwino Stein - 1201324411
*/

#if !defined _COMMON_TASK
#define _COMMON_TASK

#include <functional>
#include <thread>
#include <chrono>

namespace common {

	static const char TIME_UNIT_NANOSECONDS 	= 	0;
	static const char TIME_UNIT_MICROSECONDS 	= 	1;
	static const char TIME_UNIT_MILISECONDS 	=	2;
	static const char TIME_UNIT_SECONDS 		=	3;
	static const char TIME_UNIT_MINUTES 		=	4;
	static const char TIME_UNIT_HOURS 			= 	5;

	/**
	 * @brief Coloca a thread atual para dormir durante um tempo.
	 * @param t Tempo
	 * @param unit Unidade de tempo.
	 */
	void sleep(unsigned int t, char unit = TIME_UNIT_MILISECONDS);

	
	typedef std::function<void(void)> taskHandle;


	/**
	 * @brief Classe que encapsula uma tarefa síncrona através de uma função lambda.
	 * @details Exemplo:
	 * 
	 * @code
	 * 
	 * int total = 0;
	 * 
	 * Task soma10([&total](){
	 * 		total += 10;
	 * });
	 * 
	 * total = 5;
	 * 
	 * //Incrementa 10 ao total (total == 15)
	 * soma10();
	 * 
	 * //Incrementa mais 10 ao total (total == 25)
	 * soma10();
	 * 
	 * @endcode
	 */
	class Task{

	protected:

		/**
		 * @brief Handle da função lambda.
		 */
		taskHandle handle;

	public:

		/**
		 * @brief Construtor
		 * @details Define a função que a tarefa irá executar.
		 * 
		 * @param handle Função lambda que será executada.
		 */
		Task(taskHandle handle) : handle(handle) {}

		/**
		 * @brief Operador() de execução.
		 * @details Executa a tarefa.
		 */
		void operator()(){ this->run(); }

		/**
		 * @brief Executa a tarefa.
		 */
		void run();

	};

	/**
	 * @brief Classe que encapsula uma thread como tarefa assíncrona através de uma função lambda.
	 * @details Exemplo:
	 * 
	 * @code
	 * 
	 * int total = 0;
	 * bool loopInfinito = true;
	 * 
	 * AsyncTask executaDepois([&loopInfinito]{
	 * 		sleep(3, TIME_UNIT_SECONDS);
	 * 		loopInfinito = false;
	 * });
	 * 
	 * executaDepois();
	 * 
	 * while(loopInfinito){
	 * 		total++;
	 * }
	 * 
	 * executaDepois.join();
	 * 
	 * @endcode
	 * 
	 */

	class AsyncTask: public Task{

		protected:

		/**
		 * @brief Objeto thread que será executada.
		 */
		std::thread *pThread;

		/**
		 * @brief Ponto inicial para a execução da thread.
		 * @details Método utilizado para a inicialização da thread.
		 * 
		 * @param handle Função lambda que será executada pela thread.
		 */
		static void entryPoint(taskHandle handle);
		
		public:

		/**
		 * @brief Construtor
		 * @details Define a função que a thread irá executar.
		 * 
		 * @param handle Função lambda que será executada.
		 */
		AsyncTask(taskHandle handle) : Task(handle) {}

		/**
		 * @brief Destrutor.
		 * @details Libera os recuros da thread.
		 */
		~AsyncTask();

		/**
		 * @brief Operador() de execução.
		 * @details Executa a thread.
		 */
		void operator()(bool detachAfterInit = false){ this->run(detachAfterInit); }

		/**
		 * @brief Executa a thread
		 * @param detachAfterInit Desvincula a thread logo que for inicializada.
		 */
		void run(bool detachAfterInit = false);

		/**
		 * @brief Espera a thread terminar a execução
		 */
		void join();

		/**
		 * @brief Desvincula a thread 
		 * @details Permite que os recursos da thread sejam liberados ao final da execução do programa principal.
		 */
		void detach();

		/**
		 * @brief Verifica se a thread pode ser sincronizada.
		 */
		bool isJoinable();

	};

}
#endif