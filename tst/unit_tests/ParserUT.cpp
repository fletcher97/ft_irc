#include "codes.hpp"

#include "ParserUT.hpp"
#include "Parser.hpp"

ft_irc::ParserUT::ParserUT(void) :
	flt::Testable< ft_irc::ParserUT >("Parser")
{
	REGISTER(ft_irc::ParserUT, test_delimiter_msg)

	REGISTER(ft_irc::ParserUT, test_tag_nocmd)
	REGISTER(ft_irc::ParserUT, test_tag_presence)
	REGISTER(ft_irc::ParserUT, test_tag_single_simple)
	REGISTER(ft_irc::ParserUT, test_tag_multi_simple)
	REGISTER(ft_irc::ParserUT, test_tag_single_kv)
	REGISTER(ft_irc::ParserUT, test_tag_multi_kv)

	REGISTER(ft_irc::ParserUT, test_source_presence)

	REGISTER(ft_irc::ParserUT, test_command_nocmd)
	REGISTER(ft_irc::ParserUT, test_command_valid)
	REGISTER(ft_irc::ParserUT, test_command_invalid)
	REGISTER(ft_irc::ParserUT, test_command_missing)

	REGISTER(ft_irc::ParserUT, test_arguments_nocmd)
	REGISTER(ft_irc::ParserUT, test_arguments_single)
	REGISTER(ft_irc::ParserUT, test_arguments_multi)
	REGISTER(ft_irc::ParserUT, test_arguments_missing)
	REGISTER(ft_irc::ParserUT, test_arguments_colon)
	REGISTER(ft_irc::ParserUT, test_arguments_multi_colon)

	REGISTER(ft_irc::ParserUT, test_parser_valid)
	REGISTER(ft_irc::ParserUT, test_parser_invalid)
}	// ParserUT::ParserUT


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
	msg = "@abc AUTHENTICATE";
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_NEQ(cmd.tags.size(), 0)

	// Tags no space
	cmd = ft_irc::Parser::cmd_t();
	msg = "@abc";
	ASSERT_THROW(ft_irc::Parser::parse_tags(&cmd, msg), std::invalid_argument)

	// Tags present not at begining (shouldn't be detected)
	cmd = ft_irc::Parser::cmd_t();
	msg = " @abc AUTHENTICATE";
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags.size(), 0)

	// Tags present not at begining (shouldn't be detected)
	cmd = ft_irc::Parser::cmd_t();
	msg = ":asd @abc AUTHENTICATE";
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
	msg = "@abc AUTHENTICATE";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("abc", ""));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags, expected)

	// Simple tag
	cmd = ft_irc::Parser::cmd_t();
	msg = "@de-f AUTHENTICATE";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("de-f", ""));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags, expected)

	// Simple tag
	cmd = ft_irc::Parser::cmd_t();
	msg = "@+locahost/def AUTHENTICATE";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("+locahost/def", ""));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags, expected)

	// Simple tag
	cmd = ft_irc::Parser::cmd_t();
	msg = "@ab42 AUTHENTICATE";
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
	msg = "@abc;def;ghi AUTHENTICATE";
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
	std::map< std::string, std::string > expected;

	// Simple tag
	cmd = ft_irc::Parser::cmd_t();
	msg = "@abc= AUTHENTICATE";
	ASSERT_THROW(ft_irc::Parser::parse_tags(&cmd, msg), std::invalid_argument)

	// Simple tag
	msg = "@abc= AUTHENTICATE";
	ASSERT_THROW(ft_irc::Parser::parse_tags(&cmd, msg), std::invalid_argument)

	// Simple tag
	cmd = ft_irc::Parser::cmd_t();
	msg = "@def=abc AUTHENTICATE";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("def", "abc"));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags, expected)

	// Simple tag
	cmd = ft_irc::Parser::cmd_t();
	msg = "@+locahost/def=123qsd AUTHENTICATE";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("+locahost/def", "123qsd"));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags, expected)

	// Simple tag
	cmd = ft_irc::Parser::cmd_t();
	msg = "@ab42=!34asc AUTHENTICATE";
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
	msg = "@abc=;abc= AUTHENTICATE";
	ASSERT_THROW(ft_irc::Parser::parse_tags(&cmd, msg), std::invalid_argument)

	// Multi tag ERROR
	msg = "@abc=;abc= AUTHENTICATE";
	ASSERT_THROW(ft_irc::Parser::parse_tags(&cmd, msg), std::invalid_argument)

	// Multi tag ERROR
	msg = "@abc=; AUTHENTICATE";
	ASSERT_THROW(ft_irc::Parser::parse_tags(&cmd, msg), std::invalid_argument)

	// Multi tag
	cmd = ft_irc::Parser::cmd_t();
	msg = "@def=abc;asd AUTHENTICATE";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("def", "abc"));
	expected.insert(std::pair< std::string, std::string >("asd", ""));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags, expected)

	// Multi tag
	cmd = ft_irc::Parser::cmd_t();
	msg = "@+locahost/def=123qsd;tya AUTHENTICATE";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("+locahost/def", "123qsd"));
	expected.insert(std::pair< std::string, std::string >("tya", ""));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags, expected)

	// Multi tag
	cmd = ft_irc::Parser::cmd_t();
	msg = "@ab42=!34asc;cd33=w AUTHENTICATE";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("ab42", "!34asc"));
	expected.insert(std::pair< std::string, std::string >("cd33", "w"));
	ASSERT_NOTHROW(ft_irc::Parser::parse_tags(&cmd, msg))
	ASSERT_EQ(cmd.tags, expected)

	// Multi tag with extra information
	cmd = ft_irc::Parser::cmd_t();
	msg = "@ghi=ghi;id=123 CAP * LIST";
	expected = std::map< std::string, std::string >();
	expected.insert(std::pair< std::string, std::string >("ghi", "ghi"));
	expected.insert(std::pair< std::string, std::string >("id", "123"));
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
	expected = ft_irc::CMD_CAP;
	ASSERT_NOTHROW(ft_irc::Parser::parse_command(&cmd, msg))
	ASSERT_EQ(cmd.cmd, expected)

	cmd = ft_irc::Parser::cmd_t();
	msg = ":abc.com CAP * LS\r\n";
	expected = ft_irc::CMD_CAP;
	ASSERT_EQ(cmd.cmd, expected)

	cmd = ft_irc::Parser::cmd_t();
	msg = "@id :abc.com CAP * LS\r\n";
	expected = ft_irc::CMD_CAP;
	ASSERT_EQ(cmd.cmd, expected)

	cmd = ft_irc::Parser::cmd_t();
	msg = "@id CAP * LS\r\n";
	expected = ft_irc::CMD_CAP;
	ASSERT_EQ(cmd.cmd, expected)


	for (int i = 0; ALL_COMMANDS[i] != ft_irc::CMD_WALLOPS; i++) {
		cmd = ft_irc::Parser::cmd_t();
		msg = "@tag " + toString(ALL_COMMANDS[i]) + "\r\n";
		ASSERT_NOTHROW(ft_irc::Parser::parse_command(&cmd, msg))
		ASSERT_EQ(cmd.cmd, ALL_COMMANDS[i])
	}	// ParserUT::test_command_nocmd


	cmd = ft_irc::Parser::cmd_t();
	msg = "@tag " + toString(ft_irc::CMD_WALLOPS) + "\r\n";
	ASSERT_NOTHROW(ft_irc::Parser::parse_command(&cmd, msg))
	ASSERT_EQ(cmd.cmd, ft_irc::CMD_WALLOPS)
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

	cmd = ft_irc::Parser::cmd_t();
	msg = "@tag :\r\n";
	ASSERT_THROW(ft_irc::Parser::parse_command(&cmd, msg), std::invalid_argument)
}	// ParserUT::test_command_missing


void
ft_irc::ParserUT::test_arguments_nocmd(void)
{
	std::string msg;

	msg = "";
	ASSERT_THROW(ft_irc::Parser::parse_arguments(NULL, msg), std::invalid_argument)
}	// ParserUT::test_arguments_nocmd


void
ft_irc::ParserUT::test_arguments_single(void)
{
	ft_irc::Parser::cmd_t cmd;
	std::string msg;
	std::list< std::string > expected;

	cmd = ft_irc::Parser::cmd_t();
	msg = "@tag CAP LS\r\n";
	expected = std::list< std::string >();
	expected.push_back("LS");
	ASSERT_NOTHROW(ft_irc::Parser::parse_arguments(&cmd, msg))
	ASSERT_EQ(cmd.args, expected)

	cmd = ft_irc::Parser::cmd_t();
	msg = "CAP REQ\r\n";
	expected = std::list< std::string >();
	expected.push_back("REQ");
	ASSERT_NOTHROW(ft_irc::Parser::parse_arguments(&cmd, msg))
	ASSERT_EQ(cmd.args, expected)
}	// ParserUT::test_arguments_single


void
ft_irc::ParserUT::test_arguments_multi(void)
{
	ft_irc::Parser::cmd_t cmd;
	std::string msg;
	std::list< std::string > expected;

	cmd = ft_irc::Parser::cmd_t();
	msg = "@tag CAP * LS\r\n";
	expected = std::list< std::string >();
	expected.push_back("*");
	expected.push_back("LS");
	ASSERT_NOTHROW(ft_irc::Parser::parse_arguments(&cmd, msg))
	ASSERT_EQ(cmd.args, expected)

	cmd = ft_irc::Parser::cmd_t();
	msg = "PRIVMSG #chan Hey!\r\n";
	expected = std::list< std::string >();
	expected.push_back("#chan");
	expected.push_back("Hey!");
	ASSERT_NOTHROW(ft_irc::Parser::parse_arguments(&cmd, msg))
	ASSERT_EQ(cmd.args, expected)
}	// ParserUT::test_arguments_multi


void
ft_irc::ParserUT::test_arguments_missing(void)
{
	ft_irc::Parser::cmd_t cmd;
	std::string msg;
	std::list< std::string > expected;

	cmd = ft_irc::Parser::cmd_t();
	msg = "@tag AUTHENTICATE\r\n";
	expected = std::list< std::string >();
	ASSERT_NOTHROW(ft_irc::Parser::parse_arguments(&cmd, msg))
	ASSERT_EQ(cmd.args, expected)

	cmd = ft_irc::Parser::cmd_t();
	msg = "AUTHENTICATE\r\n";
	expected = std::list< std::string >();
	ASSERT_NOTHROW(ft_irc::Parser::parse_arguments(&cmd, msg))
	ASSERT_EQ(cmd.args, expected)
}	// ParserUT::test_arguments_missing


void
ft_irc::ParserUT::test_arguments_colon(void)
{
	ft_irc::Parser::cmd_t cmd;
	std::string msg;
	std::list< std::string > expected;

	cmd = ft_irc::Parser::cmd_t();
	msg = "PRIVMSG #chan :Hey!\r\n";
	expected = std::list< std::string >();
	expected.push_back("#chan");
	expected.push_back("Hey!");
	ASSERT_NOTHROW(ft_irc::Parser::parse_arguments(&cmd, msg))
	ASSERT_EQ(cmd.args, expected)

	cmd = ft_irc::Parser::cmd_t();
	msg = "PRIVMSG #chan :Hello world!\r\n";
	expected = std::list< std::string >();
	expected.push_back("#chan");
	expected.push_back("Hello world!");
	ASSERT_NOTHROW(ft_irc::Parser::parse_arguments(&cmd, msg))
	ASSERT_EQ(cmd.args, expected)
}	// ParserUT::test_arguments_colon


void
ft_irc::ParserUT::test_arguments_multi_colon(void)
{
	ft_irc::Parser::cmd_t cmd;
	std::string msg;
	std::list< std::string > expected;

	cmd = ft_irc::Parser::cmd_t();
	msg = "PRIVMSG #chan :Can colons(:) be used\r\n";
	expected = std::list< std::string >();
	expected.push_back("#chan");
	expected.push_back("Can colons(:) be used");
	ASSERT_NOTHROW(ft_irc::Parser::parse_arguments(&cmd, msg))
	ASSERT_EQ(cmd.args, expected)

	cmd = ft_irc::Parser::cmd_t();
	msg = "PRIVMSG #chan :Can colons with spaces : be used\r\n";
	expected = std::list< std::string >();
	expected.push_back("#chan");
	expected.push_back("Can colons with spaces : be used");
	ASSERT_NOTHROW(ft_irc::Parser::parse_arguments(&cmd, msg))
	ASSERT_EQ(cmd.args, expected)
}	// ParserUT::test_arguments_multi_colon


void
ft_irc::ParserUT::test_parser_valid(void)
{
	ft_irc::Parser::cmd_t *cmd;
	ft_irc::Parser::cmd_t expected;
	std::string msg;

	msg = "CAP LS\r\n";
	expected = ft_irc::Parser::cmd_t();
	expected.cmd = ft_irc::CMD_CAP;
	expected.args.push_back("LS");
	ASSERT_NOTHROW(cmd = ft_irc::Parser::parse_msg(msg))
	ASSERT_EQ(cmd->tags, expected.tags)
	ASSERT_EQ(cmd->cmd, expected.cmd)
	ASSERT_EQ(cmd->args, expected.args)
	delete cmd;

	msg = "PASS\r\n";
	expected = ft_irc::Parser::cmd_t();
	expected.cmd = ft_irc::CMD_PASS;
	ASSERT_NOTHROW(cmd = ft_irc::Parser::parse_msg(msg))
	ASSERT_EQ(cmd->tags, expected.tags)
	ASSERT_EQ(cmd->cmd, expected.cmd)
	ASSERT_EQ(cmd->args, expected.args)
	delete cmd;

	msg = "NICK smiro\r\n";
	expected = ft_irc::Parser::cmd_t();
	expected.cmd = ft_irc::CMD_NICK;
	expected.args.push_back("smiro");
	ASSERT_NOTHROW(cmd = ft_irc::Parser::parse_msg(msg))
	ASSERT_EQ(cmd->tags, expected.tags)
	ASSERT_EQ(cmd->cmd, expected.cmd)
	ASSERT_EQ(cmd->args, expected.args)
	delete cmd;

	msg = "NICK       smiro\r\n";
	expected = ft_irc::Parser::cmd_t();
	expected.cmd = ft_irc::CMD_NICK;
	expected.args.push_back("smiro");
	ASSERT_NOTHROW(cmd = ft_irc::Parser::parse_msg(msg))
	ASSERT_EQ(cmd->tags, expected.tags)
	ASSERT_EQ(cmd->cmd, expected.cmd)
	ASSERT_EQ(cmd->args, expected.args)
	delete cmd;

	msg = "NICK\r\n";
	expected = ft_irc::Parser::cmd_t();
	expected.cmd = ft_irc::CMD_NICK;
	ASSERT_NOTHROW(cmd = ft_irc::Parser::parse_msg(msg))
	ASSERT_EQ(cmd->tags, expected.tags)
	ASSERT_EQ(cmd->cmd, expected.cmd)
	ASSERT_EQ(cmd->args, expected.args)
	delete cmd;

	msg = "NICK :\r\n";
	expected = ft_irc::Parser::cmd_t();
	expected.cmd = ft_irc::CMD_NICK;
	expected.args.push_back("");
	ASSERT_NOTHROW(cmd = ft_irc::Parser::parse_msg(msg))
	ASSERT_EQ(cmd->tags, expected.tags)
	ASSERT_EQ(cmd->cmd, expected.cmd)
	ASSERT_EQ(cmd->args, expected.args)
	delete cmd;

	msg = "NICK @ @\r\n";
	expected = ft_irc::Parser::cmd_t();
	expected.cmd = ft_irc::CMD_NICK;
	expected.args.push_back("@");
	expected.args.push_back("@");
	ASSERT_NOTHROW(cmd = ft_irc::Parser::parse_msg(msg))
	ASSERT_EQ(cmd->tags, expected.tags)
	ASSERT_EQ(cmd->cmd, expected.cmd)
	ASSERT_EQ(cmd->args, expected.args)
	delete cmd;

	msg = "USER smiro smiro 127.0.0.1 :Sebastian Miro\r\n";
	expected = ft_irc::Parser::cmd_t();
	expected.cmd = ft_irc::CMD_USER;
	expected.args.push_back("smiro");
	expected.args.push_back("smiro");
	expected.args.push_back("127.0.0.1");
	expected.args.push_back("Sebastian Miro");
	ASSERT_NOTHROW(cmd = ft_irc::Parser::parse_msg(msg))
	ASSERT_EQ(cmd->tags, expected.tags)
	ASSERT_EQ(cmd->cmd, expected.cmd)
	ASSERT_EQ(cmd->args, expected.args)
	delete cmd;

	msg = "USER smiro 0 * :Sebastian Miro\r\n";
	expected = ft_irc::Parser::cmd_t();
	expected.cmd = ft_irc::CMD_USER;
	expected.args.push_back("smiro");
	expected.args.push_back("0");
	expected.args.push_back("*");
	expected.args.push_back("Sebastian Miro");
	ASSERT_NOTHROW(cmd = ft_irc::Parser::parse_msg(msg))
	ASSERT_EQ(cmd->tags, expected.tags)
	ASSERT_EQ(cmd->cmd, expected.cmd)
	ASSERT_EQ(cmd->args, expected.args)
	delete cmd;

	msg = "MODE smiro +i\r\n";
	expected = ft_irc::Parser::cmd_t();
	expected.cmd = ft_irc::CMD_MODE;
	expected.args.push_back("smiro");
	expected.args.push_back("+i");
	ASSERT_NOTHROW(cmd = ft_irc::Parser::parse_msg(msg))
	ASSERT_EQ(cmd->tags, expected.tags)
	ASSERT_EQ(cmd->cmd, expected.cmd)
	ASSERT_EQ(cmd->args, expected.args)
	delete cmd;

	msg = "PING 127.0.0.1\r\n";
	expected = ft_irc::Parser::cmd_t();
	expected.cmd = ft_irc::CMD_PING;
	expected.args.push_back("127.0.0.1");
	ASSERT_NOTHROW(cmd = ft_irc::Parser::parse_msg(msg))
	ASSERT_EQ(cmd->tags, expected.tags)
	ASSERT_EQ(cmd->cmd, expected.cmd)
	ASSERT_EQ(cmd->args, expected.args)
	delete cmd;

	msg = "JOIN #hola\r\n";
	expected = ft_irc::Parser::cmd_t();
	expected.cmd = ft_irc::CMD_JOIN;
	expected.args.push_back("#hola");
	ASSERT_NOTHROW(cmd = ft_irc::Parser::parse_msg(msg))
	ASSERT_EQ(cmd->tags, expected.tags)
	ASSERT_EQ(cmd->cmd, expected.cmd)
	ASSERT_EQ(cmd->args, expected.args)
	delete cmd;

	msg = "JOIN #hola 1234\r\n";
	expected = ft_irc::Parser::cmd_t();
	expected.cmd = ft_irc::CMD_JOIN;
	expected.args.push_back("#hola");
	expected.args.push_back("1234");
	ASSERT_NOTHROW(cmd = ft_irc::Parser::parse_msg(msg))
	ASSERT_EQ(cmd->tags, expected.tags)
	ASSERT_EQ(cmd->cmd, expected.cmd)
	ASSERT_EQ(cmd->args, expected.args)
	delete cmd;

	msg = "JOIN #hola,&adios 1234,*\r\n";
	expected = ft_irc::Parser::cmd_t();
	expected.cmd = ft_irc::CMD_JOIN;
	expected.args.push_back("#hola,&adios");
	expected.args.push_back("1234,*");
	ASSERT_NOTHROW(cmd = ft_irc::Parser::parse_msg(msg))
	ASSERT_EQ(cmd->tags, expected.tags)
	ASSERT_EQ(cmd->cmd, expected.cmd)
	ASSERT_EQ(cmd->args, expected.args)
	delete cmd;

	msg = "NICK USER :\r\n";
	expected = ft_irc::Parser::cmd_t();
	expected.cmd = ft_irc::CMD_NICK;
	expected.args.push_back("USER");
	expected.args.push_back("");
	ASSERT_NOTHROW(cmd = ft_irc::Parser::parse_msg(msg))
	ASSERT_EQ(cmd->tags, expected.tags)
	ASSERT_EQ(cmd->cmd, expected.cmd)
	ASSERT_EQ(cmd->args, expected.args)
	delete cmd;

	msg = "PRIVMSG #chan ::-)\r\n";
	expected = ft_irc::Parser::cmd_t();
	expected.cmd = ft_irc::CMD_PRIVMSG;
	expected.args.push_back("#chan");
	expected.args.push_back(":-)");
	ASSERT_NOTHROW(cmd = ft_irc::Parser::parse_msg(msg))
	ASSERT_EQ(cmd->tags, expected.tags)
	ASSERT_EQ(cmd->cmd, expected.cmd)
	ASSERT_EQ(cmd->args, expected.args)
	delete cmd;
}	// ParserUT::test_parser_valid


void
ft_irc::ParserUT::test_parser_invalid(void)
{
	std::string msg;

	msg = "@id=234AB :dan!d@localhost PRIVMSG #chan :Hey what's up!";
	ASSERT_THROW(ft_irc::Parser::parse_msg(msg), std::invalid_argument)

	msg = "@id=234AB :dan!d@localhost PRIVMSG #chan :Hey what's up!\r\n";
	ASSERT_THROW(ft_irc::Parser::parse_msg(msg), std::invalid_argument)

	msg = ":NICK smiro\r\n";
	ASSERT_THROW(ft_irc::Parser::parse_msg(msg), std::invalid_argument)

	msg = "@NICK smiro\r\n";
	ASSERT_THROW(ft_irc::Parser::parse_msg(msg), std::invalid_argument)

	msg = ":dan!d@localhost PRIVMSG #chan ::-)\r\n";
	ASSERT_THROW(ft_irc::Parser::parse_msg(msg), std::invalid_argument)

	msg = ":dan!d@localhost PRIVMSG #chan :-)\r\n";
	ASSERT_THROW(ft_irc::Parser::parse_msg(msg), std::invalid_argument)
}	// ParserUT::test_parser_invalid
