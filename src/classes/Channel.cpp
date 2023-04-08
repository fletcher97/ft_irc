#include "Log.hpp"

#include "Channel.hpp"

#define I 0x01 // Invite-only
#define M 0x02 // Moderated
#define S 0x04 // Secret
#define T 0x08 // Protected topic
#define N 0x10 // Not external messages

#define Q 0x01 // Founder
#define A 0x02 // Protected
#define	O 0x04 // Operator
#define H 0x08 // Halfop
#define V 0x10 // Voice

#define B 0x01 // Ban nick mask
#define E 0x02 // Ban exception nick mask
#define IV 0x04 // Invite nick mask
#define IE 0x08 // Invite exception nick mask

ft_irc::Channel::Channel(void) :
	_name(),
	_topic(),
	_key(),
	_clients(),
	_mode(),
	_client_limit()
{
	LOG_DEBUG("Creating new channel");
}

ft_irc::Channel::Channel(const std::string& name) :
	_name(name),
	_topic(),
	_key(),
	_mode(),
	_client_limit()
{
	LOG_DEBUG("Creating new channel")
	LOG_INFO("New channel created: " << name)
}

ft_irc::Channel::Channel(const ft_irc::Channel& c) :
	_name(c._name),
	_topic(c._topic),
	_key(c._key),
	_clients(c._clients),
	_mode(c._mode),
	_client_limit(c._client_limit)
{}

ft_irc::Channel&
ft_irc::Channel::operator=(const ft_irc::Channel& c) {
	this->_name = c._name;
	this->_topic = c._topic;
	this->_key = c._key;
	this->_clients = c._clients;
	this->_mode = c._mode;
	this->_client_limit = c._client_limit;
	return *this;
}

ft_irc::Channel::~Channel(void) {
	LOG_INFO("Removed channel: " << this->_name)
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
	if (name.length() == 0)
		throw ft_irc::Channel::EmptyArgument("Name must be a non empty string");
	LOG_INFO("Channel's name changed from: " << this->_name << " to: " << name)
	this->_name = name;
}

void
ft_irc::Channel::setTopic(std::string& topic) {
	if (topic.length() == 0)
		throw ft_irc::Channel::EmptyArgument("Topic must be a non empty string");
	LOG_INFO("Channel's topic changed from: " << this->_topic << " to: " << topic)
	this->_topic = topic;
}

void
ft_irc::Channel::setKey(std::string& key) {
	if (key.length() == 0)
		throw ft_irc::Channel::EmptyArgument("Key must be a non empty string");
	LOG_INFO("Channel's key changed from: " << this->_key << " to: " << key)
	this->_key = key;
}

void
ft_irc::Channel::setClientLimit(long limit) {
	if (limit <= 0)
		throw ft_irc::Channel::InvalidLimit("Invalid limit");
	LOG_INFO("Channel's limit changed from: " << this->_limit << " to: " << limit)
	this->_client_limit = limit;
}

void
ft_irc::Channel::toggleMode(const  char& mode) {
	if (mode <= (I|M|S|T|N) && mode > 0) {
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
ft_irc::Channel::isInChannel(const std::string& nickname) {
	for (client_iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
		if (it->second.client.getNickname() == nickname)
			return true;
	return false;
}

bool
ft_irc::Channel::addClient(const ft_irc::Client& client) {
	if (this->_clients.count(client.getFd()))
		return false;
	this->_clients.insert(std::make_pair(client.getFd(),
		ft_irc::Channel::ClientInfo(client)));
	if (this->_clients.size() == 1)
		this->_clients.begin()->second.mode = (Q|O);
	LOG_INFO("New client added to channel: " << client.getNickname())
	return true;
}

bool
ft_irc::Channel::banMask(const std::string& mask) {
	if (this->_masks.count(mask)) {
		if (this->_masks[mask] & B)
			return false;
		this->_masks[mask] ^= B;
	}
	else
		this->_masks.insert(std::make_pair(mask, B));
	LOG_INFO("Mask banned from channel: " << mask)
	return true;
}

bool
ft_irc::Channel::invite(const Client& source, const std::string& nick) {
	if (!this->_clients.count(source.getFd()))
		throw ft_irc::Channel::NotOnChannel();
	if (this->_mode & I && !(this->_clients.at(source.getFd()).mode & O))
		throw ft_irc::Channel::NotOperOnChannel();
	if (this->isInChannel(nick))
		throw ft_irc::Channel::AlreadyOnChannel();
	if (this->_masks.count(nick)) {
		if (this->_masks[nick] & IV)
			return false;
		this->_masks[nick] ^= IV;
	}
	else
		this->_masks.insert(std::make_pair(nick, IV));
	LOG_INFO("Client invited to channel: " << nick)
	return true;
}

bool
ft_irc::Channel::join(const ft_irc::Client& client, const std::string& key) {
	if (this->_clients.count(client.getFd()))
		return false;
	if (this->_masks.count(client.getMask()))
		throw ft_irc::Channel::BannedClient();
	if (this->_mode & I &&
		!this->_masks.count(client.getNickname()))
		throw ft_irc::Channel::InviteOnlyChannel();
	if (this->_client_limit != 0 && this->_client_limit >= this->_clients.size())
		throw ft_irc::Channel::ChannelIsFull();
	if (!this->_key.empty() && this->_key != key)
		throw ft_irc::Channel::InvalidKey("Incorrect channel key");
	LOG_INFO("Client joined to channel: " << client.getNickname())
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

ft_irc::Channel::NotOnChannel::NotOnChannel() {}

ft_irc::Channel::NotOperOnChannel::NotOperOnChannel() {}

ft_irc::Channel::AlreadyOnChannel::AlreadyOnChannel() {}

ft_irc::Channel::ClientInfo::ClientInfo(const ft_irc::Client& client) :
	client(client),
	mode()
{}
