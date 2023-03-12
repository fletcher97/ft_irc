#include "Channel.hpp"
#include "Log.hpp"

Channel::Channel() :	_name(),
											_topic(),
											_clients(),
											_key()
{
	LOG_DEBUG("Creating new channel");
}

Channel::Channel(const Channel& c) :	_name(c._name),
																			_topic(c._topic),
																			_clients(c._clients),
																			_key(c._key)
{}

Channel &Channel::operator=(const Channel& c) {
	this->_name = c.getName();
	this->_topic = c.getTopic();
	this->_clients = c._clients;
	this->_key = c.getKey();
	return *this;
}

Channel::~Channel() {
	LOG_INFO("Removed channel: " << this->_name);
}

std::string
Channel::getName() const {
	return this->_name;
}

std::string
Channel::getTopic() const {
	return this->_topic;
}

std::string
Channel::getKey() const {
	return this->_key;
}

// std::vector<Client*>
// Channel::getClients() const {
	
// }

void
Channel::setName(std::string name) {
	this->_name = name;
}

void
Channel::setTopic(std::string topic) {
	this->_topic = topic;
}

void
Channel::setKey(std::string key) {
	this->_key = key;
}

bool
Channel::isInChannel(const Client& client) {
	if (this->_clients.count(client.getFd()) == 1)
		return true;
	return false;
}
