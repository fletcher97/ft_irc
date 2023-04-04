#if !defined(SERVER_HPP)
#define SERVER_HPP

#include <string>
#include <map>

#include "Client.hpp"
#include "Configuration.hpp"

namespace ft_irc
{

class Server
{
private:
	std::map<int, ft_irc::Client*> _clients;
	Configuration _config;

protected:
	Server(void);
	Server(const Server& s);
	~Server(void);

	Server& operator=(const Server& s);

public:
	static Server&	getInstance(void);

	void	run(void);

	ft_irc::Client&	getClient(const std::string& nickname) const;
	ft_irc::Client&	getClient(int fd) const;

	void	newClient(void);
};

} // namespace ft_irc

#endif // SERVER_HPP
