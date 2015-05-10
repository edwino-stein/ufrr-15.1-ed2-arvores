#if !defined  _PARSER
#define _PARSER

#include "../Common/Common.hpp"
#include <fstream>
#include <queue>
#include <functional>

/**
 * @todo: Documentar
 */
class Parser : public Object{

protected:

	static const String basicFormat;
	static const String generalFormat;
	static const String percurseFormat;
	static const String typeFormat;
	static const String typesFormat;
	static const String intFormat;

	String fileName;
	String lastError;
	std::ifstream handleFile;
	bool fileGood;
	std::queue<String> instructionsQueue;

	static bool fileExists(String fileName);
	bool openFile();
	void closeFile();
	void eachFileLines(std::function<void (String, unsigned int)> handle);

	bool isInstruction(String input);
	void addInstruction(String input);

public:

	struct Instruction{
		char type;
		int param;
		int extraParam;
		String original;
	};

	Parser(String fileName);
	bool load();
	bool getNextInstruction(Instruction& next);
	unsigned int countInstructions();
};

#endif