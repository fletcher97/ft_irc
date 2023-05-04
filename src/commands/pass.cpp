#include "Log.hpp"

#include "Channel.hpp"
#include "Client.hpp"
#include "Communications.hpp"
#include "Server.hpp"

static bool
preCheck(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	if (client.getStatus() != ft_irc::Client::PASSWORD) {
		LOG_WARN("pass: 462: client already registered")
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_ALREADYREGISTERED, client.getNickname()));

		return false;
	}
	if (!cmd->args.size()) {
		LOG_WARN("pass: 461: Need more params")
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_NEEDMOREPARAMS, client.getNickname(), ft_irc::toString(cmd->cmd)));

		return false;
	}

	return true;
}	// preCheck


void
ft_irc::Server::pass(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	if (!preCheck(client, cmd)) {
		return;
	}
	if (cmd->args.front() != ft_irc::Communications::getInstance().getPsswd()) {
		LOG_WARN("pass: 464: password mismatch: " << cmd->args.front())

		client.sendMsg(ft_irc::getReply(ft_irc::ERR_PASSWDMISMATCH, client.getNickname()));
		client.sendMsg("ERROR :Password mismatch");
		this->deleteClient(client.getFd());
		throw std::invalid_argument("Password mismatch");
	}
	LOG_INFO("pass: " << client.getFd() << " correct password: " << cmd->args.front())
	client.setStatus(ft_irc::Client::REGISTER);
}	// Server::pass
