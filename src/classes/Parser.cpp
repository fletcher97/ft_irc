#include <stdexcept>

#include "Parser.hpp"
#include "Log.hpp"

void
ft_irc::Parser::check_delimiter(std::string &msg)
{
	if ((msg.find_first_of('\r') == std::string::npos) || (msg.find_first_of('\n') == std::string::npos)) {
		LOG_ERROR("Message parsing error: Delimiter couldn't be found")
   throw std::invalid_argument("Delimiter couldn't be found");
	}
	if ((msg.find_first_of('\r') != (msg.size() - 2)) || (msg.find_first_of('\n') != (msg.size() - 1))) {
		LOG_ERROR("Message parsing error: Delimiter not at the end of message")
   throw std::invalid_argument("Delimiter not at the end of message");
	}
}	// Parser::check_delimiter


void
ft_irc::Parser::parse_tags(ft_irc::Parser::cmd_t *cmd, std::string &msg)
{
	LOG_TRACE("Parsing tags")
	if (!cmd) {
		LOG_ERROR("NULL command passed to tags parsing");
		throw std::invalid_argument("NULL command passed to tags parsing");
	}
	if (*msg.begin() != '@') {
		LOG_TRACE("Parsing tags: No tags found")

		return;
	}
	(void) cmd;
	(void) msg;
	throw std::exception();
}	// Parser::parse_tags


void
ft_irc::Parser::check_source(std::string &msg)
{
	(void) msg;
	throw std::exception();
}	// Parser::check_source


void
ft_irc::Parser::parse_command(ft_irc::Parser::cmd_t *cmd, std::string &msg)
{
	(void) cmd;
	(void) msg;
	throw std::exception();
}	// Parser::parse_command


void
ft_irc::Parser::parse_arguments(ft_irc::Parser::cmd_t *cmd, std::string &msg)
{
	(void) cmd;
	(void) msg;
	throw std::exception();
}	// Parser::parse_arguments


ft_irc::Parser::cmd_t*
ft_irc::Parser::parse_msg(std::string &msg)
{
	ft_irc::Parser::cmd_t *ret = NULL;

	try {
		check_delimiter(msg);
		ret = new ft_irc::Parser::cmd_t();
		ft_irc::Parser::parse_tags(ret, msg);
		ft_irc::Parser::check_source(msg);
		ft_irc::Parser::parse_command(ret, msg);
		ft_irc::Parser::parse_arguments(ret, msg);

		return ret;
	} catch (const std::exception &e) {
		if (ret) {
			delete ret;
		}
		throw e;
	}
}	// Parser::parse_msg
