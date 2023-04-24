#include <netinet/in.h>

#include "Log.hpp"

#include "Server.hpp"
#include "Communications.hpp"

ft_irc::Server&
ft_irc::Server::getInstance(void)
{
	static ft_irc::Server instance;

	return instance;
}	// Server::getInstance


ft_irc::Server::Server(void)
{
	LOG_DEBUG("Creating server");
	LOG_INFO("Server created");
}


ft_irc::Server::Server(const ft_irc::Server &s) :
	_clients(s._clients)
{}

ft_irc::Server&
ft_irc::Server::operator=(const ft_irc::Server &s)
{
	this->_clients = s._clients;

	return *this;
}	// Server::operator=


ft_irc::Server::~Server(void)
{
	LOG_INFO("Removed server");
}	// Server::~Server


void
ft_irc::Server::run(void)
{
	LOG_DEBUG("Running server");
	ft_irc::Communications::getInstance().run();
}	// Server::run


ft_irc::Client&
ft_irc::Server::getClient(const std::string &nickname) const
{
	for (std::map< int, ft_irc::Client* >::const_iterator it = _clients.begin(); it != _clients.end(); it++) {
		if (it->second->getNickname() == nickname) {
			return *(it->second);
		}
	}

	return *(this->_clients.end()->second);
}	// Server::getClient


ft_irc::Client&
ft_irc::Server::getClient(int fd) const
{
	return *(this->_clients.find(fd)->second);
}	// Server::getClient


void
ft_irc::Server::newClient(void)
{
	ft_irc::Communications &communications = ft_irc::Communications::getInstance();

	if (this->_clients.size() == MAX_CLIENTS) {
		return;
	}

	struct sockaddr_in clientAddress;
	socklen_t socklen = sizeof(clientAddress);
	int clientFd = accept(communications.getFd(), reinterpret_cast< struct sockaddr* >(&clientAddress), &socklen);

	if (clientFd == -1) {
		return;
	}
	this->_clients[clientFd] = new ft_irc::Client(clientFd, clientAddress);
	communications.addPfd(clientFd);
}	// Server::newClient


void
ft_irc::Server::sendMsg(int fd, const std::string &msg)
{
	ft_irc::Communications::getInstance().sendMsg(fd, msg);
}	// Server::send


void
ft_irc::Server::excecute(int fd, const ft_irc::Parser::cmd_t *cmd)
{
	ft_irc::Client &client = this->getClient(fd);

	if (  (client.getStatus() == ft_irc::Client::PASSWORD)
	   && ((cmd->cmd != ft_irc::CMD_PASS) && (cmd->cmd != ft_irc::CMD_CAP)))
	{
		LOG_DEBUG(ft_irc::toString(cmd->cmd))
		this->error(client, "Password required");
		this->quit(client, NULL);
		throw std::exception();

		return;
	}

	switch (cmd->cmd) {
		case ft_irc::CMD_CAP: {
				LOG_INFO("execute: CAP Ignored")

				break;
			}

		case ft_irc::CMD_PASS: {
				LOG_INFO("execute: executing PASS")

				this->pass(client, cmd);
				break;
			}

		case ft_irc::CMD_NICK: {
				LOG_INFO("execute: executing NICK")

				this->nick(client, cmd);
				break;
			}

		case ft_irc::CMD_USER: {
				LOG_INFO("execute: executing USER")

				this->user(client, cmd);
				break;
			}

		case ft_irc::CMD_QUIT: {
				LOG_INFO("execute: executing QUIT")

				this->quit(client, cmd);
				break;
			}

		default: {
				LOG_WARN("Client executed " + ft_irc::toString(cmd->cmd) + " but it's not implemented")
			}
	}	// switch
}	// Server::excecute


void
ft_irc::Server::pass(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	if (client.getStatus() != ft_irc::Client::PASSWORD) {
		LOG_WARN("pass: 462: client already registered")

		return client.sendMsg("462: ");
	}
	if (cmd->args.empty() || cmd->args.front().empty()) {
		LOG_WARN("pass: 461: need more params")

		return client.sendMsg("461: ");
	}
	if (cmd->args.front() != ft_irc::Communications::getInstance().getPsswd()) {
		LOG_WARN("pass: 464: password mismatch: " << cmd->args.front())

		client.sendMsg("464: ");
		this->error(client, "Password mismatch");
		this->quit(client, NULL);
		throw std::invalid_argument("Password mismatch");
	}
	client.setStatus(ft_irc::Client::REGISTER);
}	// Server::pass


void
ft_irc::Server::nick(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	std::string old_nick;

	if (cmd->args.empty()) {
		LOG_WARN("nick: 431: need more param")

		return client.sendMsg("431: ");
	}
	for (std::map< int, ft_irc::Client* >::iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		if (it->second->getNickname() == cmd->args.front()) {
			LOG_WARN("nick: 433: " << cmd->args.front() << " is already in use")

			return client.sendMsg("433: ");
		}
	}
	old_nick = client.getNickname();
	try {
		client.setNickname(cmd->args.front());
	} catch (...) {
		LOG_WARN("nick: 433: invalid character in nickname: " << cmd->args.front())

		return client.sendMsg("432: ");
	}

	LOG_INFO("nick: " << old_nick << " set to " << cmd->args.front())
	client.sendMsg(":" + old_nick + " " + ft_irc::toString(cmd->cmd) + " " + client.getNickname());
}	// Server::nick


void
ft_irc::Server::user(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	if (client.getStatus() != ft_irc::Client::REGISTER) {
		LOG_WARN("user: 462: client already registered: " << cmd->args.front())

		return client.sendMsg("462: ");
	}
	if (cmd->args.empty() || cmd->args.front().empty()) {
		LOG_WARN("user: 461: Need more params")

		return client.sendMsg("461: ");
	}
	client.setUsername(cmd->args.front());
	client.setRealname(cmd->args.back());
	client.setStatus(ft_irc::Client::ONLINE);
}	// Server::user


void
ft_irc::Server::quit(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd)
{
	int fd;

	if (cmd) {
		this->error(client, cmd->args.front());
	}
	LOG_INFO("Deleting client: " << client.getNickname())
	fd = client.getFd();
	delete this->_clients[fd];
	this->_clients.erase(fd);
}	// Server::quit


void
ft_irc::Server::error(ft_irc::Client &client, const std::string reason)
{
	client.sendMsg("ERROR :" + reason);
}	// Server::error
