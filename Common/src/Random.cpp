/*
    Edwino Stein - 1201324411
*/

/* ************************************************************** */
/* ******************** Implementação Random ******************** */
/* ************************************************************** */

_Random* _Random::getInstance(){
    static _Random *instance = new _Random;
    return instance;
}

int _Random::rand(int min, int max){
	this->generator.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> distribution(min, max);
	return distribution(this->generator);
}

int _Random::getInt(int max, int min){

    if(min > max){
        int tmp = min;
        min = max;
        max = tmp;
    }

    if(min == max){
        return min;
    }

    return this->rand(min, max);
}

char _Random::getChar(bool printableOnly){

    char minChar = 0;
    char maxChar = 127;

    if(printableOnly){
        minChar = 33;
        maxChar = 126;
    }

    return (char) this->rand(minChar, maxChar);
}

double _Random::getDouble(){

    int i, j;

    do{

        i = this->rand(1, 100);
        j = this->rand(1, 200);

    }while((j == 0) || (i % j == 0));

    return ((double) i)/((double) j);
}

bool _Random::getBool(){
  return (this->rand(0, 99) % 2 == 0);
}