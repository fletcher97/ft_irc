#if !defined(PARSERUT_HPP)
#define PARSERUT_HPP

#include "Testable.tpp"
#include "Parser.hpp"

class ParserUT : public flt::Testable<ParserUT>, ft_irc::Parser
{
public:
	ParserUT(void);
	~ParserUT(void);

	void test_delimiter_msg(void);

	void test_tag_presence(void);
	void test_tag_single_simple(void);
	void test_tag_multi_simple(void);
	void test_tag_single_kv(void);
	void test_tag_multi_kv(void);

	void test_source_presence(void);

	void test_command_valid(void);
	void test_command_invalid(void);
	void test_command_missing(void);

	void test_arguments_single(void);
	void test_arguments_multi(void);
	void test_arguments_missing(void);
	void test_arguments_colon(void);
	void test_arguments_multi_colon(void);

};

#endif // PARSERUT_HPP
