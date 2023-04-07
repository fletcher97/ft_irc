#include <algorithm>

#include "Log.hpp"

#include "Channel.hpp"

ft_irc::Channel::Channel(void) :
	__name(),
	_topic(),
	_key(),
	_clients(),
	_mode(),
	_client_limit()
{
	LOG_DEBUG("Creating new channel");
}

ft_irc::Channel::Channel(const std::string& name) :
	__name(name),
	_topic(),
	_key(),
	_mode(),
	_client_limit()
{
	LOG_DEBUG("Creating new channel")
	LOG_INFO("New channel created: " << name)
}

ft_irc::Channel::Channel(const ft_irc::Channel& c) :
	__name(c.__name),
	_topic(c._topic),
	_key(c._key),
	_clients(c._clients),
	_mode(c._mode),
	_client_limit(c._client_limit)
{}

ft_irc::Channel&
ft_irc::Channel::operator=(const ft_irc::Channel& c) {
	this->__name = c.__name;
	this->_topic = c._topic;
	this->_key = c._key;
	this->_clients = c._clients;
	this->_mode = c._mode;
	this->_client_limit = c._client_limit;
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
		throw ft_irc::Channel::EmptyArgument("Name must be a non empty string");
	this->__name = name;
}

void
ft_irc::Channel::setTopic(std::string& topic) {
	if (topic.length() == 0)
		throw ft_irc::Channel::EmptyArgument("Topic must be a non empty string");
	this->_topic = topic;
}

void
ft_irc::Channel::setKey(std::string& key) {
	if (key.length() == 0)
		throw ft_irc::Channel::EmptyArgument("Key must be a non empty string");
	this->_key = key;
}

void
ft_irc::Channel::setClientLimit(size_t limit) {
	if (limit == 0)
		throw ft_irc::Channel::InvalidLimit("Invalid limit");
	this->_client_limit = limit;
}

void
ft_irc::Channel::toggleMode(const  char& mode) {
	if (mode <= (I|M|S|_T|N)) {
		this->_mode ^= mode;
		return ;
	}
	throw ft_irc::Channel::InvalidMode("Invalid mode");
}

bool
ft_irc::Channel::isInChannel(const ft_irc::Client& client) {
	return this->_clients.count(client.getFd());
}

bool
ft_irc::Channel::addClient(const ft_irc::Client& client) {
	if (this->_clients.count(client.getFd()))
		return false;
	this->_clients.insert(
		std::make_pair(client.getFd(), ft_irc::Channel::ClientInfo(client)));
	if (this->_clients.size() == 1)
		this->_clients.begin()->second.mode &= Q;
	return true;
}

bool
ft_irc::Channel::banMask(const std::string& mask) {
	if (this->_masks.count(mask)) {
		if (this->_masks[mask] & B)
			return false;
		this->_masks[mask] ^= B;
	}
	this->_masks.insert(std::make_pair(mask, B));
	return true;
}

// bool
// ft_irc::Channel::inviteClient(const std::string& client) {
// 	if (std::count(this->_invited.begin(), this->_invited.end(), client))
// 		return false;
// 	this->_invited.push_back(client);
// 	return true;
// }

bool
ft_irc::Channel::join(const ft_irc::Client& client, const std::string& key) {
	if (this->_clients.count(client.getFd()))
		return false;
	// if (std::count(this->_banned.begin(), this->_banned.end(), client.getNickname()))
	// 	throw ft_irc::Channel::BannedClient();
	// if (this->_mode & I &&
	// 	!std::count(this->_invited.begin(), this->_invited.end(), client.getNickname()))
	// 	throw ft_irc::Channel::InviteOnlyChannel();
	// if (this->_client_limit != 0 && this->_client_limit >= this->_clients.size())
	// 	throw ft_irc::Channel::ChannelIsFull();
	if (!this->_key.empty() && this->_key != key)
		throw ft_irc::Channel::InvalidKey("Incorrect channel key");
	this->addClient(client);
	return true;
}

ft_irc::Channel::EmptyArgument::EmptyArgument(std::string msg) : std::invalid_argument(msg)
{}

ft_irc::Channel::InvalidMode::InvalidMode(std::string msg) : std::invalid_argument(msg)
{}

ft_irc::Channel::InvalidKey::InvalidKey(std::string msg) : std::invalid_argument(msg)
{}

ft_irc::Channel::InvalidLimit::InvalidLimit(std::string msg) : std::invalid_argument(msg)
{}

ft_irc::Channel::BannedClient::BannedClient() {}

ft_irc::Channel::InviteOnlyChannel::InviteOnlyChannel() {}

ft_irc::Channel::ChannelIsFull::ChannelIsFull() {}

ft_irc::Channel::ClientInfo::ClientInfo(const ft_irc::Client& client) :
	client(client),
	mode()
{}
