#include "Log.hpp"

#include "Server.hpp"

void
ft_irc::Server::ping(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	if (cmd->args.size() == 0) {
		LOG_ERROR("ping: No token passed")
		client.sendMsg("PONG");

		return;
	}
	if (cmd->args.size() > 1) {
		LOG_ERROR("ping: Too many args. Sending first only")
		client.sendMsg("PONG " + cmd->args[0]);

		return;
	}
	LOG_DEBUG("ping: replying PONG " << cmd->args[0])
	client.sendMsg("PONG " + cmd->args[0]);
}	// Server::ping
