#if !defined  _PARSER
#define _PARSER

#include "../Common/Common.hpp"
#include <fstream>
#include <queue>
#include <functional>

/**
 * @brief Classe responsavel por processar o um arquivo de instruções.
 * @details O arquivo é carregado e pre-processador, onde se busca enfileirar as intruções para que mais tarde sejam decodificadas e executadas.
 */
class Parser : public Object{

protected:

	/**
	 * @brief Expressção regular para o formato básico de uma instrução.
	 */
	static const String basicFormat;

	/**
	 * @brief Expressção regular para o formato genérico de uma instrução.
	 */
	static const String generalFormat;

	/**
	 * @brief Expressção regular para o formato de uma instrução de percurso.
	 */
	static const String percurseFormat;

	/**
	 * @brief Expressção regular para o formato de uma instrução de tipo.
	 */
	static const String typeFormat;

	/**
	 * @brief Expressção regular para o formato de uma instrução de percurso.
	 */
	static const String typesFormat;

	/**
	 * @brief Expressção regular para o formato de um número inteiro.
	 */
	static const String intFormat;

	/**
	 * @brief Nome do arquivo que será processado.
	 */
	String filename;

	/**
	 * @brief Handle do arquivo que será processado.
	 */
	std::ifstream handleFile;

	/**
	 * @brief Flag que indica que o arquivo existe e é acessivel.
	 */
	bool fileGood;

	/**
	 * @brief Fila de instruições encontradas no arquivo processado.
	 */
	std::queue<String> instructionsQueue;

	/**
	 * @brief Verifica se o arquivo existe.
	 * 
	 * @param filename Nome do arquivo.
	 * @return <b>TRUE</b> caso o arquivo exista, e <b>FALSE</b> para caso não exista.
	 */
	static bool fileExists(String filename);

	/**
	 * @brief Abre o arquivo que será processado.
	 * @return <b>TRUE</b> caso o arquivo abriu, e <b>FALSE</b> para caso de falha.
	 */
	bool openFile();

	/**
	 * @brief Fecha o arquivo.
	 */
	void closeFile();

	/**
	 * @brief Percorre cada linha do arquivo.
	 * @details Percorre todo o arquivo executando a função anônima para cada linha.
	 * O formato da função deve ser void(String, unsigned int).
	 * 
	 * @param handle Função anônima que será executada para cada linha do arquivo.
	 */
	void eachFileLines(std::function<void (String, unsigned int)> handle);

	/**
	 * @brief Verifica se o input está em algum formado de intrução.

	 * @param input String que será verificada.
	 * @return <b>TRUE</b> caso o input seja reconhecido como intrução, e <b>FALSE</b> para caso de não seja reconhecido.
	 */
	bool isInstruction(String input);

	/**
	 * @brief Adiciona a instrução a fila de instruções.
	 * @param input String da instrução que será enfileirada.
	 */
	void addInstruction(String input);

public:

	/**
	 * @brief Struct de uma instrução decodificada. 
	 */
	struct Instruction{

		/**
		 * @brief Tipo de instrução
		 */
		char type;

		/**
		 * @brief Parâmetro da instrução
		 */
		int param;

		/**
		 * @brief Parâmetro extra da instrução
		 */
		int extraParam;

		/**
		 * @brief String original do comando.
		 */
		String original;
	};

	/**
	 * @brief Contrutor padrão.
	 * @param String Nome do arquivo.
	 */
	Parser(String filename);

	/**
	 * @brief Carrega e pre-processa o arquivo.
	 * @details Percorre o arquivo procurando instruções e gera erros, caso um comando não seja reconhecido.
	 * @return <b>TRUE</b> caso o o arquivo tenha sido carregado com sucesso, e <b>FALSE</b> para caso de falha.
	 */
	bool load();

	/**
	 * @brief Pega e decodifica a proxima instrução da fila.
	 * @param next Objeto que guardará a instrução decodificada.
	 * @return <b>TRUE</b> caso exista instrução na fila, e <b>FALSE</b> para se a fila estiver vazia.
	 */
	bool getNextInstruction(Instruction& next);

	/**
	 * @brief Conta quantas intruções existem na fila.
	 * @return Total de instruções enfileiradas.
	 */
	unsigned int countInstructions();

	/**
	 * @brief Retorna o nome do arquivo que será processado.
	 * @return Nome do arquivo.
	 */
	String getFilename();
};

#endif