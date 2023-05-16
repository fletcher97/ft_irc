#include "Log.hpp"

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"

static bool
preCheck(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	if (client.getStatus() == ft_irc::Client::PASSWORD) {
		LOG_WARN("privmsg: Client didn't set the password yet")
		client.sendMsg("ERROR :Password required");

		return false;
	}
	if (client.getStatus() == ft_irc::Client::REGISTER) {
		LOG_WARN("privmsg: Client " << client.getFd() << "hasn't registered yet ")
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_NOTREGISTERED, client.getNickname()));

		return false;
	}
	if (!cmd->args.size()) {
		LOG_WARN("privmsg: 411: No recipient")
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_NORECIPIENT, client.getNickname(), ft_irc::toString(cmd->cmd)));

		return false;
	}
	if (cmd->args.size() < 2) {
		LOG_WARN("privmsg: 412: No text to send")
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_NOTEXTTOSEND, client.getNickname()));

		return false;
	}

	return true;
}	// preCheck


static void
clientMsg(ft_irc::Client &client,
	const std::string &target,
	const std::string &msg,
	const std::map< int,
	ft_irc::Client* > &clients)
{
	ft_irc::Client *target_client = NULL;

	LOG_TRACE("privmsg: Looking for target in server: " << target)
	for (std::map< int, ft_irc::Client* >::const_iterator it = clients.begin(); it != clients.end(); it++) {
		if (it->second->getNickname() == target) {
			LOG_TRACE("privmsg: Target found: " << target)
			target_client = it->second;
			break;
		}
	}
	if (!target_client) {
		LOG_WARN("privmsg: 401 No such nick: " << target)
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_NOSUCHNICK, client.getNickname(), target));

		return;
	}
	if (target_client->getStatus() == ft_irc::Client::AWAY) {
		LOG_INFO("privmsg: 301 Client is away: " << target)
		client.sendMsg(ft_irc::getReply(ft_irc::RPL_AWAY, client.getNickname(), "USER AWAY"));	// getAWAYMSG;
	}
	target_client->sendMsg(":" + client.getMask() + " PRIVMSG " + target + " :" + msg);
	LOG_INFO("privmsg: Message succesfully send to " << target);
}	// clientMsg


static void
channelMsg(ft_irc::Client &client,
	std::string &target,
	const ft_irc::Parser::cmd_t *cmd,
	std::map< std::string,
	ft_irc::Channel* > &channels)
{
	std::string priv_chars;

	priv_chars = target.substr(0, target.find_first_not_of("#&+@~") - 1);
	target = target.substr(target.find_first_not_of("#&+@~") - 1);
	LOG_TRACE("privmsg: priv_chars: " << priv_chars << " target: " << target)
	if (!channels.count(target)) {
		LOG_WARN("privmsg: 401 No such nick: " << target)
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_NOSUCHNICK, client.getNickname(), target));

		return;
	}
	try {
		channels[target]->privmsg(client, cmd, priv_chars);
		LOG_INFO("privmsg: Message succesfully send to " << target);
	} catch (ft_irc::Channel::BannedClient &e) {
		LOG_WARN("privmsg: Client banned from channel")

		return;
	} catch (...) {
		LOG_WARN("privmsg: 404 Cannot send to channel")
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_CANNOTSENDTOCHAN, client.getNickname(), target));
	}
}	// channelMsg


void
ft_irc::Server::privmsg(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	std::stringstream target_list;
	std::string target;

	if (!preCheck(client, cmd)) {
		return;
	}
	target_list << cmd->args.at(0);
	LOG_TRACE("privmsg: target_list: " << target_list.str())
	while (getline(target_list, target, ',')) {
		if (std::string("#&+@~").find_first_of(target[0]) == std::string::npos) {
			LOG_TRACE("privmsg: target is not a channel: " << target)
			clientMsg(client, target, cmd->args.at(1), this->_clients);
		} else {
			LOG_TRACE("privmsg: target may be a channel: " << target)
			channelMsg(client, target, cmd, this->_channels);
		}
	}
}	// Server::privmsg
