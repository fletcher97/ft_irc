#include <stdexcept>

#include "Client.hpp"
#include "Log.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>

ClientMode::ClientMode() :	a(false),
														i(false),
														w(false),
														r(false),
														o(false),
														O(false),
														s(false)
{}

ClientMode::ClientMode(const ClientMode& m) :	a(m.a),
																							i(m.i),
																							w(m.w),
																							r(m.r),
																							o(m.o),
																							O(m.O),
																							s(m.s)
{}

ClientMode&
ClientMode::operator=(const ClientMode& m) {
	this->a = m.a;
	this->i = m.i;
	this->w = m.w;
	this->r = m.r;
	this->o = m.o;
	this->O = m.O;
	this->s = m.s;
	return *this;
}

Client::Client(int fd, struct sockaddr_in socket) :	_fd(fd),
																							_nickname(),
																							_username(),
																							_realname(),
																							_channels(),
																							_status(PASSWORD),
																							_mode()
{
	LOG_DEBUG("Creating new client")
	this->_address = inet_ntoa(socket.sin_addr);
	LOG_INFO("New client created: " << this->_hostname)
}

Client::Client(const Client &c) :	_fd(c._fd),
																	_address(c._address),
																	_hostname(c._hostname),
																	_nickname(c._nickname),
																	_username(c._username),
																	_realname(c._realname),
																	_channels(c._channels),
																	_status(c._status),
																	_mode(c._mode)
{}

Client&
Client::operator=(const Client &c) {
	this->_fd = c.getFd();
	this->_address = c.getAddress();
	this->_hostname = c.getHostname();
	this->_nickname = c.getNickname();
	this->_username = c.getUsername();
	this->_realname = c.getRealname();
	this->_channels = c._channels;
	this->_status = c.getStatus();
	this->_mode = c._mode;
	return *this;
}

Client::~Client() {
	// TODO: Check and exit from channels
	close(this->_fd);
	LOG_INFO("Removed client: " << this->_nickname)
}

int
Client::getFd() const {
	return this->_fd;
}

std::string
Client::getAddress() const {
	return this->_address;
}

std::string
Client::getHostname() const {
	return this->_hostname;
}

std::string
Client::getNickname() const {
	return this->_nickname;
}

std::string
Client::getUsername() const {
	return this->_username;
}

std::string
Client::getRealname() const {
	return this->_realname;
}

ClientStatus
Client::getStatus() const {
	return this->_status;
}

// std::vector<Channel&>
// Client::getChannels() const {
// 	TODO
// }

bool
Client::getMode(char c) const
{
	switch (c)
	{
		case 'a' : return this->_mode.a;
		case 'i' : return this->_mode.i;
		case 'w' : return this->_mode.w;
		case 'r' : return this->_mode.r;
		case 'o' : return this->_mode.o;
		case 'O' : return this->_mode.O;
		case 's' : return this->_mode.s;
		default : return false;
	}
}

void
Client::setNickname(std::string nickname) {
	this->_nickname = nickname;
}

void
Client::setUsername(std::string username) {
	this->_username = username;
}

void
Client::setRealname(std::string realname) {
	this->_realname = realname;
}

void
Client::setStatus(ClientStatus status) {
	this->_status = status;
}

void
Client::setMode(char c) {
	switch (c)
	{
		case 'a' : this->_mode.a = true;
		case 'i' : this->_mode.i = true;
		case 'w' : this->_mode.w = true;
		case 'r' : this->_mode.r = true;
		case 'o' : this->_mode.o = true;
		case 'O' : this->_mode.O = true;
		case 's' : this->_mode.s = true;
		default : return ;
	}
}

void
Client::unsetMode(char c) {
	switch (c)
	{
		case 'a' : this->_mode.a = false;
		case 'i' : this->_mode.i = false;
		case 'w' : this->_mode.w = false;
		case 'r' : this->_mode.r = false;
		case 'o' : this->_mode.o = false;
		case 'O' : this->_mode.O = false;
		case 's' : this->_mode.s = false;
		default : return ;
	}
}
