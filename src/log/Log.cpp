#include <iostream>

#include "Log.hpp"


void
Log::trace(const std::stringstream& msg) {
	std::cout << TRACE_COLOR_FG << "[TRACE]" << RESET_COLOR << ": " <<
		msg.str() << RESET_COLOR << std::endl;
}

void
Log::debug(const std::stringstream& msg) {
	std::cout << DEBUG_COLOR_FG << "[DEBUG]" << RESET_COLOR << ": " <<
		msg.str()  << RESET_COLOR << std::endl;
}

void
Log::info(const std::stringstream& msg) {
	std::cout << INFO_COLOR_FG << "[INFO]" << RESET_COLOR << " : " <<
		msg.str()  << RESET_COLOR << std::endl;
}

void
Log::warn(const std::stringstream& msg) {
	std::cout << WARN_COLOR_FG << "[WARNS]" << RESET_COLOR << ": " <<
		msg.str()  << RESET_COLOR << std::endl;
}

void
Log::error(const std::stringstream& msg) {
	std::cout << ERROR_COLOR_FG << "[ERROR]" << RESET_COLOR << ": " <<
		msg.str()  << RESET_COLOR << std::endl;
}

void
Log::fatal(const std::stringstream& msg) {
	std::cout << FATAL_COLOR_FG << "[FATAL]" << RESET_COLOR << ": " <<
		msg.str()  << RESET_COLOR << std::endl;
}
