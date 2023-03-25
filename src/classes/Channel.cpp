#include "Log.hpp"

#include "Channel.hpp"

ft_irc::Channel::Channel(void) :
	_name(),
	_topic(),
	_clients(),
	_key()
{
	LOG_DEBUG("Creating new channel");
}

ft_irc::Channel::Channel(const ft_irc::Channel& c) :
	_name(c._name),
	_topic(c._topic),
	_clients(c._clients),
	_key(c._key)
{}

ft_irc::Channel&
ft_irc::Channel::operator=(const ft_irc::Channel& c) {
	this->_name = c._name;
	this->_topic = c._topic;
	this->_clients = c._clients;
	this->_key = c._key;
	return *this;
}

ft_irc::Channel::~Channel(void) {
	LOG_INFO("Removed channel: " << this->_name);
}

const std::string&
ft_irc::Channel::getName(void) const {
	return this->_name;
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
	this->_name = name;
}

void
ft_irc::Channel::setTopic(std::string& topic) {
	this->_topic = topic;
}

void
ft_irc::Channel::setKey(std::string& key) {
	this->_key = key;
}

bool
ft_irc::Channel::isInChannel(const ft_irc::Client& client) {
	return this->_clients.count(client.getFd());
}
