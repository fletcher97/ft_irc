#include <fcntl.h>
#include <netinet/in.h>

#include "Log.hpp"

#include "Communications.hpp"
#include "Parser.hpp"
#include "Server.hpp"

ft_irc::Communications&
ft_irc::Communications::getInstance(void)
{
	static ft_irc::Communications instance;

	return instance;
}	// Communications::getInstance


ft_irc::Communications::Communications(void)
{
	LOG_DEBUG("Creating communitation")
	LOG_INFO("New communitation created")
}


ft_irc::Communications::Communications(const ft_irc::Communications &s) :
	_fd(s._fd),
	_pfds(s._pfds)
{}

ft_irc::Communications&
ft_irc::Communications::operator=(const ft_irc::Communications &s)
{
	this->_fd = s._fd;
	this->_pfds = s._pfds;
	this->_psswd = s._psswd;

	return *this;
}	// =


ft_irc::Communications::~Communications(void) {}

bool
ft_irc::Communications::init(int port, const char *psswd)
{
	if ((this->_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		LOG_FATAL("Error creating socket")

		return false;
	}
	if (fcntl(this->_fd, F_SETFL, O_NONBLOCK) == -1) {
		LOG_FATAL("Error fcntl")

		return false;
	}

	struct sockaddr_in serverAddress;

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(port);
	if (bind(this->_fd, reinterpret_cast< struct sockaddr* >(&serverAddress), sizeof(serverAddress)) == -1) {
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
}	// Communications::init


void
ft_irc::Communications::recvMsg(int fd)
{
	char buffer[COMS_MAX_READ];
	ssize_t size;
	std::string msg;
	std::string line;
	ft_irc::Parser::cmd_t *cmd;

	if ((size = recv(fd, &buffer, COMS_MAX_READ, 0)) == -1) {
		LOG_ERROR("Error recv")

		return;
	}
	if (!size) {
		throw std::exception();
	}
	buffer[size] = '\0';
	LOG_INFO("Message: '" << buffer << "' from: " << fd)
	msg = buffer;
	while (msg.size()) {
		cmd = NULL;
		line = msg.substr(0, msg.find("\r\n"));
		try {
			cmd = ft_irc::Parser::parse_msg(line);
			ft_irc::Server::getInstance().excecute(fd, cmd);
		} catch (...) {
			if (cmd) {
				delete cmd;
			}

			return;
		}

		msg = msg.substr(msg.find("\r\n") + 2, msg.size());
		delete cmd;
	}
}	// Communications::read


void
ft_irc::Communications::sendMsg(int fd, const std::string &msg)
{
	if (send(fd, (msg + "\r\n").c_str(), msg.size() + 2, 0) == -1) {
		LOG_ERROR("send faild");
		throw std::exception();
	}
}	// Communications::send


void
ft_irc::Communications::run(void)
{
	ft_irc::Server &server = ft_irc::Server::getInstance();

	while (42) {
		if (poll(&this->_pfds[0], this->_pfds.size(), -1) == -1) {
			LOG_ERROR("Error poll")
			continue;
		}
		if (this->_pfds[0].revents == POLLIN) {
			server.newClient();
		} else {
			for (pfds_iterator it = this->_pfds.begin(); it != this->_pfds.end(); it++) {
				if (it->revents & POLLNVAL) {
					this->_pfds.erase(it);
					break;
				}
				if (it->revents & POLLHUP) {
					LOG_INFO("Client disconnected: " << it->fd)
					server.deleteClient(it->fd);
					this->_pfds.erase(it);
					break;
				}
				if (it->revents & POLLIN) {
					try {
						this->recvMsg(it->fd);
					} catch (...) {
						LOG_INFO("Client disconnected: " << it->fd)

						server.deleteClient(it->fd);
						this->_pfds.erase(it);
						break;
					}
				}
			}
		}
	}
}	// Communications::run


int
ft_irc::Communications::getFd(void) const
{
	return this->_fd;
}	// Communications::getFd


const std::string&
ft_irc::Communications::getPsswd(void) const
{
	return this->_psswd;
}	// Communications::getPsswd


void
ft_irc::Communications::addPfd(int fd)
{
	this->_pfds.push_back(pollfd());
	this->_pfds.back().fd = fd;
	this->_pfds.back().events = POLLIN;
}	// Communications::addPfd
