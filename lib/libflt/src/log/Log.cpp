#include <iostream>

#include "Log.hpp"

std::ofstream*flt::Log::_fout = NULL;
std::string flt::Log::_path = "";

void
flt::Log::openFile(const std::string &path)
{
	std::ofstream *new_fout = new std::ofstream();

	new_fout->open(path.c_str(), std::ios::out | std::ios::app);
	if (!new_fout->is_open()) {
		LOG_ERROR("Failed to open file \"" << path << "\" for logging.")

		return;
	}

	if (flt::Log::_fout) {
		LOG_INFO("Changing log files to \"" << path << "\".")
		flt::Log::_fout->close();
		delete flt::Log::_fout;
		flt::Log::_fout = NULL;
	}

	flt::Log::_fout = new_fout;
	flt::Log::_path = path;
	LOG_INFO("Opened file \"" << flt::Log::_path << "\" for logging.")
}	// Log::openFile


void
flt::Log::closeFile(void)
{
	if (flt::Log::_fout) {
		LOG_INFO("Closing file \"" << flt::Log::_path << "\" for logging.")
		flt::Log::_fout->close();
		delete flt::Log::_fout;
		flt::Log::_fout = NULL;
	}
}	// Log::closeFile


void
flt::Log::trace(const std::stringstream &msg)
{
	std::clog << FLT_LOG_TRACE_COLOR_FG << "[TRACE]" << FLT_LOG_RESET_COLOR << ": " << msg.str() << std::endl;
	if (flt::Log::_fout) {
		*flt::Log::_fout << "[TRACE]: " << msg.str() << std::endl;
		flt::Log::_fout->flush();
	}
}	// Log::trace


void
flt::Log::debug(const std::stringstream &msg)
{
	std::clog << FLT_LOG_DEBUG_COLOR_FG << "[DEBUG]" << FLT_LOG_RESET_COLOR << ": " << msg.str() << std::endl;
	if (flt::Log::_fout) {
		*flt::Log::_fout << "[DEBUG]: " << msg.str() << std::endl;
		flt::Log::_fout->flush();
	}
}	// Log::debug


void
flt::Log::info(const std::stringstream &msg)
{
	std::clog << FLT_LOG_INFO_COLOR_FG << "[INFO]" << FLT_LOG_RESET_COLOR << ": " << msg.str() << std::endl;
	if (flt::Log::_fout) {
		*flt::Log::_fout << "[INFO]: " << msg.str() << std::endl;
		flt::Log::_fout->flush();
	}
}	// Log::info


void
flt::Log::warn(const std::stringstream &msg)
{
	std::clog << FLT_LOG_WARN_COLOR_FG << "[WARN]" << FLT_LOG_RESET_COLOR << ": " << msg.str() << std::endl;
	if (flt::Log::_fout) {
		*flt::Log::_fout << "[WARN]: " << msg.str() << std::endl;
		flt::Log::_fout->flush();
	}
}	// Log::warn


void
flt::Log::error(const std::stringstream &msg)
{
	std::clog << FLT_LOG_ERROR_COLOR_FG << "[ERROR]" << FLT_LOG_RESET_COLOR << ": " << msg.str() << std::endl;
	if (flt::Log::_fout) {
		*flt::Log::_fout << "[ERROR]: " << msg.str() << std::endl;
		flt::Log::_fout->flush();
	}
}	// Log::error


void
flt::Log::fatal(const std::stringstream &msg)
{
	std::clog << FLT_LOG_FATAL_COLOR_FG << "[FATAL]" << FLT_LOG_RESET_COLOR << ": " << msg.str() << std::endl;
	if (flt::Log::_fout) {
		*flt::Log::_fout << "[FATAL]: " << msg.str() << std::endl;
		flt::Log::_fout->flush();
	}
}	// Log::fatal
