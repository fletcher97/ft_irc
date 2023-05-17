#include <netinet/in.h>

#include "Log.hpp"

#include "BotHLGame.hpp"

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

	LOG_INFO("Loading bots");
	this->_clients[-1] = new ft_irc::BotHLGame();

	LOG_INFO("Server created");
}


ft_irc::Server::Server(const ft_irc::Server &s) :
	_clients(s._clients),
	_channels(s._channels)
{}

ft_irc::Server&
ft_irc::Server::operator=(const ft_irc::Server &s)
{
	this->_clients = s._clients;
	this->_channels = s._channels;

	return *this;
}	// Server::operator=


ft_irc::Server::~Server(void)
{
	LOG_INFO("Removed server");
	delete this->_clients[-1];
	this->_clients.erase(-1);
}	// Server::~Server


void
ft_irc::Server::setName(std::string name)
{
	this->_name = name;
}	// Server::setName


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


ft_irc::Channel&
ft_irc::Server::getChannel(const std::string &name) const
{
	for (std::map< std::string, ft_irc::Channel* >::const_iterator it = this->_channels.begin();
		 it != this->_channels.end();
		 it++)
	{
		if (it->second->getName() == name) {
			return *(it->second);
		}
	}

	throw std::runtime_error("Channel not found");
}	// Server::getChannel


std::map< std::string, ft_irc::Channel* >&
ft_irc::Server::getChannels(void)
{
	return this->_channels;
}	// Server::getChannels


void
ft_irc::Server::newClient(void)
{
	ft_irc::Communications &communications = ft_irc::Communications::getInstance();

	if (this->_clients.size() == MAX_CLIENTS) {
		LOG_WARN("newClient: max number of clients in server")

		return;
	}

	struct sockaddr_in clientAddress;
	socklen_t socklen = sizeof(clientAddress);
	int clientFd = accept(communications.getFd(), reinterpret_cast< struct sockaddr* >(&clientAddress), &socklen);

	if (clientFd == -1) {
		LOG_WARN("newClient: accept faild")

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

		case ft_irc::CMD_JOIN: {
			LOG_INFO("execute: executing JOIN")

			this->join(client, cmd);
			break;
		}

		case ft_irc::CMD_PART: {
			LOG_INFO("execute: executing PART")

			this->part(client, cmd);
			break;
		}

		case ft_irc::CMD_INVITE: {
			LOG_INFO("execute: executing INVITE")

			this->invite(client, cmd);
			break;
		}

		case ft_irc::CMD_TOPIC: {
			LOG_INFO("execute: executing TOPIC")

			this->topic(client, cmd);
			break;
		}

		case ft_irc::CMD_QUIT: {
			LOG_INFO("execute: executing QUIT")

			this->quit(client, cmd);
			break;
		}

		case ft_irc::CMD_MODE: {
			LOG_INFO("execute: executing MODE")

			this->mode(client, cmd);
			break;
		}

		case ft_irc::CMD_PRIVMSG: {
			LOG_INFO("execute: executing PRIVMSG")

			this->privmsg(client, cmd);
			break;
		}

		case ft_irc::CMD_PING: {
			LOG_INFO("execute: executing PING")

			this->ping(client, cmd);
			break;
		}

		case ft_irc::CMD_KICK: {
			LOG_INFO("execute: executing KICK")

			this->kick(client, cmd);
			break;
		}

		default: {
			LOG_WARN("Client executed " + ft_irc::toString(cmd->cmd) + " but it's not implemented")
		}
	}	// switch
}	// Server::excecute


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


void
ft_irc::Server::posConnection(ft_irc::Client &client)
{
	client.setStatus(ft_irc::Client::ONLINE);
	LOG_INFO("user: " << client.getMask() << " is online")
	client.sendMsg(ft_irc::getReply(ft_irc::RPL_WELCOME, client.getNickname(), "irc.42.Barcelona", client.getMask()));
	client.sendMsg(ft_irc::getReply(ft_irc::RPL_YOURHOST, client.getNickname(), "irc.42.Barcelona", "1.0"));
	client.sendMsg(ft_irc::getReply(ft_irc::RPL_MYINFO, client.getNickname(), "irc.42.Barcelona", "1.0", "ioOw",
		"beliIkmstn"));
}	// Server::posConnection
