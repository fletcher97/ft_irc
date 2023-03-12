//throw std::invalid_argument("Invalid nickname");

#include <iostream>
#include <vector>
#include <netinet/in.h>
#include <poll.h>
#include <stdexcept>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>

#include "Communications.hpp"
#include "Server.hpp"
#include "Log.hpp"

Communications::Communications(Server *server) : _server(server)
{
	LOG_DEBUG("Creating communitation");
	LOG_INFO("New communitation created");
}

Communications::Communications(const Communications &s) :	_fd(s._fd),
																													_pfds(s._pfds),
																													_psswd(s._psswd),
																													_server(s._server)
{}

Communications &Communications::operator=(const Communications &s) {
	this->_fd = s._fd;
	this->_pfds = s._pfds;
	this->_psswd = s._psswd;
	return *this;
}

Communications::~Communications() {}

void
Communications::write_error(const char *s) {
    std::cerr << s << std::endl;
    exit (EXIT_FAILURE);
}

void
Communications::init(int port, std::string psswd) {
    if ((_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    	write_error("Error creating socket");

    if (fcntl(_fd, F_SETFL, O_NONBLOCK) == -1)
    	write_error("Error fcntl");

    struct sockaddr_in	serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (bind(_fd, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1)
        write_error("Error binding"); //error al asociar el socket a la direccion del servidor

    if (listen(_fd, MAX_CLIENTS) == -1)
        write_error("Error listening"); //error al escuchar conexiones entrantes

    addPfd(_fd);
    	
    _psswd = psswd;
    std::cout << "Listening on port " << port << std::endl;
}

void
Communications::run(void) {
	while (42)
	{
		if (poll(&_pfds[0], _pfds.size(), -1) == -1)
		{
			std::cerr << "Error poll" << std::endl;
			continue;
		}
  
		if (_pfds[0].revents == POLLIN)
			_server->newClient();
		else
			for(pfds_iterator it = _pfds.begin(); it != _pfds.end(); it++)
				if ((*it).revents == POLLIN)
					_server->getClient((*it).fd);
		std::vector<Client*>	clients = _server->getClients();
		
		for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); it++)
			if ((*it)->getStatus() == DELETE)
				(void)_server; //Delete Client from channels and server
		//SEND MESSAGES PENDING
	}
}

int
Communications::getFd() const {
	return _fd;
}

void
Communications::addPfd(int fd) {
	_pfds.push_back(pollfd());
  _pfds.back().fd = fd;
  _pfds.back().events = POLLIN;
}
