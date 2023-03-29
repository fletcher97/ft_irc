#include "ClientUT.hpp"

ClientUT::ClientUT(void) : flt::Testable<ClientUT>("Client"), Client() {
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
}

ClientUT::~ClientUT(void) {}

void ClientUT::test_setNickname(void) {
	ASSERT_THROW(this->setNickname(""), std::invalid_argument)
	this->setNickname("smiro");
	ASSERT_EQ(this->_nickname, "smiro")
	this->setNickname("marvin");
	ASSERT_EQ(this->_nickname, "marvin");
}

void ClientUT::test_setUsername(void) {
	ASSERT_THROW(this->setUsername(""), std::invalid_argument)
	this->setUsername("smiro");
	ASSERT_EQ(this->_username, "smiro")
	this->setUsername("marvin");
	ASSERT_EQ(this->_username, "marvin");
}

void ClientUT::test_setRealname(void) {
	ASSERT_THROW(this->setRealname(""), std::invalid_argument)
	this->setRealname("smiro");
	ASSERT_EQ(this->_realname, "smiro")
	this->setRealname("marvin");
	ASSERT_EQ(this->_realname, "marvin");
}

void ClientUT::test_setStatus(void) {
	this->setStatus(Client::PASSWORD);
	ASSERT_EQ(this->_status, Client::PASSWORD)
	this->setStatus(Client::REGISTER);
	ASSERT_EQ(this->_status, Client::REGISTER)
	this->setStatus(Client::ONLINE);
	ASSERT_EQ(this->_status, Client::ONLINE)
	this->setStatus(Client::AWAY);
	ASSERT_EQ(this->_status, Client::AWAY)
	this->setStatus(Client::DELETE);
	ASSERT_EQ(this->_status, Client::DELETE)
}

void ClientUT::test_getFd(void) {
	this->_fd = 42;
	ASSERT_EQ(this->getFd(), 42)
	this->_fd = 84;
	ASSERT_EQ(this->getFd(), 84)
}

void ClientUT::test_getAddress(void) {
	this->_address = "127.0.0.1";
	ASSERT_EQ(this->getAddress(), "127.0.0.1")
	this->_address = "10.12.6.4";
	ASSERT_EQ(this->getAddress(), "10.12.6.4")
}

void ClientUT::test_getHostname(void) {
	this->_hostname = "localhost";
	ASSERT_EQ(this->getHostname(), "localhost")
	this->_hostname = "irc.com";
	ASSERT_EQ(this->getHostname(), "irc.com")
}

void ClientUT::test_getNickname(void) {
	this->_nickname = "smiro";
	ASSERT_EQ(this->getNickname(), "smiro")
	this->_nickname = "marvin";
	ASSERT_EQ(this->getNickname(), "marvin")
}

void ClientUT::test_getUsername(void) {
	this->_username = "smiro";
	ASSERT_EQ(this->getUsername(), "smiro")
	this->_username = "marvin";
	ASSERT_EQ(this->getUsername(), "marvin")
}

void ClientUT::test_getRealname(void) {
	this->_realname = "smiro";
	ASSERT_EQ(this->getRealname(), "smiro")
	this->_realname = "marvin";
	ASSERT_EQ(this->getRealname(), "marvin")
}

void ClientUT::test_getStatus(void) {
	this->_status = Client::PASSWORD;
	ASSERT_EQ(this->getStatus(), Client::PASSWORD)
	this->_status = Client::REGISTER;
	ASSERT_EQ(this->getStatus(), Client::REGISTER)
	this->_status = Client::ONLINE;
	ASSERT_EQ(this->getStatus(), Client::ONLINE)
	this->_status = Client::AWAY;
	ASSERT_EQ(this->getStatus(), Client::AWAY)
	this->_status = Client::DELETE;
	ASSERT_EQ(this->getStatus(), Client::DELETE)
}
