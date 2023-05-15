#include "Log.hpp"

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"

static bool
preCheck(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	if (client.getStatus() == ft_irc::Client::PASSWORD) {
		LOG_WARN("kick: Client didn't set the password yet")
		client.sendMsg("ERROR :Password required");

		return false;
	}
	if (client.getStatus() == ft_irc::Client::REGISTER) {
		LOG_WARN("kick: Client " << client.getFd() << "hasn't registered yet ")
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_NOTREGISTERED, client.getNickname()));

		return false;
	}
	if (cmd->args.size() < 2) {
		LOG_WARN("kick: 461: Need more params")
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_NEEDMOREPARAMS, client.getNickname(), ft_irc::toString(cmd->cmd)));

		return false;
	}

	return true;
}	// preCheck


void
ft_irc::Server::kick(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	std::stringstream target_list;
	std::string target_client;
	std::string comment = "Kicked from channel";

	if (!preCheck(client, cmd)) {
		return;
	}
	target_list << cmd->args.at(1);
	LOG_TRACE("kick: target_channel: " << cmd->args.at(0))
	LOG_TRACE("kick: target_list: " << target_list.str())
	if (!this->_channels.count(cmd->args.at(0))) {
		LOG_WARN("kick: 403: No such channel: " << cmd->args.at(0))
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_NOSUCHCHANNEL, client.getNickname(), cmd->args.at(0)));

		return;
	}
	if (cmd->args.size() > 2) {
		comment = cmd->args.at(2).empty() ? comment : cmd->args.at(2);
	}
	LOG_DEBUG("kick: comment: " << comment)
	while (getline(target_list, target_client, ',')) {
		try {
			this->_channels[cmd->args.at(0)]->kick(client, target_client, comment);
		} catch (ft_irc::Channel::NotOnChannel &e) {
			LOG_WARN("kick: 442: Not on channel: " << cmd->args.at(0));
			client.sendMsg(ft_irc::getReply(ft_irc::ERR_NOTONCHANNEL, client.getNickname(), cmd->args.at(0)));
		} catch (ft_irc::Channel::UserNotInChannel &e) {
			LOG_WARN("kick: 441: User not on channel: " << target_client << " " << cmd->args.at(0));
			client.sendMsg(ft_irc::getReply(ft_irc::ERR_USERNOTINCHANNEL, client.getNickname(), target_client,
				cmd->args.at(0)));
		} catch (ft_irc::Channel::NoPrivsOnChannel &e) {
			LOG_WARN("kick: 482: User doesnt have privileges on channel: " << cmd->args.at(0));
			client.sendMsg(ft_irc::getReply(ft_irc::ERR_CHANOPRIVSNEEDED, client.getNickname(), cmd->args.at(0)));
		}
	}
}	// Server::kick
