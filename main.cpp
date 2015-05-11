/*
	Edwino Stein - 1201324411
*/
/* ************************************************************* */
/* ********************* Programa Principal ******************** */
/* ************************************************************* */

#include "Common/Common.hpp"
#include "Util/Parser.hpp"
#include "Tree/Tree.hpp"

int Application::main(){

	//Se não foi passado nenhum arquivo, encerra o programa
	if(app->countArgs() <= 1){
		out->put("Erro: Não foram passados arquivos para serem processados", true);
		return 1;
	}

	//Carrega todos os arquivos
	std::vector<Parser *> files;
	bool error = false;
	for(int i = 1; i < app->countArgs(); i++){
		
		//Cria um parser e carrega o arquivo
		Parser *p = new Parser(app->getArg(i));
		out->put("Carregando arquivo \"")->put(p->getFilename())->put("\"...", true);
		if(!p->load()){

			out ->put(" *** Houve erros enquanto carregava o arquivo \"")
				->put(p->getFilename())
				->put("\" ***\n", true);

			error = true;
		}

		//Adiciona ao final do vetor
		files.push_back(p);
	}

	//Se ocorreu algum erro durante o carregamento, encerra o programa
	if(error){
		for(int i = 0; i < files.size(); i++){
			delete files[i];
			files[i] = NULL;
		}
		return 1;
	}

	//Espera confirmação do usuário
	out->put(" * Todos os arquivo foram carregados, ");
	console->pause();

	tree::Tree *arvore = NULL;
	tree::collection historico;
	Parser::Instruction instruction;

	//Executa os arquivos
	for(int i = 0; i < files.size(); i++){

		console->clear();
		out->put(" * Executando \"")->put(files[i]->getFilename())->put("\"...", true);

		//Busca a próxima instrução e executa
		while(files[i]->getNextInstruction(instruction)){

			out->putNewLine()->put("Comando: ")->put(instruction.original, true);

			//Se não existe uma árvore instanciada, ignora o comando
			if(arvore == NULL && instruction.type != 'T' && instruction.type != 't'){
				out->put(" * Alerta: Nenhum tipo de árvore foi especificado, ignorando comando \"")
					->put(instruction.original)->put("\"...", true);
				continue;
			}


			//Verifica o que o comando deve fazer
			switch(instruction.type){

				//Cria uma nova árvore
				case 'T':
				case 't':

					//Se já tem uma árvore, subistitui por uma nova
					if(arvore != NULL){
						delete arvore;
						arvore = NULL;
						out->put("Subistituindo a árvore por uma ");
					}

					else{
						out->put("Criando uma árvore ");
					}

					//Binária
					if(instruction.param == 0){
						out->put("Binária de Busca...", true);
						arvore = new tree::BinaryTree();
						continue;
					}

					//AVL
					if(instruction.param == 1){
						out->put("Binária de Busca Auto Balanceável (AVL)...", true);
						arvore = new tree::AvlTree();
						continue;
					}

					//B
					if(instruction.param == 2){
						out->put("B...", true);

						//Caso não tenha sido informado a ordem
						if(instruction.extraParam <= 0){
							out->put(" * Alerta: Ordem indefinida, utilizando ordem 1...", true);
							instruction.extraParam = 1;
						}

						arvore = new tree::BTree(instruction.extraParam);
						continue;
					}

					//Termina o programa caso não tenha sido especificado o tipo
					out->putNewLine()->put("**** Erro: Tipo de árvore inválido! ****", true);
					for(int j = 0; j < files.size(); j++){
						delete files[j];
						files[j] = NULL;
					}
					return 1;
				break;

				//Insere um valor na árvore
				case 'I':
				case 'i':
					out->put("Inserindo o valor \"")->put(instruction.param)->put("\" na árvore...", true);
					arvore->insert(instruction.param);
				break;

				//Busca um valor na árvore
				case 'B':
				case 'b':
					out->put("Buscando o valor \"")->put(instruction.param)->put("\" na árvore...", true);
					historico.clear();
					
					if(arvore->search(instruction.param, historico)){ 

						//Imprime lista de valores que foram consultados
						out->put("A busca percorreu todos os seguintes valores: ", true);
						for(int j = 0; j < historico.size(); j++){
							out->put(historico[j]);
							if(j < historico.size() - 1)
								out->put(", ");
						}
						out->putNewLine();
					}

					else
						out->put("O valor \"")->put(instruction.param)->put("\" não foi encontrado na árvore!", true);

					continue;

				break;
				
				//Remove um valor da árvore
				case 'R':
				case 'r':
					out->put("Removendo o valor \"")->put(instruction.param)->put("\" na árvore...", true);

					if(arvore->remove(instruction.param))
						out->put("O valor \"")->put(instruction.param)->put("\" foi removido da árvore!", true);
					else
						out->put("O valor \"")->put(instruction.param)->put("\" não foi encontrado na árvore para remoção!", true);

				break;

				//Percorre a árvore
				case 'P':
				case 'p':
					out->put("Percorrendo a árvore pelo tipo ");

					//Pré-ordem
					if(instruction.param == 0){

						out->put("Pré-ordem...", true);
						arvore->each([](int valor){
							out->put('(')->put(valor)->put(") ");
						}, tree::RED_ORDER);
						out->putNewLine();

						continue;
					}

					//Em-ordem
					if(instruction.param == 1){
						out->put("Em-ordem...", true);

						arvore->each([](int valor){
							out->put('(')->put(valor)->put(") ");
						}, tree::ERD_ORDER);
						out->putNewLine();

						continue;
					}

					//Pós-ordem
					if(instruction.param == 2){
						out->put("Pós-ordem...", true);

						arvore->each([](int valor){
							out->put('(')->put(valor)->put(") ");
						}, tree::EDR_ORDER);
						out->putNewLine();

						continue;
					}

					//Termina o programa caso não tenha sido especificado o tipo de percurso
					out->putNewLine()->put("**** Erro: Tipo de percurso inválido! ****", true);
					for(int j = 0; j < files.size(); j++){
						delete files[j];
						files[j] = NULL;
					}
					return 1;

				break;

				//Termina o programa caso o comando seja inválido
				default:
					out->putNewLine()->put("**** Erro: Comando inválido! ****", true);
					for(int j = 0; j < files.size(); j++){
						delete files[j];
						files[j] = NULL;
					}
					return 1;
			}

			//Exibe a árvore
			if(arvore != NULL && !arvore->isEmpty()){
				out->put(" * Como a árvore se encontra:", true);
				arvore->print();
			}

			else
				out->put(" * Alerta: A árvore está vazia!", true);
			
		}

		//Libera memória da árvore ao terminar de executar o arquivo
		if(arvore != NULL){
			delete arvore;
			arvore = NULL;
		}

		//Espera confirmação do usuário
		out->put("\n * Execução do arquivo chegou ao fim. ");
		console->pause();
	}

	//Libera memória dos parseadores
	for(int j = 0; j < files.size(); j++){
		delete files[j];
		files[j] = NULL;
	}

	return 0;
}