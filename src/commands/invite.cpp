#include "Log.hpp"

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"

static bool
preCheck(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	if (client.getStatus() == ft_irc::Client::PASSWORD) {
		LOG_WARN("invite: Client didn't set the password yet")
		client.sendMsg("ERROR :Password required");

		return false;
	}
	if (client.getStatus() == ft_irc::Client::REGISTER) {
		LOG_WARN("invite: Client " << client.getFd() << "hasn't registered yet ")
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_NOTREGISTERED, client.getNickname()));

		return false;
	}
	if (cmd->args.size() < 2) {
		LOG_WARN("invite: 461: Need more params")
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_NEEDMOREPARAMS, client.getNickname(), ft_irc::toString(cmd->cmd)));

		return false;
	}

	return true;
}	// preCheck


static void
inviteClient(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd, const std::map< int, ft_irc::Client* > &clients)
{
	ft_irc::Client *target_client = NULL;

	LOG_TRACE("invite: Looking for target in server: " << cmd->args.at(0))
	for (std::map< int, ft_irc::Client* >::const_iterator it = clients.begin(); it != clients.end(); it++) {
		if (it->second->getNickname() == cmd->args.at(0)) {
			LOG_TRACE("privmsg: Target found: " << cmd->args.at(0))
			target_client = it->second;
			break;
		}
	}
	if (!target_client) {
		LOG_DEBUG("invite: Target nickname doesent exist: " << cmd->args.at(0))

		return;
	}
	target_client->sendMsg(":" + client.getNickname() + " " + ft_irc::toString(cmd->cmd) + " " + cmd->args.at(
		0) + " " + cmd->args.at(1));
	LOG_DEBUG("invite: Invitation to " << cmd->args.at(1) << " sent to " << cmd->args.at(0))
}	// inviteClient


void
ft_irc::Server::invite(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	if (!preCheck(client, cmd)) {
		return;
	}
	LOG_TRACE("invite: Check if target is a channel: " << cmd->args.at(1))
	if (!this->_channels.count(cmd->args.at(1))) {
		LOG_WARN("invite: 403: No such channel: " << cmd->args.at(1))
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_NOSUCHCHANNEL, client.getNickname(), ft_irc::toString(cmd->cmd),
			cmd->args.at(1)));

		return;
	}
	try {
		LOG_TRACE("invite: Try invite to channel: " << cmd->args.at(1))
		this->_channels[cmd->args.at(1)]->invite(client, cmd->args.at(0));
		client.sendMsg(ft_irc::getReply(ft_irc::RPL_INVITING, client.getNickname(), cmd->args.at(0), cmd->args.at(1)));
		inviteClient(client, cmd, this->_clients);
		LOG_INFO("invite: Client: " << cmd->args.at(0) << ", invited succesfully to " << cmd->args.at(1))
	} catch (ft_irc::Channel::NotOnChannel &e) {
		LOG_WARN("invite: 442: " << client.getNickname() << " Not on channel: " << cmd->args.at(1))
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_NOTONCHANNEL, client.getNickname(), ft_irc::toString(cmd->cmd),
			cmd->args.at(1)));
	} catch (ft_irc::Channel::NoPrivsOnChannel &e) {
		LOG_WARN("invite: 442: " << client.getNickname() << " No privileges on channel: " << cmd->args.at(1))
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_CHANOPRIVSNEEDED, client.getNickname(), ft_irc::toString(cmd->cmd),
			cmd->args.at(1)));
	} catch (ft_irc::Channel::AlreadyOnChannel &e) {
		LOG_WARN("invite: 442: " << client.getNickname() << " Use already in channel: " << cmd->args.at(
			0) << " " << cmd->args.at(1))
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_USERONCHANNEL, client.getNickname(), cmd->args.at(0),
			cmd->args.at(1)));
	}
}	// Server::invite
