#include "Log.hpp"

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"

static bool
preCheck(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	if (client.getStatus() == ft_irc::Client::PASSWORD) {
		LOG_WARN("nick: Client didn't set the password yet")
		client.sendMsg("ERROR :Password required");

		return false;
	}
	if (!cmd->args.size()) {
		LOG_WARN("nick: 461: Need more params")
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_NEEDMOREPARAMS, client.getNickname(), ft_irc::toString(cmd->cmd)));

		return false;
	}

	return true;
}	// preCheck


void
ft_irc::Server::nick(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	std::string old_nick;

	if (!preCheck(client, cmd)) {
		return;
	}
	LOG_TRACE("nick: Checking if nickname is already in use")
	for (std::map< int, ft_irc::Client* >::iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		if (it->second->getNickname() == cmd->args.front()) {
			LOG_WARN("nick: 433: " << cmd->args.front() << " is already in use")
			client.sendMsg(ft_irc::getReply(ft_irc::ERR_NICKNAMEINUSE, client.getNickname(), cmd->args.front()));

			return;
		}
	}
	if (client.getStatus() == ft_irc::Client::ONLINE) {
		old_nick = client.getNickname() + " ";
	}
	try {
		client.setNickname(cmd->args.front());
		if (client.getStatus() == ft_irc::Client::ONLINE) {
			client.sendMsg(":" + old_nick + ft_irc::toString(cmd->cmd) + " " + client.getNickname());
		}
		LOG_INFO("nick: " << old_nick << "set to " << cmd->args.front())
	} catch (...) {
		LOG_WARN("nick: 433: erroneus nickname: " << cmd->args.front())
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_ERRONEUSNICKNAME, client.getNickname(), cmd->args.front()));

		return;
	}
}	// Server::nick
