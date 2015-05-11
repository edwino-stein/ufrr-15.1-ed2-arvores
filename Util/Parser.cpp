/*
	Edwino Stein - 1201324411
*/

/* *************************************************************** */
/* ********************* Implementação Parser ******************** */
/* *************************************************************** */

#include "Parser.hpp"
#include <sys/stat.h>
#include <regex>

/* ******************* CONSTANTES ******************* */

//Formato basico para ser uma instrução
const String Parser::basicFormat = "([a-zA-Z])+((\\s)?(\\+|-)?(\\d)+)+";

//Formato genérico de uma instrução
const String Parser::generalFormat = "(i|b|r|I|B|R)(\\s)?(\\+|-)?(\\d)+";

//Formato espeficio de uma instrução de percurso
const String Parser::percurseFormat = "(p|P)(\\s)?([0-2]|10)$";
// const String Parser::percurseFormat = "p(\\s)?(0|1|2)";

//Formato espeficio de uma instrução de tipo
const String Parser::typeFormat = "(t|T)(\\s)?(0|1|2)((\\s)([1-9]\\d*)+)?";

//Lista de todas as intruções suportatas
const String Parser::typesFormat = "(t|i|b|r|p|T|I|B|R|P)";

//Forma para números inteiros
const String Parser::intFormat = "(\\+|-)?(\\d)+";

/* ******************* CONSTRUTORES E DESTRUTORES ******************* */

Parser::Parser(String filename) : filename(filename){
	//Verifica se o arquivo existe
	this->fileGood = Parser::fileExists(this->filename);
}

/* ******************* ARQUIVO ******************* */

/* Verifica se o arquivo existe */
bool Parser::fileExists(String filename){
	struct stat buffer;   
	return (stat(filename.c_str(), &buffer) == 0); 
}

/* Abre o arquivo */
bool Parser::openFile(){

	//Verifica se o arquivo está bom para trabalhar
	if(!this->fileGood){
		out->put(" * Erro: O arquivo não existe ou é inválido!", true);
		return false;
	}

	//Abre o arquivo
	this->handleFile.open(this->filename);

	//Verifica se o arquivo realmente abriu
	if(!handleFile.is_open()){
		out->put(" * Erro: O arquivo não existe ou é inválido!");
		return false;
	}

	return true;
}

/* Fecha o arquivo */
void Parser::closeFile(){
	if(this->handleFile.is_open()) this->handleFile.close();
}

/* Percorre linha por linha no arquivo */
void Parser::eachFileLines(std::function<void (String, unsigned int)> handle){

	if(!this->handleFile.is_open())
		return;

	String line;
	unsigned int countLines = 0;

	while(getline(this->handleFile, line))
		handle(line, ++countLines);
}

/* ******************* INSTURÇÕES ******************* */

//Verifica se a string está no formato de uma instrução */
bool Parser::isInstruction(String input){
	
	//Inicializa as expressões regulares	
	std::regex generalFormat(Parser::generalFormat);
	std::regex percurseFormat(Parser::percurseFormat);
	std::regex typeFormat(Parser::typeFormat);

	//Se é generica
	if(std::regex_match(input, generalFormat))
		return true;

	//Se for para percurso
	else if(std::regex_match(input, percurseFormat))
		return true;

	//Se for para tipo
	else if(std::regex_match(input, typeFormat))
		return true;

	return false;
}

/* Adiciona a instrução a fila */
void Parser::addInstruction(String input){
	this->instructionsQueue.push(input);
}
	
/* Pega a proxima instrução da fila */
bool Parser::getNextInstruction(Instruction& next){

	if(this->instructionsQueue.empty())
		return false;

	next.original = this->instructionsQueue.front();
	this->instructionsQueue.pop();

	String temp;
	std::smatch matched;
	std::regex type(Parser::typesFormat);
	std::regex param(Parser::intFormat);

	//Pega o tipo da instrução
	std::regex_search(next.original, matched, type);
	temp = matched[0];
	next.type = temp[0];

	//Pega o parâmetro
	std::regex_search(next.original, matched, param);
	temp = matched[0];
	next.param = atoi(temp.c_str());

	//Se tiver um parâmetro extra
	temp = matched.suffix().str();
	if(std::regex_search(temp, matched, param)){
		temp = matched[0];
		next.extraParam = atoi(temp.c_str());
	}

	//Se não existir parâmetro extra
	else{
		next.extraParam = (-1);
	}

	return true;
}

/* Conta as instruções enfileiradas */
unsigned int Parser::countInstructions(){
	return this->instructionsQueue.size();
}

/* Carrega todas as intruções do arquivo */
bool Parser::load(){

	if(!this->openFile())
		return false;

	Parser *me = this;
	bool error = false;

	//Para cada linha do arquivo
	this->eachFileLines([&me, &error](String line, unsigned int countLines){

		//Se tiver vazia, ignora
		if(line.empty()){
			out->printf(" * Alerta: Linha %d está vazia, ignorando...\n", countLines);
			return;
		}

		std::smatch matched;
		std::regex basicFormat(Parser::basicFormat);
		bool found = false;
		
		//Procura por possiveis instruções na linha
		while(std::regex_search(line, matched, basicFormat)){

			found = true;

			//Se for uma instrução válida, guarda na fila, se não, gera um erro
			if(!me->isInstruction(matched[0])){
				out ->printf(" * Erro: O comando na linha %d não foi reconhecido: \"", countLines)
					->put(matched[0])->put("\"", true);
				error = true;
			}else{
				me->addInstruction(matched[0]);
			}

			//Pega o resto da linha
			line = matched.suffix().str();
		}

		//Se não achou nada parecido com uma instrução
		if(!found){
			out->printf(" * Erro: Nenhum comando foi reconhecido na linha %d:\"%s\"\n", countLines, line.c_str());
			error = true;
		}
	});

	this->closeFile();

	return !error;
}


String Parser::getFilename(){
	return this->filename;
}
