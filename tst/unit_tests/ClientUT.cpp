#include "ClientUT.hpp"

ft_irc::ClientUT::ClientUT(void) : flt::Testable<ClientUT>("Client"), Client() {
	REGISTER(ClientUT, test_setNickname)
	REGISTER(ClientUT, test_setUsername)
	REGISTER(ClientUT, test_setRealname)
	REGISTER(ClientUT, test_setStatus)

	REGISTER(ClientUT, test_getFd)
	REGISTER(ClientUT, test_getAddress)
	REGISTER(ClientUT, test_getHostname)
	REGISTER(ClientUT, test_getNickname)
	REGISTER(ClientUT, test_getUsername)
	REGISTER(ClientUT, test_getRealname)
	REGISTER(ClientUT, test_getStatus)
	REGISTER(ClientUT, test_getMask)
}

ft_irc::ClientUT::~ClientUT(void) {}

void
ft_irc::ClientUT::test_setNickname(void) {
	ASSERT_THROW(ft_irc::Client::setNickname(""), std::invalid_argument)

	ft_irc::Client::setNickname("smiro");
	ASSERT_EQ(ft_irc::Client::_nickname, "smiro")

	ft_irc::Client::setNickname("marvin");
	ASSERT_EQ(ft_irc::Client::_nickname, "marvin");
}

void
ft_irc::ClientUT::test_setUsername(void) {
	ASSERT_THROW(ft_irc::Client::setUsername(""), std::invalid_argument)

	ft_irc::Client::setUsername("smiro");
	ASSERT_EQ(ft_irc::Client::_username, "smiro")

	ft_irc::Client::setUsername("marvin");
	ASSERT_EQ(ft_irc::Client::_username, "marvin");
}

void
ft_irc::ClientUT::test_setRealname(void) {
	ASSERT_THROW(ft_irc::Client::setRealname(""), std::invalid_argument)

	ft_irc::Client::setRealname("smiro");
	ASSERT_EQ(ft_irc::Client::_realname, "smiro")

	ft_irc::Client::setRealname("marvin");
	ASSERT_EQ(ft_irc::Client::_realname, "marvin");
}

void
ft_irc::ClientUT::test_setStatus(void) {
	ft_irc::Client::setStatus(Client::PASSWORD);
	ASSERT_EQ(ft_irc::Client::_status, Client::PASSWORD)

	ft_irc::Client::setStatus(Client::REGISTER);
	ASSERT_EQ(ft_irc::Client::_status, Client::REGISTER)

	ft_irc::Client::setStatus(Client::ONLINE);
	ASSERT_EQ(ft_irc::Client::_status, Client::ONLINE)

	ft_irc::Client::setStatus(Client::AWAY);
	ASSERT_EQ(ft_irc::Client::_status, Client::AWAY)

	ft_irc::Client::setStatus(Client::DELETE);
	ASSERT_EQ(ft_irc::Client::_status, Client::DELETE)
}

void
ft_irc::ClientUT::test_getFd(void) {
	ft_irc::Client::_fd = 42;
	ASSERT_EQ(ft_irc::Client::getFd(), 42)

	ft_irc::Client::_fd = 84;
	ASSERT_EQ(ft_irc::Client::getFd(), 84)
}

void
ft_irc::ClientUT::test_getAddress(void) {
	ft_irc::Client::_address = "127.0.0.1";
	ASSERT_EQ(ft_irc::Client::getAddress(), "127.0.0.1")

	ft_irc::Client::_address = "10.12.6.4";
	ASSERT_EQ(ft_irc::Client::getAddress(), "10.12.6.4")
}

void
ft_irc::ClientUT::test_getHostname(void) {
	ft_irc::Client::_hostname = "localhost";
	ASSERT_EQ(ft_irc::Client::getHostname(), "localhost")

	ft_irc::Client::_hostname = "irc.com";
	ASSERT_EQ(ft_irc::Client::getHostname(), "irc.com")
}

void
ft_irc::ClientUT::test_getNickname(void) {
	ft_irc::Client::_nickname = "smiro";
	ASSERT_EQ(ft_irc::Client::getNickname(), "smiro")

	ft_irc::Client::_nickname = "marvin";
	ASSERT_EQ(ft_irc::Client::getNickname(), "marvin")
}

void
ft_irc::ClientUT::test_getUsername(void) {
	ft_irc::Client::_username = "smiro";
	ASSERT_EQ(ft_irc::Client::getUsername(), "smiro")

	ft_irc::Client::_username = "marvin";
	ASSERT_EQ(ft_irc::Client::getUsername(), "marvin")
}

void
ft_irc::ClientUT::test_getRealname(void) {
	ft_irc::Client::_realname = "smiro";
	ASSERT_EQ(ft_irc::Client::getRealname(), "smiro")

	ft_irc::Client::_realname = "marvin";
	ASSERT_EQ(ft_irc::Client::getRealname(), "marvin")
}

void
ft_irc::ClientUT::test_getStatus(void) {
	ft_irc::Client::_status = ft_irc::Client::PASSWORD;
	ASSERT_EQ(ft_irc::Client::getStatus(), ft_irc::Client::PASSWORD)

	ft_irc::Client::_status = ft_irc::Client::REGISTER;
	ASSERT_EQ(ft_irc::Client::getStatus(), ft_irc::Client::REGISTER)

	ft_irc::Client::_status = ft_irc::Client::ONLINE;
	ASSERT_EQ(ft_irc::Client::getStatus(), ft_irc::Client::ONLINE)

	ft_irc::Client::_status = ft_irc::Client::AWAY;
	ASSERT_EQ(ft_irc::Client::getStatus(), ft_irc::Client::AWAY)

	ft_irc::Client::_status = ft_irc::Client::DELETE;
	ASSERT_EQ(ft_irc::Client::getStatus(), ft_irc::Client::DELETE)
}

void
ft_irc::ClientUT::test_getMask(void) {
	ft_irc::Client::_nickname = "smiro";
	ft_irc::Client::_username = "smiro";
	ft_irc::Client::_hostname = "localhost.com";

	ASSERT_EQ(ft_irc::Client::getMask(), "smiro!smiro@localhost.com")
}
