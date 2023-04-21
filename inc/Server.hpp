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
private:
	std::map< int, ft_irc::Client* > _clients;

protected:
	Server(void);
	Server(const Server &s);
	~Server(void);

	Server& operator=(const Server &s);

public:
	static Server& getInstance(void);

	void run(void);

	ft_irc::Client& getClient(const std::string &nickname) const;
	ft_irc::Client& getClient(int fd) const;

	void newClient(void);

	void send(int fd, const std::string& msg);

	void excecute(int fd, ft_irc::Parser::cmd_t *cmd);
};	// class Server

}	// namespace ft_irc

#endif // SERVER_HPP
