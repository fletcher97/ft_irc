#include "Log.hpp"

#include "IBot.hpp"

#include "Server.hpp"

ft_irc::IBot::IBot(void) :
	ft_irc::Client()
{}	// IBot::IBot


ft_irc::IBot::IBot(const IBot &other) :
	ft_irc::Client(other)
{}	// IBot::IBot

ft_irc::IBot::IBot(const ft_irc::Client &other) :
	ft_irc::Client(other)
{}


ft_irc::IBot&
ft_irc::IBot::operator=(const ft_irc::IBot &other)
{
	ft_irc::Client::operator=(other);

	return *this;
}	// IBot::operator=


void
ft_irc::IBot::sendMsg(const std::string &msg) const
{
	ft_irc::Parser::cmd_t *cmd;
	std::string copy = msg;

	// remove tags
	if (copy[0] == '@') {
		copy = copy.substr(copy.find_first_not_of(' ', copy.find_first_of(' ')), copy.size());
	}
	// remove source
	if (copy[0] == ':') {
		copy = copy.substr(copy.find_first_not_of(' ', copy.find_first_of(' ')), copy.size());
	}

	cmd = ft_irc::Parser::parse_msg(copy);
	if (cmd->cmd == ft_irc::CMD_INVITE) {
		this->onInvite(cmd->args[1]);
		delete cmd;

		return;
	}

	if (cmd->cmd == ft_irc::CMD_PRIVMSG) {
		this->exec(cmd);
		delete cmd;

		return;
	}
}	// IBot::sendMsg


void
ft_irc::IBot::respond(const std::string &msg, const std::string &response) const
{
	ft_irc::Parser::cmd_t *cmd;
	std::string tmp;

	tmp = msg;
	cmd = ft_irc::Parser::parse_msg(tmp);

	this->respond(cmd, response);
	delete cmd;
}	// IBot::respond


void
ft_irc::IBot::respond(const ft_irc::Parser::cmd_t *cmd, const std::string &response) const
{
	ft_irc::Parser::cmd_t *cmd_resp;
	std::string msg;

	msg = "PRIVMSG " + cmd->args[0] + " :" + response;
	cmd_resp = ft_irc::Parser::parse_msg(msg);
	ft_irc::Server::getInstance().excecute(this->_fd, cmd_resp);
	delete cmd_resp;
}	// IBot::respond


void
ft_irc::IBot::onInvite(std::string &chan) const
{
	std::string msg;
	ft_irc::Parser::cmd_t *cmd;

	msg = "JOIN " + chan;
	cmd = ft_irc::Parser::parse_msg(msg);
	LOG_FATAL("IBot: Joining " + chan)
	ft_irc::Server::getInstance().join(ft_irc::Server::getInstance().getClient(this->_fd), cmd);
	LOG_FATAL("IBot: Joined")
	delete cmd;
}	// IBot::onInvite
