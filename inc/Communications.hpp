#if !defined(COMMUNICATIONS_HPP)
#define COMMUNICATIONS_HPP

#include <map>
#include <string>
#include <vector>
#include <poll.h>
#include "Configuration.hpp"

#define MAX_CLIENTS 124
#define COMS_MAX_READ 4096


namespace ft_irc
{

class Communications
{
protected:
	int _fd;
	std::vector< pollfd > _pfds;
	std::map< int, std::string > _msgs_buffer;
	std::string _psswd;
	Configuration _server_config;

	typedef std::vector< pollfd >::iterator pfds_iterator;

	Communications(void);
	Communications(const Communications &s);
	~Communications(void);

	Communications& operator=(const Communications &s);

public:
	static Communications& getInstance(void);

	bool init(int port, const char *psswd);
	void run(void);
	void recvMsg(int fd);
	void sendMsg(int fd, const std::string &msg);

	int getFd(void) const;
	const std::string& getPsswd(void) const;
	void addPfd(int fd);
};	// class Communications

}	// namespace ft_irc

#endif // if !defined(COMMUNICATIONS_HPP)
