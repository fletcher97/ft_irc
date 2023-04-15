#include "Parser.hpp"

#include "ParserUT.hpp"

ft_irc::ParserUT::ParserUT(void) :
	flt::Testable< ft_irc::ParserUT >("Parser")
{
	REGISTER(ft_irc::ParserUT, test_delimiter_msg)
	REGISTER(ft_irc::ParserUT, test_tag_nocmd)
	REGISTER(ft_irc::ParserUT, test_tag_presence)
	REGISTER(ft_irc::ParserUT, test_tag_single_simple)
	REGISTER(ft_irc::ParserUT, test_tag_multi_simple)
}


ft_irc::ParserUT::~ParserUT(void) {}

void
ft_irc::ParserUT::test_delimiter_msg(void)
{
	std::string msg;

	// Empty message
	msg = "";
	ASSERT_THROW(ft_irc::Parser::check_delimiter(msg), std::invalid_argument)

	// No delimiter string
	msg = "Hello world!";
	ASSERT_THROW(ft_irc::Parser::check_delimiter(msg), std::invalid_argument)

	// Multy delimiter string
	msg = "Hello\r\nworld!\r\n";
	ASSERT_THROW(ft_irc::Parser::check_delimiter(msg), std::invalid_argument)

	// Not delimiter terminated string
	msg = "Hello\r\nworld!";
	ASSERT_THROW(ft_irc::Parser::check_delimiter(msg), std::invalid_argument)

	// Delimiter char in middle of string
	msg = "Hello\rworld!\r\n";
	ASSERT_THROW(ft_irc::Parser::check_delimiter(msg), std::invalid_argument)

	// Delimiter char in middle of string
	msg = "Hello\nworld!\r\n";
	ASSERT_THROW(ft_irc::Parser::check_delimiter(msg), std::invalid_argument)

	// Correctly terminated string
	msg = "Hello world!\r\n";
	ASSERT_NOTHROW(ft_irc::Parser::check_delimiter(msg))
}	// ParserUT::test_delimiter_msg


void
ft_irc::ParserUT::test_tag_nocmd(void)
{
	std::string msg;

	// NULL cmd
	msg = "";
	ASSERT_THROW(ft_irc::Parser::parse_tags(NULL, msg), std::invalid_argument)
}	// ParserUT::test_tag_nocmd


void
ft_irc::ParserUT::test_tag_presence(void)
{
	ft_irc::Parser::cmd_t cmd;
	std::string msg;

	// Tags not present
	cmd = ft_irc::Parser::cmd_t();
	msg = "";
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags.size(), 0)

	// Tags present
	cmd = ft_irc::Parser::cmd_t();
	msg = "@abc";
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_NEQ(cmd.tags.size(), 0)

	// Tags present not at begining (shouldn't be detected)
	cmd = ft_irc::Parser::cmd_t();
	msg = " @abc";
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags.size(), 0)

	// Tags present not at begining (shouldn't be detected)
	cmd = ft_irc::Parser::cmd_t();
	msg = ":asd @abc";
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags.size(), 0)
}	// ParserUT::test_tag_presence


void
ft_irc::ParserUT::test_tag_single_simple(void)
{
	ft_irc::Parser::cmd_t cmd;
	std::string msg;
	std::map< std::string, std::string > expected;

	// Simple tag
	cmd = ft_irc::Parser::cmd_t();
	msg = "@abc";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("abc", ""));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags, expected)

	// Simple tag
	cmd = ft_irc::Parser::cmd_t();
	msg = "@de-f";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("de-f", ""));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags, expected)

	// Simple tag
	cmd = ft_irc::Parser::cmd_t();
	msg = "@+locahost/def";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("+locahost/def", ""));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags, expected)

	// Simple tag
	cmd = ft_irc::Parser::cmd_t();
	msg = "@ab42";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("ab42", ""));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags, expected)

	// Simple tag with extra information
	cmd = ft_irc::Parser::cmd_t();
	msg = "@ghi CAP * LIST";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("ghi", ""));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
}	// ParserUT::test_tag_single_simple


void
ft_irc::ParserUT::test_tag_multi_simple(void)
{
	ft_irc::Parser::cmd_t cmd;
	std::string msg;
	std::map< std::string, std::string > expected;

	// Simple multi tag
	cmd = ft_irc::Parser::cmd_t();
	msg = "@abc;def;ghi";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("abc", ""));
	expected.insert(std::pair< std::string, std::string >("def", ""));
	expected.insert(std::pair< std::string, std::string >("ghi", ""));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags, expected)

	// Simple multi tag with source and command
	cmd = ft_irc::Parser::cmd_t();
	msg = "@abc;def :sdwa CAP * LIST";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("abc", ""));
	expected.insert(std::pair< std::string, std::string >("def", ""));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags, expected)

	// Simple multi tag with source and command
	cmd = ft_irc::Parser::cmd_t();
	msg = "@+abc;+localhost/def;ab42 :sdwa CAP * LIST";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("+abc", ""));
	expected.insert(std::pair< std::string, std::string >("+localhost/def", ""));
	expected.insert(std::pair< std::string, std::string >("ab42", ""));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags, expected)
}	// ParserUT::test_tag_multi_simple


void
ft_irc::ParserUT::test_tag_single_kv(void)
{
	ft_irc::Parser::cmd_t cmd;
	std::string msg;

	// Simple tag
	cmd = ft_irc::Parser::cmd_t();
	msg = "@abc=";
	ASSERT_THROW(ft_irc::Parser::parse_tags(&cmd, msg), std::invalid_argument)

	// Simple tag
	msg = "@abc= ";
	ASSERT_THROW(ft_irc::Parser::parse_tags(&cmd, msg), std::invalid_argument)

	// Simple tag
	cmd = ft_irc::Parser::cmd_t();
	msg = "@def=abc";
	std::map< std::string, std::string > expected = std::map< std::string, std::string >();

	expected.insert(std::pair< std::string, std::string >("de-f", "abc"));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags, expected)

	// Simple tag
	cmd = ft_irc::Parser::cmd_t();
	msg = "@+locahost/def=123qsd";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("+locahost/def", "123qsd"));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags, expected)

	// Simple tag
	cmd = ft_irc::Parser::cmd_t();
	msg = "@ab42=!34asc";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("ab42", "!34asc"));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags, expected)

	// Simple tag with extra information
	cmd = ft_irc::Parser::cmd_t();
	msg = "@ghi=ghi CAP * LIST";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("ghi", "ghi"));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags, expected)
}	// ParserUT::test_tag_single_kv


void
ft_irc::ParserUT::test_tag_multi_kv(void)
{
	ft_irc::Parser::cmd_t cmd;
	std::string msg;
	std::map< std::string, std::string > expected;

	// Multi tag ERROR
	cmd = ft_irc::Parser::cmd_t();
	msg = "@abc=;abc=";
	ASSERT_THROW(ft_irc::Parser::parse_tags(&cmd, msg), std::invalid_argument)

	// Multi tag ERROR
	msg = "@abc=;abc= ";
	ASSERT_THROW(ft_irc::Parser::parse_tags(&cmd, msg), std::invalid_argument)

	// Multi tag ERROR
	msg = "@abc=;";
	ASSERT_THROW(ft_irc::Parser::parse_tags(&cmd, msg), std::invalid_argument)

	// Multi tag
	cmd = ft_irc::Parser::cmd_t();
	msg = "@def=abc;asd";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("de-f", "abc"));
	expected.insert(std::pair< std::string, std::string >("de-f", "abc"));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags, expected)

	// Multi tag
	cmd = ft_irc::Parser::cmd_t();
	msg = "@+locahost/def=123qsd;tya";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("+locahost/def", "123qsd"));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags, expected)

	// Multi tag
	cmd = ft_irc::Parser::cmd_t();
	msg = "@ab42=!34asc,cd33=w";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("ab42", "!34asc"));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags, expected)

	// Multi tag with extra information
	cmd = ft_irc::Parser::cmd_t();
	msg = "@ghi=ghi;id=123 CAP * LIST";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("ghi", "ghi"));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags, expected)
}	// ParserUT::test_tag_multi_kv


void
ft_irc::ParserUT::test_source_presence(void)
{
	std::string msg;

	msg = "CAP * LS\r\n";
	ASSERT_NOTHROW(ft_irc::Parser::check_source(msg))


	msg = "@id :abc.com CAP * LS\r\n";
	ASSERT_THROW(ft_irc::Parser::check_source(msg), std::invalid_argument)

	msg = ":abc.com CAP * LS\r\n";
	ASSERT_THROW(ft_irc::Parser::check_source(msg), std::invalid_argument)
}	// ParserUT::test_source_presence


void
ft_irc::ParserUT::test_command_nocmd(void)
{
	std::string msg;

	msg = "";
	ASSERT_THROW(ft_irc::Parser::parse_command(NULL, msg), std::invalid_argument)
}	// ParserUT::test_command_nocmd


void
ft_irc::ParserUT::test_command_valid(void)
{
	ft_irc::Parser::cmd_t cmd;
	std::string msg;
	ft_irc::commands expected;

	cmd = ft_irc::Parser::cmd_t();
	msg = "CAP * LS\r\n";
	expected = CAP;
	ASSERT_NOTHROW(ft_irc::Parser::parse_command(&cmd, msg))
	ASSERT_EQ(cmd.cmd, expected)

	cmd = ft_irc::Parser::cmd_t();
	msg = ":abc.com CAP * LS\r\n";
	expected = CAP;
	ASSERT_EQ(cmd.cmd, expected)

	cmd = ft_irc::Parser::cmd_t();
	msg = "@id :abc.com CAP * LS\r\n";
	expected = CAP;
	ASSERT_EQ(cmd.cmd, expected)

	cmd = ft_irc::Parser::cmd_t();
	msg = "@id CAP * LS\r\n";
	expected = CAP;
	ASSERT_EQ(cmd.cmd, expected)


	for (int i = 0; ALL_COMMANDS[i] != WALLOPS; i++) {
		cmd = ft_irc::Parser::cmd_t();
		msg = "@tag " + toString(ALL_COMMANDS[i]) + "\r\n";
		ASSERT_NOTHROW(ft_irc::Parser::parse_command(&cmd, msg))
		ASSERT_EQ(cmd.cmd, ALL_COMMANDS[i])
	}	// ParserUT::test_command_nocmd


	cmd = ft_irc::Parser::cmd_t();
	msg = "@tag " + toString(WALLOPS) + "\r\n";
	ASSERT_NOTHROW(ft_irc::Parser::parse_command(&cmd, msg))
	ASSERT_EQ(cmd.cmd, WALLOPS)
}	// ParserUT::test_command_valid


void
ft_irc::ParserUT::test_command_invalid(void)
{
	ft_irc::Parser::cmd_t cmd;
	std::string msg;

	cmd = ft_irc::Parser::cmd_t();
	msg = "@tag NOCAP\r\n";
	ASSERT_THROW(ft_irc::Parser::parse_command(&cmd, msg), std::invalid_argument)

	cmd = ft_irc::Parser::cmd_t();
	msg = "NOCAP\r\n";
	ASSERT_THROW(ft_irc::Parser::parse_command(&cmd, msg), std::invalid_argument)
}	// ParserUT::test_command_invalid


void
ft_irc::ParserUT::test_command_missing(void)
{
	ft_irc::Parser::cmd_t cmd;
	std::string msg;

	cmd = ft_irc::Parser::cmd_t();
	msg = "@tag\r\n";
	ASSERT_THROW(ft_irc::Parser::parse_command(&cmd, msg), std::invalid_argument)

	cmd = ft_irc::Parser::cmd_t();
	msg = "";
	ASSERT_THROW(ft_irc::Parser::parse_command(&cmd, msg), std::invalid_argument)

	cmd = ft_irc::Parser::cmd_t();
	msg = "@tag : asd\r\n";
	ASSERT_THROW(ft_irc::Parser::parse_command(&cmd, msg), std::invalid_argument)
}	// ParserUT::test_command_missing


void
ft_irc::ParserUT::test_arguments_nocmd(void)
{
	std::string msg;

	msg = "";
	ASSERT_THROW(ft_irc::Parser::parse_arguments(NULL, msg), std::invalid_argument)
}	// ParserUT::test_arguments_nocmd


void ft_irc::ParserUT::test_arguments_single(void) {}

void ft_irc::ParserUT::test_arguments_multi(void) {}

void ft_irc::ParserUT::test_arguments_missing(void) {}

void ft_irc::ParserUT::test_arguments_colon(void) {}

void ft_irc::ParserUT::test_arguments_multi_colon(void) {}
