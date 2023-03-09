#include "Server.hpp"
#include "Log.hpp"

Server::Server(std::string name) {
	LOG_DEBUG("Creating new server");
	this->_name = name;
	LOG_INFO("New server created: " << this->_name);
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
	LOG_INFO("Removed server: " << this->_name);
}
