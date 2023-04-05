#include <algorithm>

#include "Log.hpp"

#include "Channel.hpp"

ft_irc::Channel::Channel(void) :
	__name(),
	_topic(),
	_key(),
	_clients()
{
	LOG_DEBUG("Creating new channel");
}

ft_irc::Channel::Channel(const std::string& name) :
	__name(name),
	_topic(),
	_key(),
	_clients()
{
	LOG_DEBUG("Creating new channel")
	LOG_INFO("New channel created: " << name)
}

ft_irc::Channel::Channel(const ft_irc::Channel& c) :
	__name(c.__name),
	_topic(c._topic),
	_key(c._key),
	_clients(c._clients)
{}

ft_irc::Channel&
ft_irc::Channel::operator=(const ft_irc::Channel& c) {
	this->__name = c.__name;
	this->_topic = c._topic;
	this->_key = c._key;
	this->_clients = c._clients;
	return *this;
}

ft_irc::Channel::~Channel(void) {
	LOG_INFO("Removed channel: " << this->__name);
}

const std::string&
ft_irc::Channel::getName(void) const {
	return this->__name;
}

const std::string&
ft_irc::Channel::getTopic(void) const {
	return this->_topic;
}

const std::string&
ft_irc::Channel::getKey(void) const {
	return this->_key;
}

void
ft_irc::Channel::setName(std::string& name) {
	if (name.length() == 0)
		throw EmptyArgument("Name must be a non empty string");
	this->__name = name;
}

void
ft_irc::Channel::setTopic(std::string& topic) {
	if (topic.length() == 0)
		throw EmptyArgument("Topic must be a non empty string");
	this->_topic = topic;
}

void
ft_irc::Channel::setKey(std::string& key) {
	if (key.length() == 0)
		throw EmptyArgument("Key must be a non empty string");
	this->_key = key;
}

bool
ft_irc::Channel::isInChannel(const ft_irc::Client& client) {
	return this->_clients.count(client.getFd());
}

bool
ft_irc::Channel::addClient(ft_irc::Client client) {
	if (this->_clients.count(client.getFd()))
		return false;
	this->_clients[client.getFd()] = &client;
	return true;
}

bool
ft_irc::Channel::banClient(const std::string& client) {
	if (std::count(this->_banned.begin(), this->_banned.end(), client))
		return false;
	this->_banned.push_back(client);
	return true;
}

ft_irc::Channel::EmptyArgument::EmptyArgument(std::string msg) : std::invalid_argument(msg)
{}

ft_irc::Channel::InvalidKey::InvalidKey(std::string msg) : std::invalid_argument(msg)
{}
