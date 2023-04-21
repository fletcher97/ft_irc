#include <iostream>
#include <stdexcept>

#include "Parser.hpp"
#include "Log.hpp"

void
ft_irc::Parser::check_delimiter(std::string &msg)
{
	if ((msg.find_first_of('\r') == std::string::npos) || (msg.find_first_of('\n') == std::string::npos)) {
		LOG_ERROR("Message parsing error: Delimiter couldn't be found");
		throw std::invalid_argument("Delimiter couldn't be found");
	}
	if ((msg.find_first_of('\r') != (msg.size() - 2)) || (msg.find_first_of('\n') != (msg.size() - 1))) {
		LOG_ERROR("Message parsing error: Delimiter not at the end of message");
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
	std::string tmp;

	LOG_TRACE("Checking source presence for msg \"" + msg + "\"")
	if (msg[0] == ':') {
		LOG_ERROR("First char is a colon ':'");
		throw std::invalid_argument("First char is a colon ':'");
	}
	if (msg[0] != '@') {
		LOG_TRACE("No tag or source found")

		return;
	}
	if (msg[msg.find_first_not_of(' ', msg.find_first_of(' '))] == ':') {
		LOG_ERROR("Source's colon ':' found in middle of msg");
		throw std::invalid_argument("Source's colon ':' found in middle of msg");
	}
}	// Parser::check_source


void
ft_irc::Parser::parse_command(ft_irc::Parser::cmd_t *cmd, std::string &msg)
{
	std::string tmp;

	LOG_DEBUG("Parsing command for \"" + msg + "\"")
	if (!cmd) {
		LOG_ERROR("NULL command passed to command parsing");
		throw std::invalid_argument("NULL command passed to command parsing");
	}

	tmp = msg;
	if (tmp.size() && (tmp[0] == '@')) {
		try {
			LOG_TRACE("Removing tags from msg")
			tmp = tmp.substr(tmp.find_first_not_of(' ', tmp.find_first_of(' ')), tmp.size());
		} catch (std::exception &e) {
			LOG_ERROR("Failed tag removal due to missing spaces");
			throw std::invalid_argument("Failed tag removal due to missing spaces");
		}
	}
	if ((tmp.size() > 1) && (tmp[0] == ':')) {
		try {
			LOG_TRACE("Removing source from msg")
			tmp = tmp.substr(tmp.find_first_not_of(' ', tmp.find_first_of(' ')), tmp.size());
		} catch (std::exception &e) {
			LOG_ERROR("Failed source removal due to missing spaces");
			throw std::invalid_argument("Failed source removal due to missing spaces");
		}
	}
	tmp = tmp.substr(0, std::min(tmp.find_first_of(' '), tmp.find_first_of('\r')));
	try {
		LOG_TRACE("Getting command \"" + tmp + "\"")
		cmd->cmd = commandFromString(tmp);
	} catch (std::invalid_argument &e) {
		LOG_ERROR("\"" + tmp + "\" is not a valid command");
		throw std::invalid_argument("\"" + tmp + "\" is not a valid command");
	}
}	// Parser::parse_command


void
ft_irc::Parser::parse_arguments(ft_irc::Parser::cmd_t *cmd, std::string &msg)
{
	std::string tmp;

	LOG_DEBUG("Parsing args for \"" + msg + "\"")
	if (!cmd) {
		LOG_ERROR("NULL command passed to command parsing");
		throw std::invalid_argument("NULL command passed to command parsing");
	}

	tmp = msg;
	// Skip tag
	if (tmp.size() && (tmp[0] == '@')) {
		try {
			LOG_TRACE("Removing tags from msg")
			tmp = tmp.substr(tmp.find_first_not_of(' ', tmp.find_first_of(' ')), tmp.size());
		} catch (std::exception &e) {
			LOG_ERROR("Failed tag removal due to missing spaces");
			throw std::invalid_argument("Failed tag removal due to missing spaces");
		}
	}
	// Skip source
	if ((tmp.size()) && (tmp[0] == ':')) {
		try {
			LOG_TRACE("Removing source from msg")
			tmp = tmp.substr(tmp.find_first_not_of(' ', tmp.find_first_of(' ')), tmp.size());
		} catch (std::exception &e) {
			LOG_ERROR("Failed source removal due to missing spaces");
			throw std::invalid_argument("Failed source removal due to missing spaces");
		}
	}
	// Skip command
	LOG_TRACE("Removing command from msg")
	tmp = tmp.substr(std::min(tmp.find_first_not_of(' ', tmp.find_first_of(' ')), tmp.size()), tmp.size());

	while (tmp.size()) {
		LOG_TRACE("Extracting next param from " + tmp);
		if (tmp[0] == ':') {
			cmd->args.push_back(tmp.substr(1, tmp.size()));
			LOG_TRACE("Added ---" + cmd->args.back() + "---")
			break;
		} else {
			cmd->args.push_back(tmp.substr(0, std::min(tmp.find_first_of(' '), tmp.size())));
			LOG_TRACE("Added ---" + cmd->args.back() + "---")
		}
		tmp = tmp.substr(std::min(tmp.find_first_not_of(' ', tmp.find_first_of(' ')), tmp.size()), tmp.size());
	}
}	// Parser::parse_arguments


ft_irc::Parser::cmd_t*
ft_irc::Parser::parse_msg(std::string &msg)
{
	ft_irc::Parser::cmd_t *ret = NULL;

	msg = msg.substr(0, std::min(msg.find("\r\n"), msg.size()));
	try {
		ret = new ft_irc::Parser::cmd_t();
		ft_irc::Parser::parse_tags(ret, msg);
		ft_irc::Parser::check_source(msg);
		ft_irc::Parser::parse_command(ret, msg);
		ft_irc::Parser::parse_arguments(ret, msg);

		return ret;
	} catch (...) {
		if (ret) {
			delete ret;
		}
		throw;
	}
}	// Parser::parse_msg
