#include <stdexcept>

#include "Parser.hpp"
#include "Log.hpp"

void
ft_irc::Parser::check_delimiter(std::string &msg) {
	(void)msg;
	throw std::exception();
}

void ft_irc::Parser::parse_tags(ft_irc::Parser::cmd_t *cmd, std::string &msg)
{
	(void)cmd;
	(void)msg;
	throw std::exception();
}

void
ft_irc::Parser::check_source(ft_irc::Parser::cmd_t *cmd, std::string &msg) {
	(void)cmd;
	(void)msg;
	throw std::exception();
}

void
ft_irc::Parser::parse_command(ft_irc::Parser::cmd_t *cmd, std::string &msg) {
	(void)cmd;
	(void)msg;
	throw std::exception();
}

void
ft_irc::Parser::parse_arguments(ft_irc::Parser::cmd_t *cmd, std::string &msg) {
	(void)cmd;
	(void)msg;
	throw std::exception();
}

ft_irc::Parser::cmd_t*
ft_irc::Parser::parse_msg(std::string &msg)
{
	(void)msg;
	throw std::exception();
}
