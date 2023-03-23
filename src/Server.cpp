#include "Server.hpp"
#include "Log.hpp"

Server&
Server::getInstance(void) {
	static Server	instance;
	return instance;
}

Server::Server() {
	LOG_DEBUG("Creating server");
	LOG_INFO("Server created");
}

Server::Server(const Server& s) :
	_clients(s._clients)
{}

Server& Server::operator=(const Server& s) {
	this->_clients = s._clients;
	return *this;
}

Server::~Server() {
	LOG_INFO("Removed server");
}

bool
Server::init(int port, std::string psswd) {
	LOG_DEBUG("Initiating server");
	LOG_INFO("Server initiated with port: " << port << " and password: " << psswd);
	return Communications::getInstance().init(port, psswd);
}

void
Server::run() {
	LOG_DEBUG("Running server");
	Communications::getInstance().run();
}

Client&
Server::getClient(const std::string& nickname) const {
	for (std::map<int, Client*>::const_iterator it = _clients.begin(); it != _clients.end(); it++)
		if (it->second->getNickname() == nickname)
			return *(it->second);
	return *(this->_clients.end()->second);
}

Client&
Server::getClient(int fd) const{
	return *(this->_clients.find(fd)->second);
}

void
Server::newClient() {
	Communications&	communications = Communications::getInstance();
	if (this->_clients.size() == MAX_CLIENTS)
		return ;

	struct sockaddr_in	clientAddress;
	socklen_t socklen = sizeof(clientAddress);
	int	clientFd = accept(communications.getFd(), reinterpret_cast<struct sockaddr*>(&clientAddress), &socklen);
	if (clientFd == -1)
		return ;
	this->_clients[clientFd] = new Client(clientFd, clientAddress);
	communications.addPfd(clientFd);
}
