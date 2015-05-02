/*
    Edwino Stein - 1201324411
*/
    
#if !defined _COMMON_STDOUTPUT
#define _COMMON_STDOUTPUT

#include <iostream>

namespace common {

    /**
     * @brief Classe singleton responsavel pela saida padrão.
     * @details A impressão de valores utiliza mesmo métodos de assinaturas diferentes
     * e de forma continua (a partir do retorno do método anterior), como no exemplo:
     * 
     * @code
     * 
     * //Recupera a instância de _StdOutput
     * _StdOutput *out = _StdOutput::getInstance();
     * 
     * //Imprime: Olá Mundo!
     * out->put("Olá")->put(' ')->put("Mundo!", true);
     * 
     * //Imprime: Int: 123
     * out->put("Int: ")->put(123, true);
     * 
     * //Imprime: Float: 123.456
     * out->put("Float: ")->put(123.456, true);
     * 
     * @endcode
     */
    class _StdOutput{

    	private:

        /**
         * @brief Contrutor padrão privado.
         */
        _StdOutput();

        /**
         * @brief Contrutor de copia privado.
         */
        _StdOutput(_StdOutput const&);

        /**
         * @brief Operador de atribuição privado.
         */
        void operator=(_StdOutput const&);

        public:

        /**
         * @brief Recupera a instância de _StdOutput.
         * @return Referência para a instância singleton de _StdOutput.
         */
        static _StdOutput* getInstance();

        /**
         * @brief Caractere de quebra de linha
         */
        static const char NEW_LINE = '\n';

        /**
         * @brief Imprime uma quebra de linha
         * @return Retorna a referência de _StdOutput para a utilização de chamadas continuas.
         */
        _StdOutput * putNewLine();


        /**
         * @brief Limpa o buffer de saida.
         * @return Retorna a referência de _StdOutput para a utilização de chamadas continuas.
         */
        _StdOutput * flush();

        /**
         * @brief Saida formatada.
         * @details Imprime uma string formatada, sem parâmetros ao estilo <b>printf()</b>
         * 
         * @param strFormat String de formato básica.
         * 
         * @return Retorna a referência de _StdOutput para a utilização de chamadas continuas.
         */
        _StdOutput * printf(const char *strFormat);

        /**
         * @brief Saida formatada.
         * @details Imprime uma string formatada, onde os parâmetros são concatenados a <b>strFormat</b> ao estilo <b>printf()</b>
         * 
         * @param strFormat String de formato básica.
         * @param params Conjunto de parâmetros que serão concatenados a strFormat.
         * 
         * @return Retorna a referência de _StdOutput para a utilização de chamadas continuas.
         */
        template<typename... Params>
        _StdOutput * printf(const char *strFormat, Params... params){
            std::printf(strFormat, params...);
            return this;
        }

        /**
         * @brief Método de impressão generico
         * @details Método responsavel por imprimir o valor do tipo <b>T</b>
         * 
         * @param val Valor a ser impresso.
         * @param newLine Adiciona uma quebra de linha apos o valor impresso.
         * 
         * @return Retorna a referência de _StdOutput para a utilização de chamadas continuas.
         */
        template<typename T>
        _StdOutput * put(T val, bool newLine = false){

            std::cout << val;

            if(newLine){
                this->putNewLine();
            }

            return this;
        }

        //boolean
        /**
         * @brief Imprime um valor booleano.
         * @details Método responsavel por imprimir o valor do tipo booleano.
         * 
         * @param val Valor a ser impresso.
         * @param newLine Adiciona uma quebra de linha apos o valor impresso.
         * 
         * @return Retorna a referência de _StdOutput para a utilização de chamadas continuas.
         */
        _StdOutput * put(bool val, bool newLine = false);

        /**
         * @brief Imprime um valor booleano.
         * @details Método responsavel por imprimir o valor do tipo booleano apartir de um representante.
         * 
         * @param val Valor a ser impresso.
         * @param fTrue Representante para TRUE.
         * @param fFalse Representante para FALSE.
         * @param newLine Adiciona uma quebra de linha apos o valor impresso.
         * 
         * @return Retorna a referência de _StdOutput para a utilização de chamadas continuas.
         */
        _StdOutput * put(bool val, std::string fTrue = "1", std::string fFalse = "0", bool newLine = false);

        //aritméticos
        /**
         * @brief Imprime um valor short.
         * @details Método responsavel por imprimir o valor do tipo short.
         * 
         * @param val Valor a ser impresso.
         * @param newLine Adiciona uma quebra de linha apos o valor impresso.
         * 
         * @return Retorna a referência de _StdOutput para a utilização de chamadas continuas.
         */
        _StdOutput * put(short val, bool newLine = false);

        /**
         * @brief Imprime um valor unsigned short.
         * @details Método responsavel por imprimir o valor do tipo unsigned short.
         * 
         * @param val Valor a ser impresso.
         * @param newLine Adiciona uma quebra de linha apos o valor impresso.
         * 
         * @return Retorna a referência de _StdOutput para a utilização de chamadas continuas.
         */
        _StdOutput * put(unsigned short val, bool newLine = false);

        /**
         * @brief Imprime um valor int.
         * @details Método responsavel por imprimir o valor do tipo int.
         * 
         * @param val Valor a ser impresso.
         * @param newLine Adiciona uma quebra de linha apos o valor impresso.
         * 
         * @return Retorna a referência de _StdOutput para a utilização de chamadas continuas.
         */
        _StdOutput * put(int val, bool newLine = false);

        /**
         * @brief Imprime um valor long.
         * @details Método responsavel por imprimir o valor do tipo long.
         * 
         * @param val Valor a ser impresso.
         * @param newLine Adiciona uma quebra de linha apos o valor impresso.
         * 
         * @return Retorna a referência de _StdOutput para a utilização de chamadas continuas.
         */
        _StdOutput * put(long val, bool newLine = false);

        /**
         * @brief Imprime um valor unsigned long.
         * @details Método responsavel por imprimir o valor do tipo unsigned long.
         * 
         * @param val Valor a ser impresso.
         * @param newLine Adiciona uma quebra de linha apos o valor impresso.
         * 
         * @return Retorna a referência de _StdOutput para a utilização de chamadas continuas.
         */
        _StdOutput * put(unsigned long val, bool newLine = false);

        /**
         * @brief Imprime um valor long long.
         * @details Método responsavel por imprimir o valor do tipo long long.
         * 
         * @param val Valor a ser impresso.
         * @param newLine Adiciona uma quebra de linha apos o valor impresso.
         * 
         * @return Retorna a referência de _StdOutput para a utilização de chamadas continuas.
         */
        _StdOutput * put(long long val, bool newLine = false);

        /**
         * @brief Imprime um valor unsigned long long.
         * @details Método responsavel por imprimir o valor do tipo unsigned long long.
         * 
         * @param val Valor a ser impresso.
         * @param newLine Adiciona uma quebra de linha apos o valor impresso.
         * 
         * @return Retorna a referência de _StdOutput para a utilização de chamadas continuas.
         */
        _StdOutput * put(unsigned long long val, bool newLine = false);

        /**
         * @brief Imprime um valor float.
         * @details Método responsavel por imprimir o valor do tipo float.
         * 
         * @param val Valor a ser impresso.
         * @param newLine Adiciona uma quebra de linha apos o valor impresso.
         * 
         * @return Retorna a referência de _StdOutput para a utilização de chamadas continuas.
         */
        _StdOutput * put(float val, bool newLine = false);

        /**
         * @brief Imprime um valor double.
         * @details Método responsavel por imprimir o valor do tipo double.
         * 
         * @param val Valor a ser impresso.
         * @param newLine Adiciona uma quebra de linha apos o valor impresso.
         * 
         * @return Retorna a referência de _StdOutput para a utilização de chamadas continuas.
         */
        _StdOutput * put(double val, bool newLine = false);

        /**
         * @brief Imprime um valor long double.
         * @details Método responsavel por imprimir o valor do tipo long double.
         * 
         * @param val Valor a ser impresso.
         * @param newLine Adiciona uma quebra de linha apos o valor impresso.
         * 
         * @return Retorna a referência de _StdOutput para a utilização de chamadas continuas.
         */
        _StdOutput * put(long double val, bool newLine = false);

        //char e strings
        /**
         * @brief Imprime um valor char.
         * @details Método responsavel por imprimir o valor do tipo char.
         * 
         * @param val Valor a ser impresso.
         * @param newLine Adiciona uma quebra de linha apos o valor impresso.
         * 
         * @return Retorna a referência de _StdOutput para a utilização de chamadas continuas.
         */
        _StdOutput * put(char val, bool newLine = false);

        /**
         * @brief Imprime um valor unsigned char.
         * @details Método responsavel por imprimir o valor do tipo unsigned char.
         * 
         * @param val Valor a ser impresso.
         * @param newLine Adiciona uma quebra de linha apos o valor impresso.
         * 
         * @return Retorna a referência de _StdOutput para a utilização de chamadas continuas.
         */
        _StdOutput * put(unsigned char val, bool newLine = false);

        /**
         * @brief Imprime uma string const char *.
         * @details Método responsavel por imprimir uma string const char *.
         * 
         * @param val Valor a ser impresso.
         * @param newLine Adiciona uma quebra de linha apos o valor impresso.
         * 
         * @return Retorna a referência de _StdOutput para a utilização de chamadas continuas.
         */
        _StdOutput * put(const char *str, bool newLine = false);

        /**
         * @brief Imprime uma string.
         * @details Método responsavel por imprimir uma string.
         * 
         * @param val Valor a ser impresso.
         * @param newLine Adiciona uma quebra de linha apos o valor impresso.
         * 
         * @return Retorna a referência de _StdOutput para a utilização de chamadas continuas.
         */
        _StdOutput * put(std::string str, bool newLine = false);

        //stream buffers
        /**
         * @brief Imprime o conteúdo de um std::streambuf.
         * @details Método responsavel por imprimir o conteúdo de um std::streambuf.
         * 
         * @param val Valor a ser impresso.
         * @param newLine Adiciona uma quebra de linha apos o valor impresso.
         * 
         * @return Retorna a referência de _StdOutput para a utilização de chamadas continuas.
         */
        _StdOutput * put(std::streambuf* sb, bool newLine = false);
    };

    typedef _StdOutput *StdOutput;
}

#endif
