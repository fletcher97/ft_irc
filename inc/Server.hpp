#if !defined(SERVER_HPP)
#define SERVER_HPP

#include <string>
#include <map>
#include <vector>

#include "Client.hpp"
#include "Channel.hpp"

class Server
{
private:
	int _fd;
	std::map<int, Client&> _clients;
	std::map<std::string, Channel&> _channels;
public:
	Server();
	Server(const Server& s);
	Server& operator=(const Server& s);
	~Server();
	
	void	init();
	void	run();
	
	Client&	getClient(const std::string& nickname);
	Channel&	getChannel(const std::string& name);
	
	std::vector<Client*>	getClients();
	std::vector<Channel*>	getChannels();
	
	void	delClient(Client& client);
	void	delChannel(Channel& channel);
	
	bool	isChannel(const std::string& name) const;
private:
	typedef std::map<int, Client&>::iterator clients_iterator;
	typedef std::map<std::string, Channel&>::iterator channels_iterator;
};

#endif // SERVER_HPP
