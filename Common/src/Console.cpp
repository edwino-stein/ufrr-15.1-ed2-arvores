/*
	Edwino Stein - 1201324411
*/

/* *************************************************************** */
/* ******************** Implementação Console ******************** */
/* *************************************************************** */

_Console* _Console::getInstance(){
    static _Console *instance = new _Console;
    return instance;
}

void _Console::exec(std::string cmd){
	std::system(cmd.c_str());
}

void _Console::clear(){

	_StdOutput::getInstance()->flush();

#if defined WIN32
	this->exec("cls");
#else
	_StdOutput::getInstance()->put("\033c");
#endif

}

void _Console::pause(){

#if defined WIN32
	_StdOutput::getInstance()->flush();
    this->exec("pause");
#else
	_StdOutput::getInstance()->put("Pressione enter para continuar...");
    _StdOutput::getInstance()->flush();
    this->exec("read KEYPRESS");
#endif

}

void _Console::gotoXY(int x, int y){

#if defined WIN32
	COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
#else
	_StdOutput::getInstance()->printf("\033[%d;%dH",y,x);
#endif

}