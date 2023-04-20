#include "LogUT.hpp"
#include <iostream>
#include <sstream>

#include "Log.hpp"

LogUT::LogUT() :
	flt::Testable< LogUT >("LogUT")
{
	REGISTER(LogUT, test_print_trace_macro)
	REGISTER(LogUT, test_print_trace_to_file_macro)

	REGISTER(LogUT, test_print_debug_macro)
	REGISTER(LogUT, test_print_debug_to_file_macro)

	REGISTER(LogUT, test_print_info_macro)
	REGISTER(LogUT, test_print_info_to_file_macro)

	REGISTER(LogUT, test_print_warn_macro)
	REGISTER(LogUT, test_print_warn_to_file_macro)

	REGISTER(LogUT, test_print_error_macro)
	REGISTER(LogUT, test_print_error_to_file_macro)

	REGISTER(LogUT, test_print_fatal_macro)
	REGISTER(LogUT, test_print_fatal_to_file_macro)

	REGISTER(LogUT, test_file_open)
	REGISTER(LogUT, test_file_change)
	REGISTER(LogUT, test_file_close)
}


void
LogUT::init(void)
{
	this->newbuf = new std::stringstream();
	this->oldbuf = std::clog.rdbuf(this->newbuf->rdbuf());
}	// LogUT::init


void
LogUT::term(void)
{
	std::clog.rdbuf(this->oldbuf);
	delete this->newbuf;
	this->newbuf = NULL;
}	// LogUT::term


void
LogUT::test_print_trace_macro(void)
{
	std::string msg;
	std::string result;
	std::string expected;


	this->newbuf->str(std::string());
	msg = "trace msg";
	LOG_TRACE(msg)
	result = this->newbuf->str();
	expected = FLT_LOG_TRACE_COLOR_FG "[TRACE]" FLT_LOG_RESET_COLOR ": " + msg + "\n";
	ASSERT_EQ(result, expected)


	this->newbuf->str(std::string());
	msg = "";
	LOG_TRACE(msg)
	result = this->newbuf->str();
	expected = FLT_LOG_TRACE_COLOR_FG "[TRACE]" FLT_LOG_RESET_COLOR ": " + msg + "\n";
	ASSERT_EQ(result, expected)


	this->newbuf->str(std::string());
	msg = "";
	LOG_TRACE("")
	result = this->newbuf->str();
	expected = FLT_LOG_TRACE_COLOR_FG "[TRACE]" FLT_LOG_RESET_COLOR ": " + msg + "\n";
	ASSERT_EQ(result, expected)
}	// LogUT::test_print_trace_macro


void
LogUT::test_print_trace_to_file_macro(void)
{
	std::string msg;
	std::string result;
	std::string expected;
	std::string file_path;
	std::ifstream file_in;


	file_path = "/tmp/test.log";
	LOG_OPEN_FILE(file_path)
	file_in.open(file_path.c_str(), std::ios::in);
	file_in.seekg(0, file_in.end);


	msg = "trace msg";
	LOG_TRACE(msg)
	result = std::string(std::istreambuf_iterator< char >(file_in), std::istreambuf_iterator< char >());
	expected = "[TRACE]: " + msg + "\n";
	ASSERT_EQ(result, expected)


	msg = "";
	LOG_TRACE(msg)
	result = std::string(std::istreambuf_iterator< char >(file_in), std::istreambuf_iterator< char >());
	expected = "[TRACE]: " + msg + "\n";
	ASSERT_EQ(result, expected)


	msg = "";
	LOG_TRACE("")
	result = std::string(std::istreambuf_iterator< char >(file_in), std::istreambuf_iterator< char >());
	expected = "[TRACE]: " + msg + "\n";
	ASSERT_EQ(result, expected)


	file_in.close();
	LOG_CLOSE_FILE
}	// LogUT::test_print_trace_to_file_macro


void
LogUT::test_print_debug_macro(void)
{
	std::string msg;
	std::string result;
	std::string expected;

	this->newbuf->str(std::string());
	msg = "debug msg";
	LOG_DEBUG(msg)
	result = this->newbuf->str();
	expected = FLT_LOG_DEBUG_COLOR_FG "[DEBUG]" FLT_LOG_RESET_COLOR ": " + msg + "\n";
	ASSERT_EQ(result, expected)


	this->newbuf->str(std::string());
	msg = "";
	LOG_DEBUG(msg)
	result = this->newbuf->str();
	expected = FLT_LOG_DEBUG_COLOR_FG "[DEBUG]" FLT_LOG_RESET_COLOR ": " + msg + "\n";
	ASSERT_EQ(result, expected)


	this->newbuf->str(std::string());
	msg = "";
	LOG_DEBUG("")
	result = this->newbuf->str();
	expected = FLT_LOG_DEBUG_COLOR_FG "[DEBUG]" FLT_LOG_RESET_COLOR ": " + msg + "\n";
	ASSERT_EQ(result, expected)
}	// LogUT::test_print_debug_macro


void
LogUT::test_print_debug_to_file_macro(void)
{
	std::string msg;
	std::string result;
	std::string expected;
	std::string file_path;
	std::ifstream file_in;


	file_path = "/tmp/test.log";
	LOG_OPEN_FILE(file_path)
	file_in.open(file_path.c_str(), std::ios::in);
	file_in.seekg(0, file_in.end);


	msg = "debug msg";
	LOG_DEBUG(msg)
	result = std::string(std::istreambuf_iterator< char >(file_in), std::istreambuf_iterator< char >());
	expected = "[DEBUG]: " + msg + "\n";
	ASSERT_EQ(result, expected)


	msg = "";
	LOG_DEBUG(msg)
	result = std::string(std::istreambuf_iterator< char >(file_in), std::istreambuf_iterator< char >());
	expected = "[DEBUG]: " + msg + "\n";
	ASSERT_EQ(result, expected)


	msg = "";
	LOG_DEBUG("")
	result = std::string(std::istreambuf_iterator< char >(file_in), std::istreambuf_iterator< char >());
	expected = "[DEBUG]: " + msg + "\n";
	ASSERT_EQ(result, expected)


	file_in.close();
	LOG_CLOSE_FILE
}	// LogUT::test_print_debug_to_file_macro


void
LogUT::test_print_info_macro(void)
{
	std::string msg;
	std::string result;
	std::string expected;

	this->newbuf->str(std::string());
	msg = "info msg";
	LOG_INFO(msg)
	result = this->newbuf->str();
	expected = FLT_LOG_INFO_COLOR_FG "[INFO]" FLT_LOG_RESET_COLOR ": " + msg + "\n";
	ASSERT_EQ(result, expected)


	this->newbuf->str(std::string());
	msg = "";
	LOG_INFO(msg)
	result = this->newbuf->str();
	expected = FLT_LOG_INFO_COLOR_FG "[INFO]" FLT_LOG_RESET_COLOR ": " + msg + "\n";
	ASSERT_EQ(result, expected)


	this->newbuf->str(std::string());
	msg = "";
	LOG_INFO("")
	result = this->newbuf->str();
	expected = FLT_LOG_INFO_COLOR_FG "[INFO]" FLT_LOG_RESET_COLOR ": " + msg + "\n";
	ASSERT_EQ(result, expected)
}	// LogUT::test_print_info_macro


void
LogUT::test_print_info_to_file_macro(void)
{
	std::string msg;
	std::string result;
	std::string expected;
	std::string file_path;
	std::ifstream file_in;


	file_path = "/tmp/test.log";
	LOG_OPEN_FILE(file_path)
	file_in.open(file_path.c_str(), std::ios::in);
	file_in.seekg(0, file_in.end);


	msg = "info msg";
	LOG_INFO(msg)
	result = std::string(std::istreambuf_iterator< char >(file_in), std::istreambuf_iterator< char >());
	expected = "[INFO]: " + msg + "\n";
	ASSERT_EQ(result, expected)


	msg = "";
	LOG_INFO(msg)
	result = std::string(std::istreambuf_iterator< char >(file_in), std::istreambuf_iterator< char >());
	expected = "[INFO]: " + msg + "\n";
	ASSERT_EQ(result, expected)


	msg = "";
	LOG_INFO("")
	result = std::string(std::istreambuf_iterator< char >(file_in), std::istreambuf_iterator< char >());
	expected = "[INFO]: " + msg + "\n";
	ASSERT_EQ(result, expected)


	file_in.close();
	LOG_CLOSE_FILE
}	// LogUT::test_print_info_to_file_macro


void
LogUT::test_print_warn_macro(void)
{
	std::string msg;
	std::string result;
	std::string expected;

	this->newbuf->str(std::string());
	msg = "warn msg";
	LOG_WARN(msg)
	result = this->newbuf->str();
	expected = FLT_LOG_WARN_COLOR_FG "[WARN]" FLT_LOG_RESET_COLOR ": " + msg + "\n";
	ASSERT_EQ(result, expected)


	this->newbuf->str(std::string());
	msg = "";
	LOG_WARN(msg)
	result = this->newbuf->str();
	expected = FLT_LOG_WARN_COLOR_FG "[WARN]" FLT_LOG_RESET_COLOR ": " + msg + "\n";
	ASSERT_EQ(result, expected)


	this->newbuf->str(std::string());
	msg = "";
	LOG_WARN("")
	result = this->newbuf->str();
	expected = FLT_LOG_WARN_COLOR_FG "[WARN]" FLT_LOG_RESET_COLOR ": " + msg + "\n";
	ASSERT_EQ(result, expected)
}	// LogUT::test_print_warn_macro


void
LogUT::test_print_warn_to_file_macro(void)
{
	std::string msg;
	std::string result;
	std::string expected;
	std::string file_path;
	std::ifstream file_in;


	file_path = "/tmp/test.log";
	LOG_OPEN_FILE(file_path)
	file_in.open(file_path.c_str(), std::ios::in);
	file_in.seekg(0, file_in.end);


	msg = "warn msg";
	LOG_WARN(msg)
	result = std::string(std::istreambuf_iterator< char >(file_in), std::istreambuf_iterator< char >());
	expected = "[WARN]: " + msg + "\n";
	ASSERT_EQ(result, expected)


	msg = "";
	LOG_WARN(msg)
	result = std::string(std::istreambuf_iterator< char >(file_in), std::istreambuf_iterator< char >());
	expected = "[WARN]: " + msg + "\n";
	ASSERT_EQ(result, expected)


	msg = "";
	LOG_WARN("")
	result = std::string(std::istreambuf_iterator< char >(file_in), std::istreambuf_iterator< char >());
	expected = "[WARN]: " + msg + "\n";
	ASSERT_EQ(result, expected)


	file_in.close();
	LOG_CLOSE_FILE
}	// LogUT::test_print_warn_to_file_macro


void
LogUT::test_print_error_macro(void)
{
	std::string msg;
	std::string result;
	std::string expected;

	this->newbuf->str(std::string());
	msg = "error msg";
	LOG_ERROR(msg)
	result = this->newbuf->str();
	expected = FLT_LOG_ERROR_COLOR_FG "[ERROR]" FLT_LOG_RESET_COLOR ": " + msg + "\n";
	ASSERT_EQ(result, expected)


	this->newbuf->str(std::string());
	msg = "";
	LOG_ERROR(msg)
	result = this->newbuf->str();
	expected = FLT_LOG_ERROR_COLOR_FG "[ERROR]" FLT_LOG_RESET_COLOR ": " + msg + "\n";
	ASSERT_EQ(result, expected)


	this->newbuf->str(std::string());
	msg = "";
	LOG_ERROR("")
	result = this->newbuf->str();
	expected = FLT_LOG_ERROR_COLOR_FG "[ERROR]" FLT_LOG_RESET_COLOR ": " + msg + "\n";
	ASSERT_EQ(result, expected)
}	// LogUT::test_print_error_macro


void
LogUT::test_print_error_to_file_macro(void)
{
	std::string msg;
	std::string result;
	std::string expected;
	std::string file_path;
	std::ifstream file_in;


	file_path = "/tmp/test.log";
	LOG_OPEN_FILE(file_path)
	file_in.open(file_path.c_str(), std::ios::in);
	file_in.seekg(0, file_in.end);


	msg = "error msg";
	LOG_ERROR(msg)
	result = std::string(std::istreambuf_iterator< char >(file_in), std::istreambuf_iterator< char >());
	expected = "[ERROR]: " + msg + "\n";
	ASSERT_EQ(result, expected)


	msg = "";
	LOG_ERROR(msg)
	result = std::string(std::istreambuf_iterator< char >(file_in), std::istreambuf_iterator< char >());
	expected = "[ERROR]: " + msg + "\n";
	ASSERT_EQ(result, expected)


	msg = "";
	LOG_ERROR("")
	result = std::string(std::istreambuf_iterator< char >(file_in), std::istreambuf_iterator< char >());
	expected = "[ERROR]: " + msg + "\n";
	ASSERT_EQ(result, expected)


	file_in.close();
	LOG_CLOSE_FILE
}	// LogUT::test_print_error_to_file_macro


void
LogUT::test_print_fatal_macro(void)
{
	std::string msg;
	std::string result;
	std::string expected;

	this->newbuf->str(std::string());
	msg = "fatal msg";
	LOG_FATAL(msg)
	result = this->newbuf->str();
	expected = FLT_LOG_FATAL_COLOR_FG "[FATAL]" FLT_LOG_RESET_COLOR ": " + msg + "\n";
	ASSERT_EQ(result, expected)


	this->newbuf->str(std::string());
	msg = "";
	LOG_FATAL(msg)
	result = this->newbuf->str();
	expected = FLT_LOG_FATAL_COLOR_FG "[FATAL]" FLT_LOG_RESET_COLOR ": " + msg + "\n";
	ASSERT_EQ(result, expected)


	this->newbuf->str(std::string());
	msg = "";
	LOG_FATAL("")
	result = this->newbuf->str();
	expected = FLT_LOG_FATAL_COLOR_FG "[FATAL]" FLT_LOG_RESET_COLOR ": " + msg + "\n";
	ASSERT_EQ(result, expected)
}	// LogUT::test_print_fatal_macro


void
LogUT::test_print_fatal_to_file_macro(void)
{
	std::string msg;
	std::string result;
	std::string expected;
	std::string file_path;
	std::ifstream file_in;


	file_path = "/tmp/test.log";
	LOG_OPEN_FILE(file_path)
	file_in.open(file_path.c_str(), std::ios::in);
	file_in.seekg(0, file_in.end);


	msg = "fatal msg";
	LOG_FATAL(msg)
	result = std::string(std::istreambuf_iterator< char >(file_in), std::istreambuf_iterator< char >());
	expected = "[FATAL]: " + msg + "\n";
	ASSERT_EQ(result, expected)


	msg = "";
	LOG_FATAL(msg)
	result = std::string(std::istreambuf_iterator< char >(file_in), std::istreambuf_iterator< char >());
	expected = "[FATAL]: " + msg + "\n";
	ASSERT_EQ(result, expected)


	msg = "";
	LOG_FATAL("")
	result = std::string(std::istreambuf_iterator< char >(file_in), std::istreambuf_iterator< char >());
	expected = "[FATAL]: " + msg + "\n";
	ASSERT_EQ(result, expected)


	file_in.close();
	LOG_CLOSE_FILE
}	// LogUT::test_print_fatal_to_file_macro


void
LogUT::test_file_open(void)
{
	std::string file_path;
	std::ifstream file_in;

	std::string msg;
	std::string result;
	std::string expected;

	LOG_CLOSE_FILE;

	file_path = "/tmp/test.log";
	msg = "Opened file \"" + file_path + "\" for logging.";

	this->newbuf->str(std::string());				// clog prep
	file_in.open(file_path.c_str(), std::ios::in);	// file prep
	file_in.seekg(0, file_in.end);					// file prep

	LOG_OPEN_FILE(file_path);	// test

	result = this->newbuf->str();														// clog check
	expected = FLT_LOG_INFO_COLOR_FG "[INFO]" FLT_LOG_RESET_COLOR ": " + msg + "\n";	// clog check
	ASSERT_EQ(result, expected)															// clog check

	result = std::string(std::istreambuf_iterator< char >(file_in),	// file check
		std::istreambuf_iterator< char >());						// file check
	expected = "[INFO]: " + msg + "\n";								// file check
	ASSERT_EQ(result, expected)										// file check

	LOG_CLOSE_FILE;
}	// LogUT::test_file_open


void LogUT::test_file_change(void)
{}


void LogUT::test_file_close(void)
{}
