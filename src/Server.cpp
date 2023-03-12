#include "Server.hpp"
#include "Log.hpp"

Server::Server()
{
	LOG_DEBUG("Creating new server");
	LOG_INFO("New server created");
}

Server::Server(const Server &s) : _fd(s._fd),
																	_clients(s._clients),
																	_channels(s._channels)
{}

Server &Server::operator=(const Server &s) {
	this->_fd = s._fd;
	this->_clients = s._clients;
	this->_channels = s._channels;
	return *this;
}

Server::~Server() {
	//TODO: Check and clean clients and channels
	LOG_INFO("Removed server: " << this->_name);
}

void
Server::init()
{}

void
Server::run()
{}

Client&
Server::getClient(const std::string& nickname) {
	for (std::map<int, Client&>::iterator it = _clients.begin(); it != _clients.end(); it++)
		if ((*it).second.getNickname() == nickname)
			return (*it).second;
	return _clients.end()->second;
}

Channel&
Server::getChannel(const std::string& name) {
	Channel& channel = _channels[name];
	channel.setName(name);
	return channel;
}

std::vector<Client*>
Server::getClients() {
	std::vector<Client*>	clients_vec;
	for (clients_iterator it = _clients.begin(); it != _clients.end(); it++)
		clients_vec.push_back(&(*it).second);
	return clients_vec;
}

std::vector<Channel*>
Server::getChannels() {
	std::vector<Channel*>	channels_vec;
	for (channels_iterator it = _channels.begin(); it != _channels.end(); it++)
		channels_vec.push_back(&(*it).second);
	return channels_vec;
}

// void
// Server::delClient(Client& client)
// {}

// void
// Server::delChannel(Client& channel)
// {}

// bool
// Server::isChannel(const std::string& name) const
// {}
