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
	std::string tags;
	std::string tag;
	std::string key;

	// Error checking
	LOG_DEBUG("Parsing tags for \"" + msg + "\"")
	if (!cmd) {
		LOG_ERROR("NULL command passed to tags parsing");
		throw std::invalid_argument("NULL command passed to tags parsing");
	}
	if (*msg.begin() != '@') {
		LOG_TRACE("No tags found")

		return;
	}
	if (msg.find_first_of(' ') == msg.npos) {
		LOG_ERROR("No spaces found to split tags with");
		throw std::invalid_argument("Msg contains no spaces");
	}
	if ((msg[msg.find_first_of(' ') - 1] == '=') || (msg[msg.find_first_of(' ') - 1] == ';')) {
		LOG_ERROR("Tags section ends with a '='");
		throw std::invalid_argument("Tag section ends with =");
	}

	// Tag parsing
	tags = msg.substr(1, msg.find_first_of(' ') - 1);
	LOG_TRACE("Splitting tags")
	do {
		LOG_TRACE("Parsing next tag")
		// Getting first tag
		if (*tags.begin() == ';') {
			tags = tags.substr(1, tags.size());
		}
		if (tags.find_first_of(';') != tags.npos) {
			tag = tags.substr(0, tags.find_first_of(';'));
		} else {
			tag = tags;
		}
		// Checking key
		if (tag.find_first_of('=') != tag.npos) {
			key = tag.substr(tag.find_first_of('=') + 1, tag.size());
			tag = tag.substr(0, tag.find_first_of('='));
		} else {
			key = "";
		}
		// Adding tag to cmd
		LOG_DEBUG("Adding tag: [" + tag + ";" + key + "]")
		cmd->tags.insert(std::pair< std::string, std::string >(tag, key));
		if (tags.find_first_of(';') != tags.npos) {
			LOG_TRACE("Tag deimiter detected")
			tags = tags.substr(tags.find_first_of(';'), tags.size());
		}
	} while (tags.find_first_of(';') != tags.npos);
	LOG_TRACE("Tag parsing completed")
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
