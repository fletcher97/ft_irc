#if !defined(CHANNEL_HPP)
#define CHANNEL_HPP

#include <map>
#include <stdexcept>
#include <string>

#include "Client.hpp"

#define INVITE_ONLY 0x01
#define MODERATE 0x02
#define SECRET 0x04
#define PROTECTED_TOPIC 0x08
#define NOT_EXTERNAL_MSGS 0x10

#define FOUNDER 0x01
#define PROTECTED 0x02
#define OPERATOR 0x04
#define HALFOP 0x08
#define VOICE 0x10

#define BAN 0x01
#define EXCEPTION 0x02
#define INVITE 0x04
#define INVITE_EXCEPTION 0x08

namespace ft_irc
{

class Client;

class Channel
{
public:
	typedef char channel_mode;
	typedef char client_mode;
	typedef char mask_mode;

protected:

	class ClientInfo
	{
public:
		const ft_irc::Client &client;
		client_mode mode;

		ClientInfo(const ft_irc::Client &client);
	};	// class ClientInfo

public:
	typedef std::map< std::string, mask_mode >::iterator mask_iterator;
	typedef std::map< int, ClientInfo >::iterator client_iterator;

protected:
	std::string _name;
	std::string _topic;
	std::string _key;
	std::map< int, ClientInfo > _clients;
	std::map< std::string, mask_mode > _masks;
	channel_mode _mode;
	size_t _client_limit;

public:
	Channel(void);
	Channel(const std::string &name);
	Channel(const Channel &c);

	Channel& operator=(const Channel &c);

	~Channel(void);

	const std::string& getName(void) const;
	const std::string& getTopic(void) const;
	const std::string& getKey(void) const;

	void setName(const std::string &name);
	void setTopic(ft_irc::Client &source, std::string &topic);
	void setKey(std::string &key);
	void setClientLimit(long limit);
	void toggleMode(const char mode);

	bool isInChannel(const Client &client);
	bool isInChannel(const std::string &nickname);
	bool addClient(const Client &client);
	bool banMask(const std::string &client);
	bool invite(const Client &source, const std::string &client);

	bool join(const ft_irc::Client &client, const std::string &key = "");

public:

	class InvalidChannelName :
		public std::invalid_argument
	{
public:
		InvalidChannelName(std::string msg);
	};	// class InvalidChannelName

	class InvalidMode :
		public std::invalid_argument
	{
public:
		InvalidMode(std::string msg);
	};	// class InvalidMode

	class InvalidKey :
		public std::invalid_argument
	{
public:
		InvalidKey(std::string msg);
	};	// class InvalidKey

	class InvalidLimit :
		public std::invalid_argument
	{
public:
		InvalidLimit(std::string msg);
	};	// class InvalidLimit

	class BannedClient :
		public std::exception
	{
public:
		BannedClient();
	};	// class BannedClient

	class InviteOnlyChannel :
		public std::exception
	{
public:
		InviteOnlyChannel();
	};	// class InviteOnlyChannel

	class ChannelIsFull :
		public std::exception
	{
public:
		ChannelIsFull();
	};	// class ChannelIsFull

	class NotOnChannel :
		public std::exception
	{
public:
		NotOnChannel();
	};	// class NotOnChannel

	class NoPrivsOnChannel :
		public std::exception
	{
public:
		NoPrivsOnChannel();
	};	// class NoPrivsOnChannel

	class AlreadyOnChannel :
		public std::exception
	{
public:
		AlreadyOnChannel();
	};	// class AlreadyOnChannel
};	// class Channel

}	// namespace ft_irc

#endif // CHANNEL_HPP
