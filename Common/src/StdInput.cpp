/*
    Edwino Stein - 1201324411
*/

/* **************************************************************** */
/* ******************** Implementação StdInput ******************** */
/* **************************************************************** */

_StdInput* _StdInput::getInstance(){
    static _StdInput *instance = new _StdInput;
    return instance;
}


_StdInput::_StdInput(){

#if !defined _IO_ftrylockfile && __GNU_LIBRARY__ != 1 && !defined __sferror && !defined __DragonFly__
    _StdOutput::getInstance()->put("ERRO FALTAL: O programa não é compativel com implementação da LIBC do seu compilador!!! :(\n");
    exit(1);
#endif
    
}

/*
    Implementação deste metodo teve como base a implementação feita pela GNU da função fpurge() na GLIBC.
    Disponivel em <http://www.gnu.org/software/gnulib/coverage/gllib/fpurge.c.gcov.frameset.html>
    acessado em 10/10/14 as 11:23.
*/
bool _StdInput::bufferIsEmpty(){
/* ******************** Código em C ******************** */

#if defined _IO_ftrylockfile || __GNU_LIBRARY__ == 1
    /* Compatibilidade com: GNU libc, BeOS, Haiku, Linux libc5 */
    return strlen(stdin->_IO_read_ptr) == strlen(stdin->_IO_read_end);
    
#elif defined __sferror || defined __DragonFly__
    /* Compatibilidade com: FreeBSD, NetBSD, OpenBSD, DragonFly, MacOS X, Cygwin */
    return stdin->_r <= 0;

#else
    /* Caso não haja compatibilidade com os citados acima */
    _StdOutput::getInstance()->put("ERRO FALTAL: O programa não é compativel com implementação da LIBC do seu compilador!!! :(\n");
    exit(1);
#endif

/* ***************************************************** */
}

void _StdInput::flush(){
    if(!this->bufferIsEmpty()){
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string _StdInput::putString(){
    std::string str;
    std::getline(std::cin, str);
    return str;
}

bool _StdInput::putBool(std::string forTrue, std::string forFalse, std::string error){
    std::string input;

    while(true){
        input = this->putString();

        if(input == forTrue){
            return true;
        }

        if(input == forFalse){
            return false;
        }

        _StdOutput::getInstance()->put(error);
    }
}

bool _StdInput::putBool(std::string forTrue, std::string forFalse, int defaultVal){

    std::string input = this->putString();

    if(input == forTrue){
        return true;
    }

    if(input == forFalse){
        return false;
    }
    
    return (bool) defaultVal;
}