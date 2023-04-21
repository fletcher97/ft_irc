#include "CommunicationsUT.hpp"

ft_irc::CommunicationsUT::CommunicationsUT(void) :
	flt::Testable< CommunicationsUT >("Communications"),
	ft_irc::Communications()
{
	REGISTER(CommunicationsUT, test_getFd);
	REGISTER(CommunicationsUT, test_addPfd);
}


ft_irc::CommunicationsUT::~CommunicationsUT(void) {}

void
ft_irc::CommunicationsUT::test_getFd(void)
{
	this->_fd = 42;
	ASSERT_EQ(this->getFd(), 42)
	this->_fd = 84;
	ASSERT_EQ(this->getFd(), 84)
}	// CommunicationsUT::test_getFd


void
ft_irc::CommunicationsUT::test_addPfd(void)
{
	struct pollfd miPollfd = {42, POLLIN, 0};

	struct pollfd miPollfd2 = {42, POLLIN, 0};

	this->addPfd(miPollfd.fd);
	ASSERT_EQ(this->_pfds[this->_pfds.size() - 1].fd, miPollfd.fd);
	ASSERT_EQ(this->_pfds[this->_pfds.size() - 1].events, miPollfd.events);
	ASSERT_EQ(this->_pfds[this->_pfds.size() - 1].revents, miPollfd.revents);
	this->addPfd(miPollfd2.fd);
	ASSERT_EQ(this->_pfds[this->_pfds.size() - 1].fd, miPollfd2.fd);
	ASSERT_EQ(this->_pfds[this->_pfds.size() - 1].events, miPollfd2.events);
	ASSERT_EQ(this->_pfds[this->_pfds.size() - 1].revents, miPollfd2.revents);
}	// CommunicationsUT::test_addPfd
