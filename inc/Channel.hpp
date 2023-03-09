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
	std::map<std::string, Client&> _clients;
public:
	Channel(std::string name);
	Channel(const Channel& c);
	Channel& operator=(const Channel& c);
	~Channel();
};

#endif // CHANNEL_HPP
