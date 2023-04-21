#if !defined(SERVER_HPP)
#define SERVER_HPP

#include <map>
#include <string>

#include "Client.hpp"
#include "Parser.hpp"

namespace ft_irc
{

class Server
{
protected:
	Server(void);
	Server(const Server &s);
	~Server(void);

	Server& operator=(const Server& s);
	std::map<int, Client*> _clients;

public:
	static Server& getInstance(void);

	void run(void);

	ft_irc::Client& getClient(const std::string &nickname) const;
	ft_irc::Client& getClient(int fd) const;

	void newClient(void);
	void quit(int fd);

	void sendMsg(int fd, const std::string &msg);

	void excecute(int fd, const ft_irc::Parser::cmd_t *cmd);
};	// class Server

}	// namespace ft_irc

#endif // SERVER_HPP
