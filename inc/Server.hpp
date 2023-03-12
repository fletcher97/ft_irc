#if !defined(SERVER_HPP)
#define SERVER_HPP

#include <string>
#include <map>
#include <vector>

#include "Client.hpp"
#include "Channel.hpp"
#include "Communications.hpp"

class Communications;
class Server
{
private:
	std::map<int, Client*> _clients;
	std::map<std::string, Channel*> _channels;
	Communications*	_communications;
public:
	Server();
	Server(const Server& s);
	Server& operator=(const Server& s);
	~Server();
	
	void	init(int port, std::string _psswd);
	void	run();
		
	Client&	getClient(const std::string& nickname);
	Client&	getClient(int fd);
	Channel&	getChannel(const std::string& name);
	
	std::vector<Client*>	getClients();
	std::vector<Channel*>	getChannels();
	
	void	delClient(Client& client);
	void	delChannel(Channel& channel);
	
	bool	isChannel(const std::string& name) const;
	
	void	newClient();
	
private:
	typedef std::map<int, Client*>::iterator clients_iterator;
	typedef std::map<std::string, Channel*>::iterator channels_iterator;
};

#endif // SERVER_HPP
