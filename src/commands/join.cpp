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


static void
leaveAllChannels(ft_irc::Client &client, std::map< std::string, ft_irc::Channel* > &channels)
{
	std::map< std::string, ft_irc::Channel* >::iterator it = channels.begin();
	std::string channel_name;

	LOG_INFO("join: " << client.getNickname() << " leaves every channel")
	while (it != channels.end()) {
		if (it->second->isInChannel(client)) {
			LOG_TRACE("join: " << client.getNickname() << " leaves " << it->second->getName());
			if (it->second->part(client, "Leaving")) {
				LOG_DEBUG("join: Deleting empty channel: " << it->second->getName())

				channel_name = it->second->getName();
				delete it->second;
				it++;
				channels.erase(channel_name);
				continue;
			}
		}
		it++;
	}
}	// leaveAllChannels


static bool
checkChannel(ft_irc::Client &client,
	std::map< std::string, ft_irc::Channel* > &channels,
	const std::string &channel_name)
{
	if (!channels.count(channel_name)) {
		LOG_DEBUG("join: Channel doesent match any existing channel: " << channel_name)
		try {
			LOG_TRACE("join: Try to create channel with name: " << channel_name);
			channels[channel_name] = new ft_irc::Channel(channel_name);
		} catch (...) {
			LOG_WARN("join: 476 Invalid channel name: " << channel_name);
			client.sendMsg(ft_irc::getReply(ft_irc::ERR_BADCHANMASK, client.getNickname(), channel_name));
			channels.erase(channel_name);

			return false;
		}
	}

	return true;
}	// checkChannel


static void
joinChannel(ft_irc::Client &client,
	std::map< std::string, ft_irc::Channel* > &channels,
	const std::string &channel_name,
	const std::string &key)
{
	try {
		LOG_TRACE("join: " << client.getNickname() << " try to join to  channel: " << channel_name);
		channels[channel_name]->join(client, key);
		LOG_INFO("join: " << client.getNickname() << " joined succesfully to " << channel_name);
		if (channels[channel_name]->getTopic().size()) {
			client.sendMsg(ft_irc::getReply(ft_irc::RPL_TOPIC, client.getNickname(), channel_name,
				channels[channel_name]->getTopic()));
		}
		channels[channel_name]->names(client);
	} catch (ft_irc::Channel::BannedClient &e) {
		LOG_WARN("join: 473: Invite only channel and client is not invited: " << client.getMask());
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_INVITEONLYCHAN, channel_name));
	} catch (ft_irc::Channel::InviteOnlyChannel &e) {
		LOG_WARN("join: 474: Banned from channel: " << client.getMask());
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_BANNEDFROMCHAN, channel_name));
	} catch (ft_irc::Channel::ChannelIsFull &e) {
		LOG_WARN("join: 471: Channel is full: " << channel_name);
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_CHANNELISFULL, channel_name));
	} catch (ft_irc::Channel::InvalidKey &e) {
		LOG_WARN("join: 475: Wrong channel key: " << key);
		client.sendMsg(ft_irc::getReply(ft_irc::ERR_BADCHANNELKEY, channel_name));
	}
}	// joinChannel


void
ft_irc::Server::join(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	std::stringstream channel_list;
	std::stringstream key_list;
	std::string channel_name;
	std::string key;

	if (!preCheck(client, cmd)) {
		return;
	}
	LOG_TRACE("join: Check for parameter 0")
	if (cmd->args.front() == "0") {
		leaveAllChannels(client, this->_channels);

		return;
	}
	channel_list << std::stringstream(cmd->args.at(0)).str();
	LOG_TRACE("join: Channel List: " << channel_list.str())
	if (cmd->args.size() > 1) {
		key_list << std::stringstream(cmd->args.at(1)).str();
	}
	LOG_TRACE("join: Key List: " << key_list.str())
	while (getline(channel_list, channel_name, ',')) {
		getline(key_list, key, ',');
		LOG_TRACE("join: Channel: " << channel_name)
		LOG_TRACE("join: Key: " << key)
		if (!checkChannel(client, this->_channels, channel_name)) {
			continue;
		}
		joinChannel(client, this->_channels, channel_name, key);
	}
}	// Server::join
