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
	(void) fd;
	switch (cmd->cmd) {
		case ft_irc::CMD_CAP: {
				LOG_INFO("Ignoring CAP")
				break;
			}

		case ft_irc::CMD_NICK: {
				LOG_INFO("Excecuting NICK")
				break;
			}

		case ft_irc::CMD_USER: {
				LOG_INFO("Excecuting USER")
				break;
			}

		case ft_irc::CMD_QUIT: {
				LOG_INFO("Excecuting QUIT")
				break;
			}

		default: {
				LOG_WARN("Client executed " + ft_irc::toString(cmd->cmd) + " but it's not implemented")
			}
	}	// switch
}	// Server::excecute
