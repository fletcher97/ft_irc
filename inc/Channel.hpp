#if !defined(CHANNEL_HPP)
#define CHANNEL_HPP

#include <string>
#include <map>
#include <vector>
#include <stdexcept>

#include "Client.hpp"

#define I 0x01 // Invite-only
#define M 0x02 // Moderated
#define S 0x04 // Secret
#define _T 0x08 // Protected topic
#define N 0x10 // Not external messages

#define Q 0x01 // Founder
#define A 0x02 // Protected
#define	O 0x04 // Operator
#define H 0x08 // Halfop
#define V 0x10 // Voice

#define B 0x01 // Ban nick mask
#define E 0x02 // Ban exception nick mask
#define IE 0x04 // Invite exception nick mask

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
	class ClientInfo {
	public:
		ClientInfo(const ft_irc::Client& client);

		const ft_irc::Client&	client;
		client_mode	mode;
	};

protected:
	std::string __name;
	std::string _topic;
	std::string	_key;
	std::map<int, ClientInfo>	_clients;
	std::map<std::string, mask_mode>	_masks;
	channel_mode	_mode;
	size_t	_client_limit;

public:
	Channel(void);
	Channel(const std::string& name);
	Channel(const Channel& c);
	Channel& operator=(const Channel& c);
	~Channel(void);

	const std::string&	getName(void) const;
	const std::string&	getTopic(void) const;
	const std::string&	getKey(void) const;

	void	setName(std::string& name);
	void	setTopic(std::string& topic);
	void	setKey(std::string& key);
	void	setClientLimit(size_t limit);
	void	toggleMode(const char& mode);

	bool	isInChannel(const Client& client);
	bool	addClient(const Client& client);
	bool	banMask(const std::string& client);
	bool	inviteClient(const std::string& client);

	bool	join(const ft_irc::Client& client, const std::string& key = "");

public:
	class EmptyArgument : public std::invalid_argument
	{
	public:
		EmptyArgument(std::string msg);
	};

	class InvalidMode : public std::invalid_argument
	{
	public:
		InvalidMode(std::string msg);
	};

	class InvalidKey : public std::invalid_argument
	{
	public:
			InvalidKey(std::string msg);
	};

	class InvalidLimit : public std::invalid_argument
	{
	public:
			InvalidLimit(std::string msg);
	};

	class BannedClient : public std::exception
	{
	public:
			BannedClient();
	};

	class InviteOnlyChannel : public std::exception
	{
	public:
			InviteOnlyChannel();
	};

	class ChannelIsFull : public std::exception
	{
	public:
			ChannelIsFull();
	};
};

} // namespace ft_irc

#endif // CHANNEL_HPP
