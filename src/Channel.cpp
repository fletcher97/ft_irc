#include "Channel.hpp"
#include "Log.hpp"

Channel::Channel(std::string name) {
	LOG_DEBUG("Creating new channel");
	this->_name = name;
	LOG_INFO("New channel created: " << name);
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

Channel::~Channel() {
	LOG_INFO("Removed channel: " << this->name);
}
