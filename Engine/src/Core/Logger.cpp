#include "Logger.h"

namespace Efflux {
	std::function<void(std::string&& message)> Logger::_function = NULL;

	bool Logger::Init(std::function<void(std::string&& message)> printfunction)
	{
		_function = printfunction;
		return true;
	}

	void Logger::Message(Level&& level, const std::string& message)
	{
		std::vector<std::string> levels = {
			"TRACE",
			"DEBUG",
			"INFO",
			"WARN",
			"ERROR",
			"SEVERE"
		};

		std::stringstream outmsg;
		outmsg << "[" << levels[(int)level] << "]: " << message;

		_function(outmsg.str());
	}
}