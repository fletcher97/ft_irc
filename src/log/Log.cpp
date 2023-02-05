#include <iostream>

#include "Log.hpp"

std::ofstream Log::fout;

void
Log::openFile(const std::string& path) {
	if (Log::fout.is_open()) {
		LOG_INFO("Changing log files to " << path)
		Log::fout.close();
	}

	Log::fout.open(path.c_str(), std::ios::out | std::ios::app);
	if (!Log::fout.is_open()) {
		LOG_ERROR("Failed to open file.")
	}
}

void
Log::closeFile() {
	if (Log::fout.is_open())
		Log::fout.close();
}

void
Log::trace(const std::stringstream& msg) {
	std::clog << TRACE_COLOR_FG << "[TRACE]" << RESET_COLOR << ": " <<
		msg.str() << RESET_COLOR << std::endl;
	if (Log::fout.is_open()) {
		Log::fout << "[TRACE]: " << msg.str() << std::endl;
		Log::fout.flush();
	}

}

void
Log::debug(const std::stringstream& msg) {
	std::clog << DEBUG_COLOR_FG << "[DEBUG]" << RESET_COLOR << ": " <<
		msg.str()  << RESET_COLOR << std::endl;
	if (Log::fout.is_open()) {
		Log::fout << "[DEBUG]: " << msg.str() << std::endl;
		Log::fout.flush();
	}
}

void
Log::info(const std::stringstream& msg) {
	std::clog << INFO_COLOR_FG << "[INFO]" << RESET_COLOR << ": " <<
		msg.str()  << RESET_COLOR << std::endl;
	if (Log::fout.is_open()) {
		Log::fout << "[INFO]: " << msg.str() << std::endl;
		Log::fout.flush();
	}
}

void
Log::warn(const std::stringstream& msg) {
	std::clog << WARN_COLOR_FG << "[WARNS]" << RESET_COLOR << ": " <<
		msg.str()  << RESET_COLOR << std::endl;
	if (Log::fout.is_open()) {
		Log::fout << "[WARNS]: " << msg.str() << std::endl;
		Log::fout.flush();
	}
}

void
Log::error(const std::stringstream& msg) {
	std::clog << ERROR_COLOR_FG << "[ERROR]" << RESET_COLOR << ": " <<
		msg.str()  << RESET_COLOR << std::endl;
	if (Log::fout.is_open()) {
		Log::fout << "[ERROR]: " << msg.str() << std::endl;
		Log::fout.flush();
	}
}

void
Log::fatal(const std::stringstream& msg) {
	std::clog << FATAL_COLOR_FG << "[FATAL]" << RESET_COLOR << ": " <<
		msg.str()  << RESET_COLOR << std::endl;
	if (Log::fout.is_open()) {
		Log::fout << "[FATAL]: " << msg.str() << std::endl;
		Log::fout.flush();
	}
}
