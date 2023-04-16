#if !defined(COMMUNICATIONS_HPP)
#define COMMUNICATIONS_HPP

#include <string>
#include <vector>
#include <poll.h>

#define MAX_CLIENTS 124

namespace ft_irc
{

class Communications
{
private:
	int _fd;
	std::vector< pollfd > _pfds;
	std::string _psswd;

	typedef std::vector< pollfd >::iterator pfds_iterator;

	void write_error(const char *s);

protected:
	Communications(void);
	Communications(const Communications &s);
	~Communications(void);

	Communications& operator=(const Communications &s);

public:
	static Communications& getInstance(void);

	bool init(int port, const char *psswd);
	void run(void);

	int getFd(void) const;
	void addPfd(int fd);
};	// class Communications

}	// namespace ft_irc

#endif // if !defined(COMMUNICATIONS_HPP)
