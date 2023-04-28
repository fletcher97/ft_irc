#include <netinet/in.h>

#include "Log.hpp"

#include "Server.hpp"
#include "Communications.hpp"

ft_irc::Server&
ft_irc::Server::getInstance(void)
{
	static ft_irc::Server instance;

	return instance;
}	// Server::getInstance


ft_irc::Server::Server(void)
{
	LOG_DEBUG("Creating server");
	LOG_INFO("Server created");
}


ft_irc::Server::Server(const ft_irc::Server &s) :
	_clients(s._clients)
{}

ft_irc::Server&
ft_irc::Server::operator=(const ft_irc::Server &s)
{
	this->_clients = s._clients;

	return *this;
}	// Server::operator=


ft_irc::Server::~Server(void)
{
	LOG_INFO("Removed server");
}	// Server::~Server


void
ft_irc::Server::run(void)
{
	LOG_DEBUG("Running server");
	ft_irc::Communications::getInstance().run();
}	// Server::run


ft_irc::Client&
ft_irc::Server::getClient(const std::string &nickname) const
{
	for (std::map< int, ft_irc::Client* >::const_iterator it = _clients.begin(); it != _clients.end(); it++) {
		if (it->second->getNickname() == nickname) {
			return *(it->second);
		}
	}

	return *(this->_clients.end()->second);
}	// Server::getClient


ft_irc::Client&
ft_irc::Server::getClient(int fd) const
{
	return *(this->_clients.find(fd)->second);
}	// Server::getClient


void
ft_irc::Server::newClient(void)
{
	ft_irc::Communications &communications = ft_irc::Communications::getInstance();

	if (this->_clients.size() == MAX_CLIENTS) {
		return;
	}

	struct sockaddr_in clientAddress;
	socklen_t socklen = sizeof(clientAddress);
	int clientFd = accept(communications.getFd(), reinterpret_cast< struct sockaddr* >(&clientAddress), &socklen);

	if (clientFd == -1) {
		return;
	}
	this->_clients[clientFd] = new ft_irc::Client(clientFd, clientAddress);
	communications.addPfd(clientFd);
}	// Server::newClient


void
ft_irc::Server::sendMsg(int fd, const std::string &msg)
{
	ft_irc::Communications::getInstance().sendMsg(fd, msg);
}	// Server::send


void
ft_irc::Server::excecute(int fd, const ft_irc::Parser::cmd_t *cmd)
{
	ft_irc::Client &client = this->getClient(fd);

	switch (cmd->cmd) {
		case ft_irc::CMD_CAP: {
			LOG_INFO("execute: CAP Ignored")

			break;
		}

		case ft_irc::CMD_PASS: {
			LOG_INFO("execute: executing PASS")

			this->pass(client, cmd);
			break;
		}

		case ft_irc::CMD_NICK: {
			LOG_INFO("execute: executing NICK")

			this->nick(client, cmd);
			break;
		}

		case ft_irc::CMD_USER: {
			LOG_INFO("execute: executing USER")

			this->user(client, cmd);
			break;
		}

		case ft_irc::CMD_PART: {
			LOG_INFO("execute: executing PART")

			this->part(client, cmd);
			break;
		}

		case ft_irc::CMD_QUIT: {
			LOG_INFO("execute: executing QUIT")

			this->quit(client, cmd);
			break;
		}

		default: {
			LOG_WARN("Client executed " + ft_irc::toString(cmd->cmd) + " but it's not implemented")
		}
	}	// switch
}	// Server::excecute


void
ft_irc::Server::pass(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	if (client.getStatus() != ft_irc::Client::PASSWORD) {
		LOG_WARN("pass: 462: client already registered")

		return client.sendMsg("462: ");
	}
	if (cmd->args.empty() || cmd->args.front().empty()) {
		LOG_WARN("pass: 461: need more params")

		return client.sendMsg("461: ");
	}
	if (cmd->args.front() != ft_irc::Communications::getInstance().getPsswd()) {
		LOG_WARN("pass: 464: password mismatch: " << cmd->args.front())

		client.sendMsg("464: ");
		client.sendMsg("ERROR :Password mismatch");
		this->quit(client, NULL);
		throw std::invalid_argument("Password mismatch");
	}
	LOG_INFO("pass: " << client.getFd() << " correct password: " << cmd->args.front())
	client.setStatus(ft_irc::Client::REGISTER);
}	// Server::pass


void
ft_irc::Server::nick(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	std::string old_nick;

	if (client.getStatus() == ft_irc::Client::PASSWORD) {
		LOG_ERROR("user: Client didn't set the password yet")

		return client.sendMsg("ERROR :Password required");
	}
	if (cmd->args.empty()) {
		LOG_WARN("nick: 431: need more param")

		return client.sendMsg("431: ");
	}
	for (std::map< int, ft_irc::Client* >::iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		if (it->second->getNickname() == cmd->args.front()) {
			LOG_WARN("nick: 433: " << cmd->args.front() << " is already in use")

			return client.sendMsg("433: ");
		}
	}
	old_nick = client.getNickname();
	try {
		client.setNickname(cmd->args.front());
	} catch (...) {
		LOG_WARN("nick: 433: invalid character in nickname: " << cmd->args.front())

		return client.sendMsg("432: ");
	}

	LOG_INFO("nick: " << old_nick << " set to " << cmd->args.front())
	client.sendMsg(":" + old_nick + " " + ft_irc::toString(cmd->cmd) + " " + client.getNickname());
}	// Server::nick


void
ft_irc::Server::user(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	if (client.getStatus() == ft_irc::Client::PASSWORD) {
		LOG_ERROR("user: Client didn't set the password yet")

		return client.sendMsg("ERROR :Password required");
	}
	if (client.getStatus() != ft_irc::Client::REGISTER) {
		LOG_WARN("user: 462: client already registered: " << cmd->args.front())

		return client.sendMsg("462: ");
	}
	if ((cmd->args.size() < 4) || cmd->args.front().empty()) {
		LOG_WARN("user: 461: Need more params")

		return client.sendMsg("461: ");
	}
	client.setUsername(cmd->args.front());
	client.setRealname(cmd->args.back());
	client.setStatus(ft_irc::Client::ONLINE);
	LOG_INFO("user: " << client.getMask() << " is online")
}	// Server::user


void
ft_irc::Server::join(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	std::stringstream channel_list;
	std::stringstream key_list;
	std::string channel_name;
	std::string key;

	if (cmd->args.empty()) {
		LOG_WARN("join: 461: Need more params")

		return client.sendMsg("461");
	}
	LOG_TRACE("join: Check for parameter 0")
	if (cmd->args.front() == "0") {
		LOG_INFO("join: " << client.getNickname() << " leaves every channel")

		for (std::map< std::string, Channel* >::iterator it = this->_channels.begin(); it != this->_channels.end(); it++) {
			if (it->second->isInChannel(client)) {
				LOG_TRACE("join: " << client.getNickname() << " leaves " << ti->second->getName());
				it->second->part(client, "Leaving");
			}
		}
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
		if (!this->_channels.count(channel_name))
		{
			LOG_DEBUG("join: Channel doesent match any existing channel: " << channel_name)
			try {
				LOG_TRACE("join: Try to create channel with name: " << channel_name);
				this->_channels[channel_name] = new ft_irc::Channel(channel_name);
			} catch (...) {
				LOG_WARN("join: 476 Invalid channel name: " << channel_name);
				client.sendMsg("476 ERR_BADCHANMASK");
				delete this->_channels[channel_name];
				this->_channels.erase(channel_name);
				return ;
			}
		}
		try {
			LOG_TRACE("join: " << client.getNickname() <<  " try to join to  channel: " << channel_name);
			this->_channels[channel_name]->join(client, key);
			LOG_DEBUG("join: " << client.getNickname() << " joined succesfully to " << channel_name)
		} catch (ft_irc::Channel::BannedClient &e) {
			LOG_WARN("join: 474: Banned from channel: " << client.getMask())

			client.sendMsg("474");
		}
	}
}


void
ft_irc::Server::part(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	std::stringstream channel_list;
	std::string channel_name;
	std::string reason;

	if (cmd->args.empty()) {
		LOG_WARN("part: 461: Need more params")

		return client.sendMsg("461");
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

			client.sendMsg("403");
			continue;
		}
		try {
			if (this->_channels[channel_name]->part(client, reason)) {
				LOG_DEBUG("part: Deleting empty channel: " << channel_name)

				delete this->_channels[channel_name];
				this->_channels.erase(channel_name);
			}
			LOG_INFO("part: Client (" << client.getNickname() << ") succesfully leaved " << channel_name)
		} catch (...) {
			LOG_WARN("part: 442: Client(" << client.getNickname() << ") not on channel: " << channel_name)

			client.sendMsg("442");
		}
	}
}	// Server::part




void
ft_irc::Server::quit(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	LOG_INFO("quit: " << client.getNickname() << " leaving")
	client.sendMsg("ERROR :Leaving Server");
	if (!cmd->args.empty()) {
		LOG_TRACE("quit: Reason: " << cmd->args.front())

		this->deleteClient(client.getFd(), cmd->args.front());

		return;
	}
	LOG_TRACE("quit: With no reason")
	this->deleteClient(client.getFd());
}	// Server::quit


void
ft_irc::Server::deleteClient(int fd, const std::string &reason)
{
	std::map< std::string, Channel* >::iterator it = this->_channels.begin();
	std::string channel_name;

	LOG_TRACE("deleteClient: Quitting channels")
	while (it != this->_channels.end()) {
		if (it->second->isInChannel(this->getClient(fd))) {
			LOG_TRACE("deleteClient: Quitting: " << it->second->getName())
			if (it->second->part(this->getClient(fd), reason)) {
				LOG_DEBUG("deleteClient: Deleting empty channel: " << it->second->getName())

				channel_name = it->second->getName();
				delete it->second;
				it++;
				this->_channels.erase(channel_name);
				continue;
			}
		}
		it++;
	}
	LOG_INFO("Deleting client: " << fd)
	delete this->_clients[fd];
	this->_clients.erase(fd);
}	// Server::deleteClient
