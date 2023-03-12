#if !defined(CHANNEL_HPP)
#define CHANNEL_HPP

#include <string>
#include <map>
#include <vector>


#include "Client.hpp"

// struct	ChannelMode
// {
// 	bool	a;
// 	bool	i;
// 	bool	m;
// 	bool	n;
// 	bool	q;
// 	bool	p;
// 	bool	s;
// 	bool	r;
// 	bool	t;
// 	bool	k;
// 	bool	l;
// 	bool	b;
// 	bool	e;
// 	bool	I;
// 	bool	O;
// 	bool	o;
// 	bool	v;
// 	//TODO Check wich are necessary
// 	ChannelMode();
// 	ChannelMode(const ChannelMode& m);
// 	ChannelMode& operator=(const ChannelMode& m);
// };

class Client;
class Channel
{
protected:
	std::string _name;
	std::string _topic;
	std::map<int, Client&> _clients;
	// ChannelMode	_mode;
	std::string	_key;
	// size_t	maxClients; Usefull?
	// std::vector<Client*>	_invited; Usefull?
	// std::vector<Client*>	_banned; Usefull?
public:
	Channel();
	Channel(const Channel& c);
	Channel& operator=(const Channel& c);
	~Channel();
	
	std::string	getName() const;
	std::string	getTopic() const;
	std::string	getKey() const;
	
	// std::vector<Client *> getClients() const;
	
	void	setName(std::string name);
	void	setTopic(std::string topic);
	void	setKey(std::string key);
	
	bool	isInChannel(const Client& client);
	// bool	isInChannel(const std::string& nickname);
	
};

#endif // CHANNEL_HPP
