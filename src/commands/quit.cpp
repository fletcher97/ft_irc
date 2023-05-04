#include "Log.hpp"

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"

void
ft_irc::Server::quit(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	LOG_INFO("quit: " << client.getNickname() << " leaving")
	client.sendMsg("ERROR :Leaving Server");
	if (!cmd->args.empty()) {
		LOG_TRACE("quit: Reason: " << cmd->args.front())

		this->deleteClient(client.getFd(), cmd->args.front());

		return;
	}
	LOG_TRACE("quit: No reason")
	this->deleteClient(client.getFd());
}	// Server::quit
