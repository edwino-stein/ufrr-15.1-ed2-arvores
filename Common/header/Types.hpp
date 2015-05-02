/*
    Edwino Stein - 1201324411
*/

#if !defined _COMMON_TYPES
#define _COMMON_TYPES

#include <typeinfo>
#include <iostream>

namespace common {

    /**
     * @brief Classe responsavel por ralizar checagem de tipos.
     */

    class Types{

    	private:
        /**
         * @brief Contrutor padrão privado.
         */
		Types(){}

        /**
         * @brief Contrutor de copia privado.
         */
		Types(Types const&);

        /**
         * @brief Operador de atribuição privado.
         */
        void operator=(Types const&);

    	public:

        /**
         * @brief Verifica se o valor passado é um int.
         * @param var Valor a ser verificado.
         */
        template<typename Param>
        static bool isInt(Param var){
        	return typeid(var) == typeid(int);
    	}

        /**
         * @brief Verifica se o valor passado é um double.
         * @param var Valor a ser verificado.
         */
    	template<typename Param>
        static bool isDouble(Param var){
        	return typeid(var) == typeid(double);
    	}

        /**
         * @brief Verifica se o valor passado é um float.
         * @param var Valor a ser verificado.
         */
    	template<typename Param>
        static bool isFloat(Param var){
        	return typeid(var) == typeid(float);
    	}

        /**
         * @brief Verifica se o valor passado é um Real (float ou double).
         * @param var Valor a ser verificado.
         */
    	template<typename Param>
        static bool isReal(Param var){
        	return (typeid(var) == typeid(float)) || typeid(var) == typeid(double);
    	}

        /**
         * @brief Verifica se o valor passado é um char.
         * @param var Valor a ser verificado.
         */
    	template<typename Param>
        static bool isChar(Param var){
        	return typeid(var) == typeid(char);
    	}

        /**
         * @brief Verifica se o valor passado é uma string (char*, const char* ou std::string).
         * @param var Valor a ser verificado.
         */
    	template<typename Param>
        static bool isString(Param var){

        	if(typeid(var) == typeid(char *)){
        		return true;
        	}

        	if(typeid(var) == typeid(const char *)){
        		return true;
        	}

        	if(typeid(var) == typeid(std::string)){
        		return true;
        	}

        	return false;
    	}

        /**
         * @brief Verifica se o valor passado é um bool.
         * @param var Valor a ser verificado.
         */
    	template<typename Param>
        static bool isBool(Param var){
        	return typeid(var) == typeid(bool);
    	}

        /**
         * @brief Verifica se o valor passado é do tipo <b>T</b>.
         * @param var Valor a ser verificado.
         * @tparam T Tipo que será comparado.
         */
    	template <class T, typename Param>
        static bool is(Param var){
        	return typeid(var) == typeid(T);
    	}
    };
}

#endif