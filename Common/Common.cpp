/*
	Edwino Stein - 1201324411
*/
	
#include "Common.hpp"

int main(int argc, char *argv[]){

	for(int i = 0; i < argc; i++)
		app->setArg(i, argv[i]);

	return app->main();
}

Application* Application::getInstance(){
    static Application *instance = new Application;
    return instance;
}

void Application::setArg(unsigned int index, std::string arg){

	Application *me = Application::getInstance();

	if(index >= me->args.size())
		me->args.push_back(arg);

	else
		me->args.insert(me->args.begin() + index, arg);
}

std::string Application::getArg(unsigned int index){
	
	Application *me = Application::getInstance();

	if(index >= me->args.size())
		return me->args.back();

	else
		return me->args[index];
}

unsigned int Application::countArgs(){
	return Application::getInstance()->args.size();
}

/*
	Aqui o preprocessador concatena os arquivos fontes para gerar um unico arquivo objeto
*/
#include "src/Random.cpp"
#include "src/Console.cpp"
#include "src/StdInput.cpp"
#include "src/StdOutput.cpp"
#include "src/Task.cpp"