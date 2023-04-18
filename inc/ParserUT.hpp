#if !defined(PARSERUT_HPP)
#define PARSERUT_HPP

#include "Parser.hpp"
#include "Testable.tpp"

namespace ft_irc
{

class ParserUT :
	public flt::Testable< ft_irc::ParserUT >, ft_irc::Parser
{
public:
	ParserUT(void);
	~ParserUT(void);

	void test_delimiter_msg(void);

	void test_tag_nocmd(void);
	void test_tag_presence(void);
	void test_tag_single_simple(void);
	void test_tag_multi_simple(void);
	void test_tag_single_kv(void);
	void test_tag_multi_kv(void);

	void test_source_presence(void);

	void test_command_nocmd(void);
	void test_command_valid(void);
	void test_command_invalid(void);
	void test_command_missing(void);

	void test_arguments_nocmd(void);
	void test_arguments_single(void);
	void test_arguments_multi(void);
	void test_arguments_missing(void);
	void test_arguments_colon(void);
	void test_arguments_multi_colon(void);
};	// class ParserUT

}	// namespace ft_irc

#endif // PARSERUT_HPP
