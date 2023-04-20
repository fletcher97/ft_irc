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
	for (std::map<int, ft_irc::Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		delete it->second;
	}
	for (std::map<std::string, ft_irc::Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++)
	{
		delete it->second;
	}
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

	if (this->_clients.size() == MAX_CLIENTS)
	{
		LOG_WARN("newClient: max number of clients in server")
		return;
	}

	struct sockaddr_in clientAddress;
	socklen_t socklen = sizeof(clientAddress);
	int clientFd = accept(communications.getFd(), reinterpret_cast< struct sockaddr* >(&clientAddress), &socklen);

	if (clientFd == -1)
	{
		LOG_WARN("newClient: accept faild")
		return;
	}
	this->_clients[clientFd] = new ft_irc::Client(clientFd, clientAddress);
	communications.addPfd(clientFd);
}	// Server::newClient

bool
ft_irc::Server::newChannel(const std::string &channel)
{
	if (channel.length() == 0)
	{
		LOG_WARN("newChannel: empty channel name")
		throw std::invalid_argument("newChannel: Channel name must be a non empty string");
	}
	if (this->_channels.count(channel))
	{
		LOG_WARN("newChannel: channel already exists: " << channel)
		return false;
	}

	ft_irc::Channel *chan = new ft_irc::Channel();

	try
	{
		chan->setName(channel);
	}
	catch (std::invalid_argument &e)
	{
		delete chan;
		throw e;
	}
	this->_channels[channel] = chan;
	return true;
}	// Server::newChannel


bool
ft_irc::Server::isClient(const std::string& nickname) const {
	for (std::map<int, ft_irc::Client*>::const_iterator it = _clients.begin(); it != _clients.end(); it++)
		if (it->second->getNickname() == nickname)
			return true;
	LOG_WARN("isClient: client does not exits: " << nickname)
	return false;
}


ft_irc::Channel&
ft_irc::Server::getChannel(const std::string &channel) {
	return *this->_channels.at(channel);
}


void
ft_irc::Server::deleteClient(int fd)
{
	ft_irc::Client&	client = this->getClient(fd);

	for (std::map<std::string, ft_irc::Channel*>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++)
	{
		if (it->second->isInChannel(client) && it->second->deleteClient(client))
		{
			delete it->second;
			this->_channels.erase(it);
		}
	}
}
