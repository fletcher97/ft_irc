#if !defined(SERVER_HPP)
#define SERVER_HPP

#include <string>
#include <map>

#include "Client.hpp"
#include "Channel.hpp"

class Server
{
private:
	std::string _name;
	std::map<std::string, Client&> _clients;
	std::map<std::string, Channel&> _channels;
public:
	Server(std::string name);
	Server(const Server& s);
	Server& operator=(const Server& s);
	~Server();
};

#endif // SERVER_HPP
