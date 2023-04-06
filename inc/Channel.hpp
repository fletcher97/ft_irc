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


namespace ft_irc
{

class Client;
class Channel
{
protected:
	std::string __name;
	std::string _topic;
	std::string	_key;
	std::map<int, ft_irc::Client*> _clients;
	std::vector<std::string>	_banned;
	char _mode;

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
	void	toggleMode(const char& mode);

	bool	isInChannel(const Client& client);
	bool	addClient(Client client);
	bool	banClient(const std::string& client);

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

	// class InvalidKey : public std::invalid_argument
	// {
	// public:
	// 		InvalidKey(std::string msg);
	// };

};

} // namespace ft_irc

#endif // CHANNEL_HPP
