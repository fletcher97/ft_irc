#include "Log.hpp"

#include "Channel.hpp"

Channel::Channel(void) :
	__name(),
	_topic(),
	_clients(),
	_key()
{
	LOG_DEBUG("Creating new channel");
}

Channel::Channel(const Channel& c) :
	__name(c.__name),
	_topic(c._topic),
	_clients(c._clients),
	_key(c._key)
{}

Channel&
Channel::operator=(const Channel& c) {
	this->__name = c.__name;
	this->_topic = c._topic;
	this->_clients = c._clients;
	this->_key = c._key;
	return *this;
}

Channel::~Channel(void) {
	LOG_INFO("Removed channel: " << this->__name);
}

const std::string&
Channel::getName(void) const {
	return this->__name;
}

const std::string&
Channel::getTopic(void) const {
	return this->_topic;
}

const std::string&
Channel::getKey(void) const {
	return this->_key;
}

void
Channel::setName(std::string& name) {
	if (name.length() == 0)
		throw EmptyArgument("Name must be a non empty string");
	this->__name = name;
}

void
Channel::setTopic(std::string& topic) {
	if (topic.length() == 0)
		throw EmptyArgument("Topic must be a non empty string");
	this->_topic = topic;
}

void
Channel::setKey(std::string& key) {
	if (key.length() == 0)
		throw EmptyArgument("Key must be a non empty string");
	this->_key = key;
}

bool
Channel::isInChannel(const Client& client) {
	return this->_clients.count(client.getFd());
}

Channel::EmptyArgument::EmptyArgument(std::string msg) : std::invalid_argument(msg)
{}
