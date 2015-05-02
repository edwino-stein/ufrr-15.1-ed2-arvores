/*
    Edwino Stein - 1201324411
*/

/* ***************************************************************** */
/* ******************** Implementação StdOutput ******************** */
/* ***************************************************************** */

_StdOutput* _StdOutput::getInstance(){
    static _StdOutput *instance = new _StdOutput;
    return instance;
}

_StdOutput::_StdOutput(){}

_StdOutput * _StdOutput::putNewLine(){
	std::cout << _StdOutput::NEW_LINE;

	return this;
}

_StdOutput * _StdOutput::flush(){
    std::cout.flush();

    return this;
}

_StdOutput * _StdOutput::printf(const char *strFormat){
    this->put(strFormat, false);

    return this;
}

//boolean
_StdOutput * _StdOutput::put(bool val, std::string fTrue, std::string fFalse, bool newLine){

	if(val){
		std::cout << fTrue;
	}else{
		std::cout << fFalse;
	}

	if(newLine){
        this->putNewLine();
    }

    return this;
}

_StdOutput * _StdOutput::put(bool val, bool newLine){
	this->put(val, "1", "0", newLine);
	
    return this;
}

//aritméticos
_StdOutput * _StdOutput::put(short val, bool newLine){
	std::cout << val;

	if(newLine){
        this->putNewLine();
    }

    return this;
}

_StdOutput * _StdOutput::put(unsigned short val, bool newLine){
	std::cout << val;

	if(newLine){
        this->putNewLine();
    }

    return this;
}

_StdOutput * _StdOutput::put(int val, bool newLine){
	std::cout << val;

	if(newLine){
        this->putNewLine();
    }

    return this;
}

_StdOutput * _StdOutput::put(long val, bool newLine){
	std::cout << val;

	if(newLine){
        this->putNewLine();
    }

    return this;
}

_StdOutput * _StdOutput::put(unsigned long val, bool newLine){
	std::cout << val;

	if(newLine){
        this->putNewLine();
    }

    return this;
}

_StdOutput * _StdOutput::put(long long val, bool newLine){
	std::cout << val;

	if(newLine){
        this->putNewLine();
    }

    return this;
}

_StdOutput * _StdOutput::put(unsigned long long val, bool newLine){
	std::cout << val;

	if(newLine){
        this->putNewLine();
    }

    return this;
}

_StdOutput * _StdOutput::put(float val, bool newLine){
	std::cout << val;

	if(newLine){
        this->putNewLine();
    }

    return this;
}

_StdOutput * _StdOutput::put(double val, bool newLine){
	std::cout << val;

	if(newLine){
        this->putNewLine();
    }

    return this;
}

_StdOutput * _StdOutput::put(long double val, bool newLine){
	std::cout << val;

	if(newLine){
        this->putNewLine();
    }

    return this;
}


//char e strings
_StdOutput * _StdOutput::put(char val, bool newLine){
	std::cout << val;

	if(newLine){
        this->putNewLine();
    }

    return this;
}

_StdOutput * _StdOutput::put(unsigned char val, bool newLine){
	std::cout << val;

	if(newLine){
        this->putNewLine();
    }

    return this;
}

_StdOutput * _StdOutput::put(const char *str, bool newLine){
	std::cout << str;

	if(newLine){
        this->putNewLine();
    }

    return this;
}

_StdOutput * _StdOutput::put(std::string str, bool newLine){
	std::cout << str;

	if(newLine){
        this->putNewLine();
    }

    return this;
}

//stream buffers
_StdOutput * _StdOutput::put(std::streambuf* sb, bool newLine){
	std::cout << sb;

	if(newLine){
        this->putNewLine();
    }

    return this;
}
