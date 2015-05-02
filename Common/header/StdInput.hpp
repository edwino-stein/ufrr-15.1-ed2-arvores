/*
    Edwino Stein - 1201324411
*/

#if !defined _COMMON_STDINPUT
#define _COMMON_STDINPUT

#include <iostream>
#include <limits>
#include <cstdio>
#if defined _IO_ftrylockfile || __GNU_LIBRARY__ == 1
    #include <cstring>
#endif

#include "StdOutput.hpp"

namespace common {

    /**
     * @brief Classe singleton responsavel pela entrada padrão.
     * @details A captura de valores é feita através de sobrecarga de operadores de casting, onde a variável 
     * recebe a instância _StdInput "convertida" para o tipo esperado. Exemplo:
     * 
     * @code
     * 
     * //Recupera a instância de _StdInput
     * _StdInput *in = _StdInput::getInstance();
     * 
     * //casting para int
     * int i = *in;
     * 
     * //casting para float
     * float f = *in;
     * 
     * //casting para char
     * char c = *in;
     * 
     * //casting para std::string
     * std::string s = *in;
     * 
     * @endcode
     * 
     */
    class _StdInput{

    	private:

        /**
         * @brief Contrutor padrão privado.
         */
        _StdInput();

        /**
         * @brief Verifica se o buffer do teclado está vazio.
         * @details Verifica-se a existência de algum resíduo originado na última operação de entrada no stream <b>STDIN</b>.
         * <p><i>Implementação deste método teve como base a implementação feita pela <b>GNU</b> da função <b>fpurge()</b> na <b>GLIBC</b>.
         * Disponivel em <a href="http://www.gnu.org/software/gnulib/coverage/gllib/fpurge.c.gcov.frameset.html">
         * http://www.gnu.org/software/gnulib/coverage/gllib/fpurge.c.gcov.frameset.html</a>, acessado em 10/10/14 as 11:23.</i></p>
         * 
         * @return TRUE caso esteja vazio, FALSE para exista algum resíduo.
         */ 
        bool bufferIsEmpty();

        public:
        
        /**
         * @brief Recupera a instância de _StdInput.
         * @return Referência para a instância singleton de _StdInput.
         */
        static _StdInput* getInstance();

        /**
         * @brief Captura um valor do tipo <b>T</b>
         * @details Método genérico responsável por realizar a captura de um valor do tipo definido no template.
         * 
         * @tparam T Tipo de dado esperado.
         * @return Valor capturado na entrada.
         */
        template<typename T>
        T get(){
            T var;
            std::cin >> var;
            this->flush();
            return var;
        }

        /**
         * @brief Método responsavel por encapsular o apontamento para a instância de _StdInput.
         * @return _StdInput Objeto de _StdInput.
         */
        _StdInput put(){
            return  *this;
        }

        /**
         * @brief Método responsavel por encapsular o apontamento para a instância de _StdInput.
         * @details Realiza a mesma função que <b>put()</b>, porém imprime uma string antes de realizar a captura.
         * 
         * @param strFormat String que será exibida antes da captura.
         * @return _StdInput Objeto de _StdInput
         */
        _StdInput put(const char *strFormat){
            _StdOutput::getInstance()->put(strFormat, false);
            return  *this;
        }

        /**
         * @brief Método responsavel por encapsular o apontamento para a instância de _StdInput.
         * @details Realiza a mesma função que <b>put(const char *strFormat)</b>, porém imprime uma string
         * concatenando os parâmentos ao estilo do <b>printf()</b> antes de realizar a captura.
         * 
         * @param strFormat String que será exibida antes da captura.
         * @param params Conjunto de parâmetros que serão concatenados a strFormat.
         * @return _StdInput Objeto de _StdInput
         */
        template <typename... Params>
        _StdInput put(const char *strFormat, Params... params){
            _StdOutput::getInstance()->printf(strFormat, params...);
            return *this;
        }

        /**
         * @brief Limpa o buffer de entrada, caso esteja sujo.
         */
        void flush();

        //boolean

        /**
         * @brief Operador de casting para booleano.
         * @details Realiza a captura de um valor booleano durante o casting.
         * @return Valor booleano capturado.
         */
        operator bool(){ return this->get<bool>(); }

        /**
         * @brief Realiza a captura de um valor booleano.
         * @details Define-se chaves de entrada para os valores TRUE e FALSE,
         * onde ao final da captura, o valor será equivalente a sua respectiva chave.
         * Será exibida uma menssagem de erro caso nenhuma das chaves sejam capturadas.
         * 
         * @param forTrue Chave que será equivalente ao TRUE.
         * @param forFalse Chave que será equivalente ao FALSE.
         * @param error Menssagem que será exibida caso nenhuma das chaves sejam capturadas. 
         * @return Valor booleano capturado.
         */
        bool putBool(std::string forTrue, std::string forFalse, std::string error);

        /**
         * @brief Realiza a captura de um valor booleano.
         * @details Define-se chaves de entrada para os valores TRUE e FALSE,
         * onde ao final da captura, o valor será equivalente a sua respectiva chave.
         * Neste método será definido um valor padrão caso nenhuma das chaves sejam capturadas.
         * 
         * @param forTrue Chave que será equivalente ao TRUE.
         * @param forFalse Chave que será equivalente ao FALSE.
         * @param defaultVal Valor padrão caso nenhuma das chaves sejam capturadas. 0 para FALSE ou qualquer valor par TRUE.
         * @return Valor booleano capturado.
         */
        bool putBool(std::string forTrue, std::string forFalse, int defaultVal);

        //aritméticos

        /**
         * @brief Operador de casting para short.
         * @details Realiza a captura de um valor short durante o casting.
         * @return Valor short capturado.
         */
        operator short(){ return this->get<short>(); }

        /**
         * @brief Operador de casting para unsigned short.
         * @details Realiza a captura de um valor unsigned short durante o casting.
         * @return Valor unsigned short capturado.
         */
        operator unsigned short(){ return this->get<unsigned short>(); }

        /**
         * @brief Operador de casting para int.
         * @details Realiza a captura de um valor int durante o casting.
         * @return Valor int capturado.
         */
        operator int(){ return this->get<int>(); }

        /**
         * @brief Operador de casting para unsigned int.
         * @details Realiza a captura de um valor unsigned int durante o casting.
         * @return Valor unsigned int capturado.
         */
        operator unsigned int(){ return this->get<unsigned int>(); }

        /**
         * @brief Operador de casting para long.
         * @details Realiza a captura de um valor long durante o casting.
         * @return Valor long capturado.
         */
        operator long(){ return this->get<long>(); }

        /**
         * @brief Operador de casting para unsigned long.
         * @details Realiza a captura de um valor unsigned long durante o casting.
         * @return Valor unsigned long capturado.
         */
        operator unsigned long(){ return this->get<unsigned long>(); }

        /**
         * @brief Operador de casting para long long.
         * @details Realiza a captura de um valor long long durante o casting.
         * @return Valor long long capturado.
         */
        operator long long(){ return this->get<long long>(); }

        /**
         * @brief Operador de casting para unsigned long long.
         * @details Realiza a captura de um valor unsigned long long durante o casting.
         * @return Valor unsigned long long capturado.
         */
        operator unsigned long long(){ return this->get<unsigned long long>(); }

        /**
         * @brief Operador de casting para float.
         * @details Realiza a captura de um valor float durante o casting.
         * @return Valor float capturado.
         */
        operator float(){ return this->get<float>(); }

        /**
         * @brief Operador de casting para double.
         * @details Realiza a captura de um valor double durante o casting.
         * @return Valor double capturado.
         */
        operator double(){ return this->get<double>(); }

        /**
         * @brief Operador de casting para long double.
         * @details Realiza a captura de um valor long double durante o casting.
         * @return Valor long double capturado.
         */
        operator long double(){ return this->get<long double>(); }

        //char e strings

        /**
         * @brief Operador de casting para char.
         * @details Realiza a captura de um valor char durante o casting.
         * @return Valor char capturado.
         */
        operator char(){return this->get<char>();}

        /**
         * @brief Operador de casting para unsigned char.
         * @details Realiza a captura de um valor unsigned char durante o casting.
         * @return Valor unsigned char capturado.
         */
        operator unsigned char(){return this->get<unsigned char>();}

        /**
         * @brief Operador de casting para std::string.
         * @details Realiza a captura de um valor std::string durante o casting.
         * @return Valor std::string capturado.
         */
        operator std::string(){ return this->putString(); }

        /**
         * @brief Metodo responsavel por capturar uma string de uma vez
         * @return String capturada
         */
        std::string putString();
    };

    typedef _StdInput *StdInput;
}
#endif
