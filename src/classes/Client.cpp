#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

#include "Log.hpp"

#include "Client.hpp"

Client::Client(void) {}

Client::Client(int fd, struct sockaddr_in socket) :
	_fd(fd),
	_nickname(),
	_username(),
	_realname(),
	_status(PASSWORD)
{
	LOG_DEBUG("Creating new client")
	this->_address = inet_ntoa(socket.sin_addr);
	LOG_INFO("New client created: " << this->_hostname)
}

Client::Client(const Client &c) :
	_fd(c._fd),
	_address(c._address),
	_hostname(c._hostname),
	_nickname(c._nickname),
	_username(c._username),
	_realname(c._realname),
	_status(c._status)
{}

Client&
Client::operator=(const Client &c) {
	this->_fd = c._fd;
	this->_address = c._address;
	this->_hostname = c._hostname;
	this->_nickname = c._nickname;
	this->_username = c._username;
	this->_realname = c._realname;
	this->_status = c._status;
	return *this;
}

Client::~Client() {
	close(this->_fd);
	LOG_INFO("Removed client: " << this->_nickname)
}

int
Client::getFd() const {
	return this->_fd;
}

const std::string&
Client::getAddress() const {
	return this->_address;
}

const std::string&
Client::getHostname() const {
	return this->_hostname;
}

const std::string&
Client::getNickname() const {
	return this->_nickname;
}

const std::string&
Client::getUsername() const {
	return this->_username;
}

const std::string&
Client::getRealname() const {
	return this->_realname;
}

Client::Status
Client::getStatus() const {
	return this->_status;
}

void
Client::setNickname(std::string& nickname) {
	this->_nickname = nickname;
}

void
Client::setUsername(std::string& username) {
	this->_username = username;
}

void
Client::setRealname(std::string& realname) {
	this->_realname = realname;
}

void
Client::setStatus(Client::Status status) {
	this->_status = status;
}
