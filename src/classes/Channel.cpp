#include <ctime>
#include <sstream>

#include "Log.hpp"

#include "Channel.hpp"
#include "matcher.hpp"

ft_irc::Channel::Channel(void) :
	_name(),
	_topic(),
	_key(),
	_clients(),
	_mode(),
	_client_limit(),
	_topic_who_time()
{
	LOG_DEBUG("Creating new channel");
}


ft_irc::Channel::Channel(const std::string &name) :
	_topic(),
	_key(),
	_mode(),
	_client_limit(),
	_topic_who_time()
{
	LOG_DEBUG("Creating new channel")
	this->setName(name);
	LOG_INFO("New channel created: " << name)
}


ft_irc::Channel::Channel(const ft_irc::Channel &c) :
	_name(c._name),
	_topic(c._topic),
	_key(c._key),
	_clients(c._clients),
	_mode(c._mode),
	_client_limit(c._client_limit),
	_topic_who_time(c._topic_who_time)
{}

ft_irc::Channel&
ft_irc::Channel::operator=(const ft_irc::Channel &c)
{
	this->_name = c._name;
	this->_topic = c._topic;
	this->_key = c._key;
	this->_clients = c._clients;
	this->_mode = c._mode;
	this->_client_limit = c._client_limit;
	this->_topic_who_time = c._topic_who_time;

	return *this;
}	// =


ft_irc::Channel::~Channel(void)
{
	LOG_INFO("Removed channel: " << this->_name)
}


const std::string&
ft_irc::Channel::getName(void) const
{
	return this->_name;
}	// Channel::getName


const std::string&
ft_irc::Channel::getTopic(void) const
{
	return this->_topic;
}	// Channel::getTopic


const std::string&
ft_irc::Channel::getKey(void) const
{
	return this->_key;
}	// Channel::getKey


const std::pair< std::string, std::string >&
ft_irc::Channel::getTopicWhoTime(void) const
{
	return this->_topic_who_time;
}	// Channel::getTopicWhoTime


const ft_irc::Channel::channel_mode&
ft_irc::Channel::getMode(void) const
{
	return this->_mode;
}	// Channel::getMode


size_t
ft_irc::Channel::getClientLimit() const
{
	return this->_client_limit;
}	// Channel::getClientLimit


void
ft_irc::Channel::setName(const std::string &name)
{
	if (name.length() == 0) {
		LOG_WARN("setName called with empty string");
		throw std::invalid_argument("Name must be a non empty string");
	}
	if (  ((name.at(0) != '#') && (name.at(0) != '&')) || (name.find(' ') != std::string::npos)
	   || (name.find(0x07) != std::string::npos) || (name.find(',') != std::string::npos))
	{
		LOG_WARN("setName called with an invalid character");
		throw ft_irc::Channel::InvalidChannelName("Invalid channel  name: " + name);
	}
	LOG_INFO("Channel's name changed from: " << this->_name << " to: " << name)
	this->_name = name;
}	// Channel::setName


void
ft_irc::Channel::setTopic(ft_irc::Client &source, const std::string &topic)
{
	timespec now;
	std::ostringstream converter;

	if (!this->_clients.count(source.getFd())) {
		LOG_WARN("setTopic called with a client not on channel");
		throw ft_irc::Channel::NotOnChannel();
	}
	if (  this->_mode & CH_PROTECTED_TOPIC && !(this->_clients.at(source.getFd()).mode & CH_OPERATOR)
	   && !(this->_clients.at(source.getFd()).mode & CH_HALFOP)
	   && !(this->_clients.at(source.getFd()).mode & CH_PROTECTED))
	{
		LOG_WARN("setTopic called with a client with no privileges");
		throw ft_irc::Channel::NoPrivsOnChannel();
	}
	LOG_INFO("Channel's topic changed from: " << this->_topic << " to: " << topic)
	this->_topic = topic;
	this->_topic_who_time.first = source.getMask();
	clock_gettime(CLOCK_REALTIME, &now);
	converter.precision(0);
	converter << std::fixed << static_cast< double >(now.tv_sec);
	this->_topic_who_time.second = converter.str();
	LOG_INFO("setTopic: topic changed by " << this->_topic_who_time.first << " at " << this->_topic_who_time.second)
}	// Channel::setTopic


void
ft_irc::Channel::setKey(const std::string &key)
{
	if (key.length() == 0) {
		LOG_WARN("setKet with an empty string");
		throw std::invalid_argument("Key must be a non empty string");
	}
	LOG_INFO("Channel's key changed from: " << this->_key << " to: " << key)
	this->_key = key;
}	// Channel::setKey


void
ft_irc::Channel::removeKey(void)
{
	LOG_INFO("Channel's key was removed")
	this->_key = "";
}	// Channel::setKey


void
ft_irc::Channel::setClientLimit(long limit)
{
	if (limit <= 0) {
		LOG_WARN("setClientLimit with an invalid number: " << limit);
		throw ft_irc::Channel::InvalidLimit("Invalid limit");
	}
	LOG_INFO("Channel's limit changed from: " << this->_client_limit << " to: " << limit)
	this->_client_limit = limit;
}	// Channel::setClientLimit


void
ft_irc::Channel::removeClientLimit(void)
{
	this->_client_limit = 0;
}	// Channel::removeKey


void
ft_irc::Channel::toggleMode(const char mode)
{
	if ((mode > (CH_INVITE | CH_MODERATE | CH_SECRET | CH_PROTECTED_TOPIC | CH_NOT_EXTERNAL_MSGS)) || (mode <= 0)) {
		LOG_WARN("setClientLimit with an invalid mode: " << mode);
		throw ft_irc::Channel::InvalidMode("Invalid mode");
	}
	this->_mode ^= mode;
}	// Channel::toggleMode


bool
ft_irc::Channel::isInChannel(const ft_irc::Client &client) const
{
	return this->_clients.count(client.getFd());
}	// Channel::isInChannel


bool
ft_irc::Channel::isInChannel(const std::string &nickname) const
{
	for (std::map< int, ClientInfo >::const_iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		if (it->second.client.getNickname() == nickname) {
			LOG_INFO("isInChannel client in channel: " << nickname)

			return true;
		}
	}
	LOG_INFO("isInChannel client not in channel: " << nickname)

	return false;
}	// Channel::isInChannel


bool
ft_irc::Channel::isFounder(const ft_irc::Client &c) const
{
	for (client_const_iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		if (it->second.client.getNickname() == c.getNickname()) {
			return it->second.mode & CH_FOUNDER;
		}
	}

	return false;
}	// Channel::isFounder


bool
ft_irc::Channel::isProtected(const ft_irc::Client &c) const
{
	for (client_const_iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		if (it->second.client.getNickname() == c.getNickname()) {
			return it->second.mode & CH_PROTECTED;
		}
	}

	return false;
}	// Channel::isProtected


bool
ft_irc::Channel::isOp(const ft_irc::Client &c) const
{
	for (client_const_iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		if (it->second.client.getNickname() == c.getNickname()) {
			return it->second.mode & CH_OPERATOR;
		}
	}

	return false;
}	// Channel::isOp


bool
ft_irc::Channel::isHalfOp(const ft_irc::Client &c) const
{
	for (client_const_iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		if (it->second.client.getNickname() == c.getNickname()) {
			return it->second.mode & CH_HALFOP;
		}
	}

	return false;
}	// Channel::isHalfOp


bool
ft_irc::Channel::isVoice(const ft_irc::Client &c) const
{
	for (client_const_iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		if (it->second.client.getNickname() == c.getNickname()) {
			return it->second.mode & CH_VOICE;
		}
	}

	return false;
}	// Channel::isVoice


bool
ft_irc::Channel::isBanned(const ft_irc::Client &client) const
{
	for (std::map< std::string, mask_mode >::const_iterator it = this->_masks.begin(); it != this->_masks.end(); it++) {
		if (ft_irc::match(it->first, client.getMask())) {
			if (it->second & CH_BAN && !(it->second & CH_EXCEPTION)) {
				return true;
			}
		}
	}

	return false;
}	// Channel::isBanned


bool
ft_irc::Channel::isInvited(const ft_irc::Client &client) const
{
	for (std::map< std::string, mask_mode >::const_iterator it = this->_masks.begin(); it != this->_masks.end(); it++) {
		if (ft_irc::match(it->first, client.getNickname())) {
			if (it->second & CH_INVITE) {
				return true;
			}
			break;
		}
	}

	return false;
}	// Channel::isInvited


bool
ft_irc::Channel::setOp(const Client &c)
{
	for (client_iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		if (it->first == c.getFd()) {
			if (!(it->second.mode & CH_OPERATOR)) {
				it->second.mode |= CH_OPERATOR;

				return true;
			} else {
				break;
			}
		}
	}

	return false;
}	// Channel::setOp


bool
ft_irc::Channel::unsetOp(const Client &c)
{
	for (client_iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		if (it->first == c.getFd()) {
			if (it->second.mode & CH_OPERATOR) {
				it->second.mode &= ~(CH_OPERATOR);

				return true;
			} else {
				break;
			}
		}
	}

	return false;
}	// Channel::unsetOp


bool
ft_irc::Channel::setVoice(const Client &c)
{
	for (client_iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		if (it->first == c.getFd()) {
			it->second.mode |= CH_OPERATOR;

			return true;
		}
	}

	return false;
}	// Channel::setVoice


bool
ft_irc::Channel::unsetVoice(const Client &c)
{
	for (client_iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		if (it->first == c.getFd()) {
			it->second.mode &= ~CH_VOICE;

			return true;
		}
	}

	return false;
}	// Channel::unsetVoice


bool
ft_irc::Channel::addClient(const ft_irc::Client &client)
{
	if (this->_clients.count(client.getFd())) {
		LOG_WARN("addClient client already on channel: " << client.getNickname())

		return false;
	}
	this->_clients.insert(std::make_pair< int, ft_irc::Channel::ClientInfo >(client.getFd(),
		ft_irc::Channel::ClientInfo(client)));
	LOG_INFO("New client added to channel: " << client.getNickname())
	if (this->_clients.size() == 1) {
		LOG_INFO("addClient first client in channel: " << client.getNickname())

		this->_clients.begin()->second.mode = (CH_FOUNDER | CH_OPERATOR);
	}

	return true;
}	// Channel::addClient


bool
ft_irc::Channel::banMask(const std::string &mask)
{
	if (this->_masks.count(mask)) {
		if (this->_masks[mask] & CH_BAN) {
			LOG_WARN("banMask mask already banned in channel: " << mask)

			return false;
		}
		this->_masks[mask] ^= CH_BAN;
	} else {
		this->_masks.insert(std::make_pair< std::string, mask_mode >(mask, CH_BAN));
	}
	LOG_INFO("Mask banned from channel: " << mask)

	return true;
}	// Channel::banMask


bool
ft_irc::Channel::invite(const Client &source, const std::string &nick)
{
	if (!this->_clients.count(source.getFd())) {
		LOG_WARN("invite, source not on channel: " << source.getNickname());
		throw ft_irc::Channel::NotOnChannel();
	}
	if (this->_mode & CH_INVITE_ONLY && !(this->_clients.at(source.getFd()).mode & CH_OPERATOR)) {
		LOG_WARN("invite, source doesent have privileges: " << source.getNickname());
		throw ft_irc::Channel::NoPrivsOnChannel();
	}
	if (this->isInChannel(nick)) {
		LOG_WARN("invite, client already on channel: " << nick);
		throw ft_irc::Channel::AlreadyOnChannel();
	}
	if (this->_masks.count(nick)) {
		if (this->_masks[nick] & CH_INVITE) {
			LOG_WARN("invite, client already invited to channel: " << nick)

			return false;
		}
		this->_masks[nick] ^= CH_INVITE;
	} else {
		this->_masks.insert(std::make_pair< std::string, mask_mode >(nick, CH_INVITE));
	}
	LOG_INFO("invite, client invited to channel: " << nick)

	return true;
}	// Channel::invite


std::map< std::string, ft_irc::Channel::mask_mode >&
ft_irc::Channel::getMasks()
{
	return this->_masks;
}	// Channel::getMasks


std::map< int, ft_irc::Channel::ClientInfo >&
ft_irc::Channel::getClients()
{
	return this->_clients;
}	// Channel::getClients


bool
ft_irc::Channel::join(const ft_irc::Client &client, const std::string &key)
{
	if (this->_clients.count(client.getFd())) {
		LOG_WARN("join, client already in channel: " << client.getNickname())

		return false;
	}
	if (this->isBanned(client)) {
		LOG_WARN("join, client banned from channel: " << client.getNickname());
		throw ft_irc::Channel::BannedClient();
	}
	if ((this->_mode & CH_INVITE_ONLY) && !this->isInvited(client)) {
		LOG_WARN("join, client not invited to channel: " << client.getNickname());
		throw ft_irc::Channel::InviteOnlyChannel();
	}
	if ((this->_client_limit != 0) && (this->_client_limit <= this->_clients.size())) {
		LOG_WARN("join, client can't join, channel is full: " << client.getNickname());
		throw ft_irc::Channel::ChannelIsFull();
	}
	if (!this->_key.empty() && (this->_key != key)) {
		LOG_WARN("join, client " << client.getNickname() << " can't join, invalid key: " << key);
		throw ft_irc::Channel::InvalidKey("Incorrect channel key");
	}
	this->_masks[client.getNickname()] &= ~(CH_INVITE);
	LOG_INFO("Client joined to channel: " << client.getNickname())
	this->addClient(client);

	return true;
}	// Channel::join


bool
ft_irc::Channel::part(const ft_irc::Client &client, const std::string &reason)
{
	LOG_TRACE("part: Checking if " << client.getNickname() << " is in " << this->_name)
	if (!this->_clients.count(client.getFd())) {
		LOG_WARN("part: 442: Not on channel: " << client.getNickname());
		throw ft_irc::Channel::NotOnChannel();
	}
	LOG_INFO("part: " << client.getNickname() << " leaves " << this->_name)

	this->_clients.erase(client.getFd());
	this->broadcast(client.getNickname(), ft_irc::CMD_PART, reason);
	LOG_TRACE("part: " << this->_name << " has " << this->_clients.size() << " clients")

	return this->_clients.empty();
}	// Channel::part


void
ft_irc::Channel::broadcast(const std::string &source, ft_irc::commands cmd, const std::string arg) const
{
	LOG_DEBUG("broadcast: " << source << " " << ft_irc::toString(cmd) << " " << arg)
	for (std::map< int, ClientInfo >::const_iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		LOG_TRACE("broadcast: Sending: " << it->second.client.getNickname())

		try {
			it->second.client.sendMsg(":" + source + " " + ft_irc::toString(cmd) + " " + this->_name + " " + arg);
		} catch (...) {
			LOG_ERROR("Faild to send to " << it->second.client.getNickname() << " when broacasting to " << this->_name)
		}
	}
}	// Channel::broadcast


void
ft_irc::Channel::broadcast(ft_irc::commands cmd, const std::string arg) const
{
	LOG_DEBUG("broadcast Command overload: " << ft_irc::toString(cmd) << " " << arg)
	for (std::map< int, ClientInfo >::const_iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		LOG_TRACE("broadcast: Sending: " << it->second.client.getNickname())

		try {
			it->second.client.sendMsg(ft_irc::toString(cmd) + " " + this->_name + " :" + arg);
		} catch (...) {
			LOG_ERROR("Faild to send to " << it->second.client.getNickname() << " when broacasting to " << this->_name)
		}
	}
}	// Channel::broadcast


void
ft_irc::Channel::names(const ft_irc::Client &client) const
{
	std::string symbol = "=";
	std::string prefix;
	bool is_in_channel = this->isInChannel(client);

	LOG_TRACE("names: Check if " << this->_name << " is secret")
	if (this->_mode & CH_SECRET) {
		if (!is_in_channel) {
			LOG_INFO("names: Chanel " << this->_name << " is secret and " << client.getNickname() << " is not joined")
			client.sendMsg(ft_irc::getReply(ft_irc::RPL_ENDOFNAMES, client.getNickname(), this->_name));

			return;
		}
		symbol = "@";
	}
	LOG_TRACE("names: Symbol " << symbol << " " << this->_name)
	for (std::map< int, ClientInfo >::const_iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		prefix = ((it->second.mode & CH_VOICE) ? "+" : "");
		prefix = ((it->second.mode & CH_HALFOP) ? "%" : prefix);
		prefix = ((it->second.mode & CH_OPERATOR) ? "@" : prefix);
		prefix = ((it->second.mode & CH_PROTECTED) ? "&" : prefix);
		LOG_DEBUG("names: " << symbol << " " << this->_name << " " << prefix << " " << it->second.client.getNickname())
		client.sendMsg(ft_irc::getReply(ft_irc::RPL_NAMREPLY, client.getNickname(), symbol, this->_name, prefix,
			it->second.client.getNickname()));
	}
	LOG_TRACE("names: End of names")
	client.sendMsg(ft_irc::getReply(ft_irc::RPL_ENDOFNAMES, client.getNickname(), this->_name));
}	// Channel::names


void
ft_irc::Channel::privmsg(const ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd, const std::string &priv_chars)
{
	size_t client_priv, priv;

	if (this->_mode & CH_NOT_EXTERNAL_MSGS && !this->isInChannel(client)) {
		LOG_WARN(
			"privmsg: Channel " << this->_name << " is in CH_NOT_EXTERNAL_MSGS mode, and " << client.getNickname() <<
			" is not on channel")
   throw ft_irc::Channel::NotOnChannel();
	}
	if (  this->_mode & CH_MODERATE
	   && (!this->isInChannel(client) || !(this->_clients.find(client.getFd())->second.mode & CH_VOICE)))
	{
		LOG_WARN("privmsg: Channel " << this->_name << " is in CH_MODERATE mode and " << client.getNickname() <<
			" has no privs")
   throw ft_irc::Channel::NoPrivsOnChannel();
	}
	if (this->isBanned(client)) {
		LOG_WARN("privmsg: Client " << client.getNickname() << " is banned from " << this->_name);
		throw ft_irc::Channel::BannedClient();
	}
	priv = std::string("~+%@&").find_last_of(priv_chars);
	LOG_DEBUG("privmsg: priv_chars: " << priv_chars << " priv: " << priv)
	for (client_iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		client_priv = ((it->second.mode & CH_VOICE) ? 4 : std::string::npos);
		client_priv = ((it->second.mode & CH_HALFOP) ? 3 : client_priv);
		client_priv = ((it->second.mode & CH_OPERATOR) ? 2 : client_priv);
		client_priv = ((it->second.mode & CH_PROTECTED) ? 1 : client_priv);
		client_priv = ((it->second.mode & CH_FOUNDER) ? 0 : client_priv);
		LOG_TRACE("privmsg: " << it->second.client.getNickname() << " client_priv: " << client_priv)
		if ((priv >= client_priv) && (it->second.client.getNickname() != client.getNickname())) {
			it->second.client.sendMsg(":" + client.getNickname() + " " + ft_irc::toString(
				cmd->cmd) + " " + this->_name + " " + cmd->args.at(1));
		}
	}
}	// Channel::privmsg


void
ft_irc::Channel::kick(const ft_irc::Client &client, const std::string &target, const std::string &comment)
{
	if (!this->isInChannel(client)) {
		LOG_WARN("kick: client not no channel: " << client.getNickname());
		throw ft_irc::Channel::NotOnChannel();
	}
	if (!(this->_clients.find(client.getFd())->second.mode & (CH_FOUNDER | CH_OPERATOR | CH_PROTECTED | CH_HALFOP))) {
		LOG_WARN("kick: permission denied: " << client.getNickname());
		throw ft_irc::Channel::NoPrivsOnChannel();
	}
	if (!this->isInChannel(target)) {
		LOG_WARN("kick: target not in channel: " << target);
		throw ft_irc::Channel::UserNotInChannel();
	}
	for (client_iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		if (it->second.client.getNickname() == target) {
			LOG_INFO("kick: Kicking: " << target)

			if (this->isFounder(it->second.client)) {
				LOG_WARN("kick: try to kick founder");
				throw ft_irc::Channel::NoPrivsOnChannel();

				return;
			}
			if (it->second.client.getNickname() == client.getNickname()) {
				throw ft_irc::Channel::NoPrivsOnChannel();

				return;
			}
			this->broadcast(client.getMask(), ft_irc::CMD_KICK, target + " " + comment);
			this->_clients.erase(it);

			return;
		}
	}
}	// Channel::kick


ft_irc::Channel::InvalidChannelName::InvalidChannelName(std::string msg) :
	std::invalid_argument(msg)
{}

ft_irc::Channel::InvalidMode::InvalidMode(std::string msg) :
	std::invalid_argument(msg)
{}

ft_irc::Channel::InvalidKey::InvalidKey(std::string msg) :
	std::invalid_argument(msg)
{}

ft_irc::Channel::InvalidLimit::InvalidLimit(std::string msg) :
	std::invalid_argument(msg)
{}

ft_irc::Channel::BannedClient::BannedClient() {}

ft_irc::Channel::InviteOnlyChannel::InviteOnlyChannel() {}

ft_irc::Channel::ChannelIsFull::ChannelIsFull() {}

ft_irc::Channel::NotOnChannel::NotOnChannel() {}

ft_irc::Channel::NoPrivsOnChannel::NoPrivsOnChannel() {}

ft_irc::Channel::AlreadyOnChannel::AlreadyOnChannel() {}

ft_irc::Channel::UserNotInChannel::UserNotInChannel() {}

ft_irc::Channel::ClientInfo::ClientInfo(const ft_irc::Client &c) :
	client(c),
	mode()
{}
