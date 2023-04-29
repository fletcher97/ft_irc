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
		client.sendMsg("451");	// 451 - ERR_NOTREGISTERED

		return false;
	}
	if (!cmd->args.size()) {
		LOG_WARN("topic: 461: Need more params")
		client.sendMsg("461");	// 461 - ERR_NEEDMOREPARAMS

		return false;
	}

	return true;
}	// preCheck


static void
topicResponse(ft_irc::Client &client, const ft_irc::Channel *channel)
{
	if (!channel->isInChannel(client)) {
		LOG_WARN("topic: 442: Not on channel")
		client.sendMsg("442");	// 442 - ERR_NOTONCHANNEL

		return;
	}
	if (channel->getTopic().empty()) {
		LOG_WARN("topic: 331: No topic on channel")
		client.sendMsg("331");	// 331 - RPL_NOTOPIC

		return;
	}
	LOG_INFO("topic: 332: RPL_TOPIC: " << channel->getTopic())
	client.sendMsg("332");	// 332 - RPL_TOPIC
	LOG_INFO("topic: 333: RPL_TOPICWHOTIME")
	client.sendMsg("333");	// 332 - RPL_TOPICWHOTIME

	return;
}	// topicResponse


void
ft_irc::Server::topic(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	if (!preCheck(client, cmd)) {
		return;
	}
	LOG_TRACE("topic: Check if channel exists")
	if (!this->_channels.count(cmd->args.front())) {
		LOG_WARN("topic: 403: No such channel")
		client.sendMsg("403");	// 403 - ERR_NOSUCHCHANNEL

		return;
	}
	if (cmd->args.size() == 1) {
		LOG_TRACE("topic: Topic with no pramas")
		topicResponse(client, this->_channels[cmd->args.at(0)]);

		return;
	}
	try {
		this->_channels[cmd->args.front()]->setTopic(client, cmd->args.at(1));
		this->_channels[cmd->args.front()]->broadcast(cmd->cmd, cmd->args.at(1));
	} catch (ft_irc::Channel::NotOnChannel &e) {
		client.sendMsg("442");	// 442 - ERR_NOTONCHANNEL
	} catch (ft_irc::Channel::NoPrivsOnChannel &e) {
		client.sendMsg("482");	// 482 - ERR-CHANOPRIVSNEEDED
	}
}	// Server::topic
