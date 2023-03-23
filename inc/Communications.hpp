#if !defined(COMMUNICATIONS_HPP)
#define COMMUNICATIONS_HPP

#include <string>
#include <netinet/in.h>
#include <vector>
#include <poll.h>

#include "Server.hpp"

#define MAX_CLIENTS 124

class Server;
class Communications
{
private:
	int _fd;
	std::vector<pollfd> _pfds;
	std::string _psswd;

	typedef std::vector<pollfd>::iterator	pfds_iterator;

	void write_error(const char *s);

protected:
	Communications();
	Communications(const Communications& s);
	~Communications(void);

	Communications& operator=(const Communications& s);

public:
	static Communications&	getInstance(void);

	bool init(int port, std::string psswd);
	void run(void);

	int	getFd(void) const;
	void	addPfd(int fd);
};

#endif
