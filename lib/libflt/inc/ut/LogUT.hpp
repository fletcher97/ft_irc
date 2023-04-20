#if !defined(LOGUT_HPP)
#define LOGUT_HPP

#include "Testable.tpp"

class LogUT :
	public flt::Testable< LogUT >
{
private:
	std::stringstream *newbuf;
	std::basic_streambuf< char, std::char_traits< char > > *oldbuf;

public:
	LogUT();

	virtual void init(void);
	virtual void term(void);


	void test_print_trace_macro(void);
	void test_print_trace_to_file_macro(void);

	void test_print_debug_macro(void);
	void test_print_debug_to_file_macro(void);

	void test_print_info_macro(void);
	void test_print_info_to_file_macro(void);

	void test_print_warn_macro(void);
	void test_print_warn_to_file_macro(void);

	void test_print_error_macro(void);
	void test_print_error_to_file_macro(void);

	void test_print_fatal_macro(void);
	void test_print_fatal_to_file_macro(void);

	void test_file_open(void);
	void test_file_change(void);
	void test_file_close(void);
};	// class LogUT

#endif // LOGUT_HPP
