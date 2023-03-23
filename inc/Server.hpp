#if !defined(SERVER_HPP)
#define SERVER_HPP

#include <string>
#include <map>

#include "Client.hpp"
#include "Channel.hpp"
#include "Communications.hpp"

class Communications;
class Server
{
private:
	std::map<int, Client*> _clients;

protected:
	Server(void);
	Server(const Server& s);
	~Server(void);

	Server& operator=(const Server& s);

public:
	static Server&	getInstance(void);

	bool	init(int port, std::string _psswd);
	void	run(void);

	Client&	getClient(const std::string& nickname) const;
	Client&	getClient(int fd) const;

	void	newClient(void);
};

#endif // SERVER_HPP
