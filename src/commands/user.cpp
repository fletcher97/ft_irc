#include "Log.hpp"

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"

static bool
preCheck(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	if (client.getStatus() == ft_irc::Client::PASSWORD) {
		LOG_WARN("user: Client didn't set the password yet")
		client.sendMsg("ERROR :Password required");

		return false;
	}
	if (client.getStatus() != ft_irc::Client::REGISTER) {
		LOG_WARN("user: 462: client already registered: " << client.getNickname())
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_ALREADYREGISTERED, client.getNickname()));

		return false;
	}
	if ((cmd->args.size() < 4) || cmd->args.front().empty()) {
		LOG_WARN("user: 461: Need more params")
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_NEEDMOREPARAMS, client.getNickname(), ft_irc::toString(cmd->cmd)));

		return false;
	}

	return true;
}	// preCheck


void
ft_irc::Server::user(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	if (!preCheck(client, cmd)) {
		return;
	}
	LOG_TRACE("user: " << client.getNickname() << ": username set to:" << cmd->args.front())
	client.setUsername(cmd->args.front());
	LOG_TRACE("user: " << client.getNickname() << ": realname set to:" << cmd->args.back())
	client.setRealname(cmd->args.back());
	if ((client.getStatus() != ft_irc::Client::ONLINE) && client.getNickname().size()) {
		this->posConnection(client);
	}
}	// Server::user
