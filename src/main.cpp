#include <cstdlib>

#include "Log.hpp"

#include "Communications.hpp"
#include "Server.hpp"

int main(int argc, char **argv)
{
	Server& server = Server::getInstance();
	Communications& communications = Communications::getInstance();

	LOG_OPEN_FILE("ircserver.log")
	if (argc != 3)
		return (1);
	int port = atoi(argv[1]);
	if (port == 0)
		return (1);
	if (!communications.init(port, argv[2]))
		return (1);
	server.run();
	return (0);
}
