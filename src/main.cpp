#include "Server.hpp"
#include <cstdlib>

int main(int argc, char **argv)
{
	Server& server = Server::getInstance();

	if (argc != 3)
		return (0);
	int port = atoi(argv[1]);
	if (port == 0)
		return (1);
	if (!server.init(port, argv[2]))
		return (1);
	server.run();
	return (0);
}
