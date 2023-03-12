#if !defined(COMMUNICATIONS_HPP)
#define COMMUNICATIONS_HPP

#define MAX_CLIENTS 124

#include <string>
#include <netinet/in.h>
#include <vector>
#include <poll.h>

#include "Server.hpp"

class Server;
class Communications
{
private:
	int _fd;
	std::vector<pollfd> _pfds;
	std::string _psswd;
	Server*	_server;
	void write_error(const char *s);
public:
	Communications(Server *server);
	Communications(const Communications& s);
	Communications& operator=(const Communications& s);
	~Communications();
	void init(int port, std::string psswd);
  void run();
  
  int	getFd() const;
  void	addPfd(int fd);
private:
	typedef std::vector<pollfd>::iterator	pfds_iterator;
};

#endif
