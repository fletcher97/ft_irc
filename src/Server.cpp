#include "Server.hpp"

Server::Server(std::string name) {
	this->_name = name;
}

Server::Server(const Server &s) {
	this->_name = s._name;
}

Server &Server::operator=(const Server &s) {
	this->_name = s._name;
	return *this;
}

Server::~Server() {
	//TODO: Check and clean clients and channels
}
