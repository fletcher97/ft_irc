#if !defined(COMMUNICATIONS_HPP)
#define COMMUNICATIONS_HPP

#include <string>
#include <vector>
#include <poll.h>

#define MAX_CLIENTS 124

class Communications
{
private:
	std::string _psswd;

	typedef std::vector<pollfd>::iterator	pfds_iterator;

	void write_error(const char *s);

protected:
	int _fd;
	std::vector<pollfd> _pfds;
	
	Communications(void);
	Communications(const Communications& s);
	~Communications(void);

	Communications& operator=(const Communications& s);

public:
	static Communications&	getInstance(void);

	bool init(int port, const char* psswd);
	void run(void);

	int	getFd(void) const;
	void	addPfd(int fd);
};

#endif
