#include "Communications.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
		return (0);//error
	int port = atoi(argv[1]);
	Communications com(port, argv[2]);
	com.init_server();
	com.run();
	return (0);
}
