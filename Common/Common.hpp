/*
	Edwino Stein - 1201324411
*/

#if !defined  _COMMON_BASE
#define _COMMON_BASE

#include "header/Types.hpp"
#include "header/StdOutput.hpp"
#include "header/StdInput.hpp"
#include "header/Random.hpp"
#include "header/Console.hpp"
#include "header/Task.hpp"
#include "Application.hpp"

namespace common {

	/**
	 * @brief Instância global de Application;
	 */
	static const Application *app 	= Application::getInstance();

	/**
	 * @brief Instância global de _Random;
	 */
    static const Random randomic 	= _Random::getInstance();

    /**
	 * @brief Instância global de _Console;
	 */
	static const Console console 	= _Console::getInstance();

	/**
	 * @brief Instância global de _StdOutput;
	 */
	static const StdOutput out 	 	= _StdOutput::getInstance();

	/**
	 * @brief Instância global de _StdInput;
	 */
	static const StdInput in 	 	= _StdInput::getInstance();

	/**
	 * @brief Objeto base
	 */
	class Object{};
	typedef Object *pObject;

	typedef std::string String;
}

using namespace common;

#endif