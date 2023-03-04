#include "Channel.hpp"

Channel::Channel(std::string name) {
	this->_name = name;
}

Channel::Channel(const Channel& c) {
	this->_name = c._name;
	this->_clients = c._clients;
}

Channel &Channel::operator=(const Channel& c) {
	this->_name = c._name;
	this->_clients = c._clients;
	return *this;
}

Channel::~Channel() {}
