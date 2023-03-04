#include <stdexcept>

#include "Client.hpp"

static bool
isNickValid(std::string& nick) {
	if (nick.length() == 0)
		return false;
	return true;
}

Client::Client(std::string nick, std::string address, std::string username) {
	if (!isNickValid(nick))
		throw std::invalid_argument("Invalid nickname");
	this->_nick = nick;
	this->_address = address;
	this->_username = username;
}

Client::Client(const Client &c) {
	this->_nick = c._nick;
	this->_address = c._address;
	this->_username = c._username;
}

Client &Client::operator=(const Client &c) {
	this->_nick = c._nick;
	this->_address = c._address;
	this->_username = c._username;
	return *this;
}

Client::~Client() {}
