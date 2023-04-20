#include <sys/socket.h>
#include <netinet/in.h>

#include "Log.hpp"

#include "ServerUT.hpp"

ft_irc::ServerUT::ServerUT(void) :
	flt::Testable< ft_irc::ServerUT >("Server"),
	ft_irc::Server()
{
	REGISTER(ft_irc::ServerUT, test_constructor)
	REGISTER(ft_irc::ServerUT, test_getClient_fd)
	REGISTER(ft_irc::ServerUT, test_getClient_nick)
}


ft_irc::ServerUT::~ServerUT(void) {}

void
ft_irc::ServerUT::test_constructor(void)
{
	ASSERT_NOTHROW(ft_irc::Server server1(void) )
	ASSERT_NOTHROW(ft_irc::Server server2(void) )
}	// ChannelUT::test_constructor



void
ft_irc::ServerUT::test_getClient_fd(void) {
	struct sockaddr_in clientSocket;
	int clientFd = 15;
	std::string nickname = "gemartin42";
	std::string username = "gerard42";
	std::string realname = "gerard";
	Client::Status status = Client::ONLINE;

	ft_irc::Server::_clients[clientFd] = new Client(clientFd, clientSocket);
	ft_irc::Server::_clients[clientFd]->setNickname(nickname);
	ft_irc::Server::_clients[clientFd]->setUsername(username);
	ft_irc::Server::_clients[clientFd]->setRealname(realname);
	ft_irc::Server::_clients[clientFd]->setStatus(status);

	ASSERT_EQ(ft_irc::Server::_clients[clientFd]->getFd(), clientFd)
	delete ft_irc::Server::_clients[clientFd];

	Client& client1 = *(ft_irc::Server::_clients[clientFd]);
	Client& client2 = getClient(clientFd);

	ASSERT_EQ(&client1, &client2)
}


void
ft_irc::ServerUT::test_getClient_nick(void) {
	struct sockaddr_in clientSocket;
	int clientFd = 18;
	std::string nickname = "gemartin42";
	std::string username = "gerard42";
	std::string realname = "gerard";
	Client::Status status = Client::ONLINE;

	ft_irc::Server::_clients[clientFd] = new Client(clientFd, clientSocket);
	ft_irc::Server::_clients[clientFd]->setNickname(nickname);
	ft_irc::Server::_clients[clientFd]->setUsername(username);
	ft_irc::Server::_clients[clientFd]->setRealname(realname);
	ft_irc::Server::_clients[clientFd]->setStatus(status);

	ASSERT_EQ(ft_irc::Server::_clients[clientFd]->getNickname(), nickname)
    delete ft_irc::Server::_clients[clientFd];

	Client& client1 = *(ft_irc::Server::_clients[clientFd]);
	Client& client2 = getClient(nickname);

	ASSERT_EQ(&client1, &client2)
}
