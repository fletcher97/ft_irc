#include "ServerUT.hpp"

#include <sys/socket.h>
#include <netinet/in.h>

#include <iostream>


ServerUT::ServerUT(void) : flt::Testable<ServerUT>("Server"), Server() {
	REGISTER(ServerUT, test_getClient_fd)
	REGISTER(ServerUT, test_getClient_nick)
}

ServerUT::~ServerUT(void) {}

void ServerUT::test_getClient_fd(void) {
	struct sockaddr_in clientSocket;
	int clientFd = 15;
	std::string nickname = "gemartin42";
	std::string username = "gerard42";
	std::string realname = "gerard";
	Client::Status status = Client::ONLINE;

	this->_clients[clientFd] = new Client(clientFd, clientSocket);
	this->_clients[clientFd]->setNickname(nickname);
	this->_clients[clientFd]->setUsername(username);
	this->_clients[clientFd]->setRealname(realname);
	this->_clients[clientFd]->setStatus(status);

	ASSERT_EQ(this->_clients[clientFd]->getFd(), clientFd)
	delete this->_clients[clientFd];

	Client& client1 = *(this->_clients[clientFd]);
	Client& client2 = getClient(clientFd);

	ASSERT_EQ(&client1, &client2)
}

void ServerUT::test_getClient_nick(void) {
	struct sockaddr_in clientSocket;
	int clientFd = 18;
	std::string nickname = "gemartin42";
	std::string username = "gerard42";
	std::string realname = "gerard";
	Client::Status status = Client::ONLINE;

	this->_clients[clientFd] = new Client(clientFd, clientSocket);
	this->_clients[clientFd]->setNickname(nickname);
	this->_clients[clientFd]->setUsername(username);
	this->_clients[clientFd]->setRealname(realname);
	this->_clients[clientFd]->setStatus(status);

	ASSERT_EQ(this->_clients[clientFd]->getNickname(), nickname)
    delete this->_clients[clientFd];
	
	Client& client1 = *(this->_clients[clientFd]);
	Client& client2 = getClient(nickname);

	ASSERT_EQ(&client1, &client2)
}

