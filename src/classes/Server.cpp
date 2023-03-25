#include <netinet/in.h>

#include "Log.hpp"

#include "Communications.hpp"
#include "Server.hpp"

ft_irc::Server&
ft_irc::Server::getInstance(void) {
	static ft_irc::Server	instance;
	return instance;
}

ft_irc::Server::Server() {
	LOG_DEBUG("Creating server");
	LOG_INFO("Server created");
}

ft_irc::Server::Server(const ft_irc::Server& s) :
	_clients(s._clients)
{}

ft_irc::Server&
ft_irc::Server::operator=(const ft_irc::Server& s) {
	this->_clients = s._clients;
	return *this;
}

ft_irc::Server::~Server() {
	LOG_INFO("Removed server");
}

void
ft_irc::Server::run() {
	LOG_DEBUG("Running server");
	ft_irc::Communications::getInstance().run();
}

ft_irc::Client&
ft_irc::Server::getClient(const std::string& nickname) const {
	for (std::map<int, ft_irc::Client*>::const_iterator it = _clients.begin(); it != _clients.end(); it++)
		if (it->second->getNickname() == nickname)
			return *(it->second);
	return *(this->_clients.end()->second);
}

ft_irc::Client&
ft_irc::Server::getClient(int fd) const{
	return *(this->_clients.find(fd)->second);
}

void
ft_irc::Server::newClient() {
	ft_irc::Communications&	communications = ft_irc::Communications::getInstance();
	if (this->_clients.size() == MAX_CLIENTS)
		return ;

	struct sockaddr_in	clientAddress;
	socklen_t socklen = sizeof(clientAddress);
	int	clientFd = accept(communications.getFd(), reinterpret_cast<struct sockaddr*>(&clientAddress), &socklen);
	if (clientFd == -1)
		return ;
	this->_clients[clientFd] = new ft_irc::Client(clientFd, clientAddress);
	communications.addPfd(clientFd);
}
