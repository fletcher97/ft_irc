#include "Server.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
		return (0);//error
	int port = atoi(argv[1]);
	Server server;
	server.init(port, argv[2]);
	server.run();
	return (0);
}
