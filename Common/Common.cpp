/*
	Edwino Stein - 1201324411
*/
	
#include "Common.hpp"

int main (){
	return app->main();
}


Application* Application::getInstance(){
    static Application *instance = new Application;
    return instance;
}


/*
	Aqui o preprocessador concatena os arquivos fontes para gerar um unico arquivo objeto
*/
#include "src/Random.cpp"
#include "src/Console.cpp"
#include "src/StdInput.cpp"
#include "src/StdOutput.cpp"
#include "src/Task.cpp"