#if !defined(COMMUNICATIONS_HPP)
#define COMMUNICATIONS_HPP

#define MAX_CLIENTS 124

#include <string>
#include <netinet/in.h>
#include <vector>
#include <poll.h>

#include "Server.hpp"

class Communications
{
private:
	std::string _psswd;
	int port;
	struct sockaddr_in server_address;
	std::vector<int> vec_clients;
	struct pollfd fd_array[MAX_CLIENTS + 1];
	int server_socket;
	int num_fds;
public:
	Communications(int port, std::string psswd);
	Communications(const Communications& s);
	Communications& operator=(const Communications& s);
	~Communications(void);
    bool is_digits(const std::string &str);
	void init_server(void);
    void run(void);
    void write_error(const char *s);
};

#endif
