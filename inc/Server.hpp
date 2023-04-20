#if !defined(SERVER_HPP)
#define SERVER_HPP

#include <map>
#include <string>

#include "Client.hpp"
#include "Channel.hpp"

#define MAX_CLIENTS 124

namespace ft_irc
{

class Server
{
protected:
	Server(void);
	Server(const Server &s);
	~Server(void);

	Server& operator=(const Server &s);
	std::map<int, Client*> _clients;
	std::map<std::string, ft_irc::Channel*> _channels;

public:
	static Server& getInstance(void);

	void run(void);

	ft_irc::Client& getClient(const std::string &nickname) const;
	ft_irc::Client& getClient(int fd) const;

	void newClient(void);
	bool newChannel(const std::string &channel);
	bool isClient(const std::string &nickname) const;
	ft_irc::Channel& getChannel(const std::string &channel);

	void deleteClient(int fd);
};	// class Server

}	// namespace ft_irc

#endif // SERVER_HPP
