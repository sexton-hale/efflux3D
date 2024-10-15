#pragma once

#include <Export.h>

#include <vector>
#include <string>
#include <functional>
#include <sstream>

namespace Efflux {
	enum class Level
	{
		TRACE,
		DEBUG,
		INFO,
		WARN,
		ERRORMSG,
		SEVERE
	};
	
	class EAPI Logger
	{
		using PrintFn = std::function<void(std::string&& message)>;
	public:
		Logger() = default;

		static bool Init(std::function<void(std::string&& message)> printfunction);

		/*
		Note: the message that will inputed into your print function, that you supplied, will not have the `\n` character in it.
		*/
		static void Message(Level&& level, const std::string& message);
	private:
		static PrintFn _function;
	};
}