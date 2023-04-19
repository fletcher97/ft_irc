#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

#include "Log.hpp"

#include "Client.hpp"

ft_irc::Client::Client(void) :
	_mode()
{}

ft_irc::Client::Client(int fd, struct sockaddr_in socket) :
	_fd(fd),
	_nickname(),
	_username(),
	_realname(),
	_status(PASSWORD),
	_mode()
{
	LOG_DEBUG("Creating new client")
	this->_hostname = inet_ntoa(socket.sin_addr);
	this->_mode &= CL_WALLOPS;
	LOG_INFO("New client created: " << this->_hostname)
}


ft_irc::Client::Client(const ft_irc::Client &c) :
	_fd(c._fd),
	_hostname(c._hostname),
	_nickname(c._nickname),
	_username(c._username),
	_realname(c._realname),
	_status(c._status),
	_mode(c._mode)
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
ft_irc::Client::getHostname(void) const
{
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
ft_irc::Client::setNickname(const std::string &nickname)
{
	if (nickname.length() == 0) {
		LOG_WARN("setNickname: called with an empty string")
   throw std::invalid_argument("Nickname must be a non empty string");
	}
	if (  (nickname.find(' ') != std::string::npos) || (nickname.find(',') != std::string::npos)
	   || (nickname.find('*') != std::string::npos) || (nickname.find('?') != std::string::npos)
	   || (nickname.find('!') != std::string::npos) || (nickname.find('@') != std::string::npos)
	   || (nickname.find('$') != std::string::npos) || (nickname.find(':') != std::string::npos)
	   || (nickname.find('#') != std::string::npos) || (nickname.find('&') != std::string::npos)
	   || (nickname.find('.') != std::string::npos))
	{
		LOG_WARN("setNickname: called with an invalid character: " << nickname)
   throw std::invalid_argument("Invalid character: " + nickname);
	}
	LOG_INFO("setNickname: changed from '" << this->_nickname << "' to '" << nickname << "'")
	this->_nickname = nickname;
}	// Client::setNickname


void
ft_irc::Client::setUsername(const std::string &username)
{
	if (username.length() == 0) {
		LOG_WARN("setUsername: called with an empty string")
   throw std::invalid_argument("Username must be a non empty string");
	}
	LOG_INFO("setUsername: set to '" << username << "'")
	this->_username = username;
}	// Client::setUsername


void
ft_irc::Client::setRealname(const std::string &realname)
{
	if (realname.length() == 0) {
		LOG_WARN("setRealname: called with an empty string")
   throw std::invalid_argument("Realname must be a non empty string");
	}
	LOG_INFO("setRealname: set to '" << realname << "'")
	this->_realname = realname;
}	// Client::setRealname


void
ft_irc::Client::setStatus(ft_irc::Client::Status status)
{
	LOG_INFO("setStatus: status changed")
	this->_status = status;
}	// Client::setStatus


void
ft_irc::Client::toggleMode(const client_mode mode)
{
	if ((mode > (CL_NETWORK_OPER | CL_LOCAL_OPER | CL_INVISIBLE | CL_WALLOPS)) || (mode <= 0)) {
		LOG_WARN("toggleMode: invalid mode: " << std::showbase << std::hex << std::uppercase << int(mode))
   throw ft_irc::Client::InvalidMode("Invalid mode");
	}
	LOG_INFO("toggleMode: " << std::showbase << std::hex << std::uppercase << int(mode))
	this->_mode ^= mode;
}	// Client::toggleMode


std::string
ft_irc::Client::getMask(void) const
{
	return this->_nickname + "!" + this->_username + "@" + this->_hostname;
}	// Client::getMask


ft_irc::Client::InvalidMode::InvalidMode(std::string msg) :
	std::invalid_argument(msg)
{}
