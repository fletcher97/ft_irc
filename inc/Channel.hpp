#if !defined(CHANNEL_HPP)
#define CHANNEL_HPP

#include <string>
#include <map>

#include "Client.hpp"

class Client;
class Channel
{
protected:
	std::string _name;
	std::string _topic;
	std::map<int, Client*> _clients;
	std::string	_key;

public:
	Channel(void);
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
};

#endif // CHANNEL_HPP
