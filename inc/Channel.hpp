#if !defined(CHANNEL_HPP)
#define CHANNEL_HPP

#include <string>
#include <map>
#include <vector>
#include <stdexcept>

#include "Client.hpp"

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

	bool	isInChannel(const Client& client);

	bool	addClient(Client client);
	bool	banClient(const std::string& client);

public:
	class EmptyArgument : public std::invalid_argument
	{
	public:
			EmptyArgument(std::string msg);
	};

	class InvalidKey : public std::invalid_argument
	{
	public:
			InvalidKey(std::string msg);
	};

};

} // namespace ft_irc

#endif // CHANNEL_HPP
