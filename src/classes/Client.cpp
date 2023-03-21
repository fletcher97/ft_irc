#include <stdexcept>

#include "Client.hpp"
#include "Log.hpp"

static bool
isNickValid(std::string& nick) {
	if (nick.length() == 0)
		return false;
	return true;
}

Client::Client(std::string nick, std::string address, std::string username) {
	LOG_DEBUG("Creating new client")
	if (!isNickValid(nick)) {
		LOG_INFO("Nick verification failed");
		throw std::invalid_argument("Invalid nickname");
	}
	this->_nick = nick;
	this->_address = address;
	this->_username = username;
	LOG_INFO("New client created: " << this->_nick)
}

Client::Client(const Client &c) {
	this->_nick = c._nick;
	this->_address = c._address;
	this->_username = c._username;
	this->_channels = c._channels;
}

Client&
Client::operator=(const Client &c) {
	this->_nick = c._nick;
	this->_address = c._address;
	this->_username = c._username;
	this->_channels = c._channels;
	return *this;
}

Client::~Client() {
	// TODO: Check and exit from channels
	LOG_INFO("Removed client: " << this->_nick)
}
