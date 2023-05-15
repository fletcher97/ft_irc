#include "Log.hpp"

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"

static bool
preCheck(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	if (client.getStatus() == ft_irc::Client::PASSWORD) {
		LOG_WARN("topic: Client didn't set the password yet")
		client.sendMsg("ERROR :Password required");

		return false;
	}
	if (client.getStatus() == ft_irc::Client::REGISTER) {
		LOG_WARN("topic: Client " << client.getFd() << "hasn't registered yet ")
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_NOTREGISTERED, client.getNickname()));

		return false;
	}
	if (!cmd->args.size()) {
		LOG_WARN("topic: 461: Need more params")
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_NEEDMOREPARAMS, client.getNickname(), ft_irc::toString(cmd->cmd)));

		return false;
	}

	return true;
}	// preCheck


static void
topicResponse(ft_irc::Client &client, const ft_irc::Channel *channel)
{
	if (!channel->isInChannel(client)) {
		LOG_WARN("topic: 442: Not on channel")
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_NOTONCHANNEL, client.getNickname(), channel->getName()));

		return;
	}
	if (channel->getTopic().empty()) {
		LOG_WARN("topic: 331: No topic on channel")
		client.sendMsg(ft_irc::getReply(ft_irc::RPL_NOTOPIC, client.getNickname(), channel->getName()));

		return;
	}
	LOG_INFO("topic: 332: RPL_TOPIC: " << channel->getTopic())
	client.sendMsg(ft_irc::getReply(ft_irc::RPL_TOPIC, client.getNickname(), channel->getName(), channel->getTopic()));
	LOG_INFO("topic: 333: RPL_TOPICWHOTIME")
	client.sendMsg(ft_irc::getReply(ft_irc::RPL_TOPICWHOTIME, client.getNickname(), channel->getName(),
		channel->getTopicWhoTime().first, channel->getTopicWhoTime().second));

	return;
}	// topicResponse


void
ft_irc::Server::topic(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	if (!preCheck(client, cmd)) {
		return;
	}
	LOG_TRACE("topic: Check if channel exists")
	if (!this->_channels.count(cmd->args.at(0))) {
		LOG_WARN("topic: 403: No such channel")
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_NOSUCHCHANNEL, client.getNickname(), cmd->args.at(0)));

		return;
	}
	if (cmd->args.size() == 1) {
		LOG_TRACE("topic: Topic with no pramas")
		topicResponse(client, this->_channels[cmd->args.at(0)]);

		return;
	}
	try {
		this->_channels[cmd->args.at(0)]->setTopic(client, cmd->args.at(1));
		this->_channels[cmd->args.at(0)]->broadcast(cmd->cmd, cmd->args.at(1));
	} catch (ft_irc::Channel::NotOnChannel &e) {
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_NOTONCHANNEL, client.getNickname(), cmd->args.at(0)));
	} catch (ft_irc::Channel::NoPrivsOnChannel &e) {
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_CHANOPRIVSNEEDED, client.getNickname(), cmd->args.at(0)));
	}
}	// Server::topic
