#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

#include "Log.hpp"

#include "Client.hpp"

#define I 0x01 // Invisible
#define W 0x02 // Recives Wallops
#define O 0x04 // Operator
#define _O 0x08 // Local operator

ft_irc::Client::Client(void) {}

ft_irc::Client::Client(int fd, struct sockaddr_in socket) :
	_fd(fd),
	_nickname(),
	_username(),
	_realname(),
	_status(PASSWORD)
{
	LOG_DEBUG("Creating new client")
	this->_hostname = inet_ntoa(socket.sin_addr);
	this->_mode &= W;
	LOG_INFO("New client created: " << this->_address)
}


ft_irc::Client::Client(const ft_irc::Client &c) :
	_fd(c._fd),
	_hostname(c._hostname),
	_nickname(c._nickname),
	_username(c._username),
	_realname(c._realname),
	_status(c._status)
{}

ft_irc::Client&
ft_irc::Client::operator=(const ft_irc::Client &c)
{
	this->_fd = c._fd;
	this->_hostname = c._hostname;
	this->_nickname = c._nickname;
	this->_username = c._username;
	this->_realname = c._realname;
	this->_status = c._status;

	return *this;
}	// =


ft_irc::Client::~Client(void)
{
	close(this->_fd);
	LOG_INFO("Removed client: " << this->_nickname)
}


int
ft_irc::Client::getFd(void) const
{
	return this->_fd;
}	// Client::getFd


const std::string&
ft_irc::Client::getHostname(void) const {
	return this->_hostname;
}	// Client::getHostname


const std::string&
ft_irc::Client::getNickname(void) const
{
	return this->_nickname;
}	// Client::getNickname


const std::string&
ft_irc::Client::getUsername(void) const
{
	return this->_username;
}	// Client::getUsername


const std::string&
ft_irc::Client::getRealname(void) const
{
	return this->_realname;
}	// Client::getRealname


ft_irc::Client::Status
ft_irc::Client::getStatus(void) const
{
	return this->_status;
}	// Client::getStatus


void
ft_irc::Client::setNickname(const std::string& nickname) {
	if (nickname.length() == 0)
		throw std::invalid_argument("Nickname must be a non empty string");
	this->_nickname = nickname;
}	// Client::setNickname


void
ft_irc::Client::setUsername(const std::string& username) {
	if (username.length() == 0)
		throw std::invalid_argument("Username must be a non empty string");
	this->_username = username;
}	// Client::setUsername


void
ft_irc::Client::setRealname(const std::string& realname) {
	if (realname.length() == 0)
		throw std::invalid_argument("Realname must be a non empty string");
	this->_realname = realname;
}	// Client::setRealname


void
ft_irc::Client::setStatus(ft_irc::Client::Status status)
{
	this->_status = status;
}	// Client::setStatus


std::string
ft_irc::Client::getMask(void) const
{
	return this->_nickname + "!" + this->_username + "@" + this->_hostname;
}	// Client::getMask
