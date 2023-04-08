#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

#include "Log.hpp"

#include "Client.hpp"

ft_irc::Client::Client(void) {}

ft_irc::Client::Client(int fd, struct sockaddr_in socket) :
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

ft_irc::Client::Client(const ft_irc::Client &c) :
	_fd(c._fd),
	_address(c._address),
	_hostname(c._hostname),
	_nickname(c._nickname),
	_username(c._username),
	_realname(c._realname),
	_status(c._status)
{}

ft_irc::Client&
ft_irc::Client::operator=(const ft_irc::Client &c) {
	this->_fd = c._fd;
	this->_address = c._address;
	this->_hostname = c._hostname;
	this->_nickname = c._nickname;
	this->_username = c._username;
	this->_realname = c._realname;
	this->_status = c._status;
	return *this;
}

ft_irc::Client::~Client(void) {
	close(this->_fd);
	LOG_INFO("Removed client: " << this->_nickname)
}

int
ft_irc::Client::getFd(void) const {
	return this->_fd;
}

const std::string&
ft_irc::Client::getAddress(void) const {
	return this->_address;
}

const std::string&
ft_irc::Client::getHostname(void) const {
	return this->_hostname;
}

const std::string&
ft_irc::Client::getNickname(void) const {
	return this->_nickname;
}

const std::string&
ft_irc::Client::getUsername(void) const {
	return this->_username;
}

const std::string&
ft_irc::Client::getRealname(void) const {
	return this->_realname;
}

ft_irc::Client::Status
ft_irc::Client::getStatus(void) const {
	return this->_status;
}

void
Client::setNickname(const std::string& nickname) {
	if (nickname.length() == 0)
		throw EmptyArgument("Nickname must be a non empty string");
	this->_nickname = nickname;
}

void
Client::setUsername(const std::string& username) {
	if (username.length() == 0)
		throw EmptyArgument("Username must be a non empty string");
	this->_username = username;
}

void
Client::setRealname(const std::string& realname) {
	if (realname.length() == 0)
		throw EmptyArgument("Realname must be a non empty string");
	this->_realname = realname;
}

void
ft_irc::Client::setStatus(ft_irc::Client::Status status) {
	this->_status = status;
}

Client::EmptyArgument::EmptyArgument(std::string msg) : std::invalid_argument(msg)
{}

std::string
ft_irc::Client::getMask(void) const {
	return this->_nickname + "!" + this->_username + "@" + this->_address;
}
