#if !defined(SERVER_HPP)
#define SERVER_HPP

#include <map>
#include <string>

#include "Channel.hpp"
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

		Server& operator=(const Server &s);

		std::map< int, Client* > _clients;
		std::map< std::string, Channel* > _channels;
		std::string _name;

public:
		static Server& getInstance(void);

		void run(void);

		ft_irc::Client& getClient(const std::string &nickname) const;
		ft_irc::Client& getClient(int fd) const;

		void setName(std::string name);

		void newClient(void);
		void deleteClient(int fd, const std::string &reason = "Leaving Server");

		void sendMsg(int fd, const std::string &msg);

		void excecute(int fd, const ft_irc::Parser::cmd_t *cmd);

		void pass(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd);
		void nick(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd);
		void user(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd);
		void join(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd);
		void part(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd);
		void quit(ft_irc::Client &client, const ft_irc::Parser::cmd_t *cmd);
	};	// class Server

	}	// namespace ft_irc
#endif // SERVER_HPP
