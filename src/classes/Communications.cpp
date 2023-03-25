#include <fcntl.h>
#include <netinet/in.h>

#include "Log.hpp"

#include "Communications.hpp"
#include "Server.hpp"

ft_irc::Communications&
ft_irc::Communications::getInstance(void) {
	static ft_irc::Communications	instance;
	return instance;
}

ft_irc::Communications::Communications()
{
	LOG_DEBUG("Creating communitation")
	LOG_INFO("New communitation created")
}

ft_irc::Communications::Communications(const ft_irc::Communications& s) :
	_fd(s._fd),
	_pfds(s._pfds),
	_psswd(s._psswd)
{}

ft_irc::Communications&
ft_irc::Communications::operator=(const ft_irc::Communications& s) {
	this->_fd = s._fd;
	this->_pfds = s._pfds;
	this->_psswd = s._psswd;
	return *this;
}

ft_irc::Communications::~Communications() {}

bool
ft_irc::Communications::init(int port, const char* psswd) {
	if ((this->_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		LOG_FATAL("Error creating socket")
		return false;
	}
	if (fcntl(this->_fd, F_SETFL, O_NONBLOCK) == -1) {
		LOG_FATAL("Error fcntl")
		return false;
	}

	struct sockaddr_in	serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(port);
	if (bind(this->_fd, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
		LOG_FATAL("Error binding")
		return false;
	}
	if (listen(this->_fd, MAX_CLIENTS) == -1) {
		LOG_FATAL("Error listening");
		return false;
	}
	this->addPfd(this->_fd);
	this->_psswd = psswd;
	LOG_INFO("Listening on port " << port)
	return true;
}

void
ft_irc::Communications::run(void) {
	ft_irc::Server&	server = ft_irc::Server::getInstance();
	while (42) {
		if (poll(&this->_pfds[0], this->_pfds.size(), -1) == -1) {
			LOG_ERROR("Error poll")
			continue;
		}
		if (this->_pfds[0].revents == POLLIN)
			server.newClient();
		else
			for(pfds_iterator it = this->_pfds.begin(); it != this->_pfds.end(); it++)
				if ((*it).revents == POLLIN)
					server.getClient(it->fd);
	}
}

int
ft_irc::Communications::getFd() const {
	return this->_fd;
}

void
ft_irc::Communications::addPfd(int fd) {
	this->_pfds.push_back(pollfd());
	this->_pfds.back().fd = fd;
	this->_pfds.back().events = POLLIN;
}
