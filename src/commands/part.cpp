#include "Log.hpp"

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"

static bool
preCheck(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	if (client.getStatus() == ft_irc::Client::PASSWORD) {
		LOG_WARN("join: Client didn't set the password yet")
		client.sendMsg("ERROR :Password required");

		return false;
	}
	if (client.getStatus() == ft_irc::Client::REGISTER) {
		LOG_WARN("join: Client " << client.getFd() << "hasn't registered yet ")
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_NOTREGISTERED, client.getNickname()));

		return false;
	}
	if (!cmd->args.size()) {
		LOG_WARN("join: 461: Need more params")
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_NEEDMOREPARAMS, client.getNickname(), ft_irc::toString(cmd->cmd)));

		return false;
	}

	return true;
}	// preCheck


void
ft_irc::Server::part(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	std::stringstream channel_list;
	std::string channel_name;
	std::string reason;

	if (!preCheck(client, cmd)) {
		return;
	}
	channel_list << std::stringstream(cmd->args.front()).str();
	LOG_TRACE("part: Channel List: " << channel_list.str())
	if (cmd->args.size() > 1) {
		reason = cmd->args.at(1);
		LOG_TRACE("part: Reason: " << reason)
	}
	while (getline(channel_list, channel_name, ',')) {
		LOG_TRACE("part: Channel Name: " << channel_name)

		if (!this->_channels.count(channel_name)) {
			LOG_WARN("part: 403: not such channel: " << channel_name)

			client.sendMsg(ft_irc::getReply(ft_irc::ERR_NOSUCHCHANNEL, client.getNickname(), channel_name));
			continue;
		}
		try {
			if (this->_channels[channel_name]->part(client, reason)) {
				LOG_DEBUG("part: Deleting empty channel: " << channel_name)

				delete this->_channels[channel_name];
				this->_channels.erase(channel_name);
			}
			client.sendMsg(":" + client.getMask() + " " + ft_irc::toString(cmd->cmd) + " " + channel_name);
			LOG_INFO("part: Client (" << client.getNickname() << ") succesfully leaved " << channel_name)
		} catch (...) {
			LOG_WARN("part: 442: Client(" << client.getNickname() << ") not on channel: " << channel_name)

			client.sendMsg(ft_irc::getReply(ft_irc::ERR_NOTONCHANNEL, client.getNickname(), channel_name));
		}
	}
}	// Server::part
