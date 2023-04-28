#include "Log.hpp"

#include "Client.hpp"
#include "Server.hpp"

static bool
preChecks(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	// check state
	if (client.getStatus() == ft_irc::Client::PASSWORD) {
		LOG_WARN("mode: Client didn't set the password yet")
		client.sendMsg("ERROR :Password required");

		return false;
	}
	if (client.getStatus() == ft_irc::Client::REGISTER) {
		LOG_WARN("mode: Client " << client.getFd << "hasn't registered yet ")
		client.sendMsg("451");	// 451 - ERR_NOTREGISTERED

		return false;
	}
	// check target
	if (!cmd->args.size()) {
		LOG_WARN("mode: 461: Need more params")
		client.sendMsg("461");	// 461 - ERR_NEEDMOREPARAMS

		return false;
	}

	return true;
}	// preChecks


void
ft_irc::Server::mode(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	// check client state
	if (!preChecks(client, cmd)) {
		return;
	}
}	// Server::mode
