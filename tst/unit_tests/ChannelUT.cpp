#include <netinet/in.h>

#include "ChannelUT.hpp"

ft_irc::ChannelUT::ChannelUT(void) : flt::Testable<ChannelUT>("Channel"), ft_irc::Channel() {
	REGISTER(ChannelUT, test_setName);
	REGISTER(ChannelUT, test_setTopic);
	REGISTER(ChannelUT, test_setKey);

	REGISTER(ChannelUT, test_getName);
	REGISTER(ChannelUT, test_getTopic);
	REGISTER(ChannelUT, test_getKey);
	REGISTER(ChannelUT, test_addClient);
	REGISTER(ChannelUT, test_banClient);
	REGISTER(ChannelUT, test_inviteClient);
	REGISTER(ChannelUT, test_toggleMode);

	// REGISTER(ChannelUT, test_join);
}

ft_irc::ChannelUT::~ChannelUT(void) {}

void
ft_irc::ChannelUT::test_setName(void) {
	std::string test = "";
	ASSERT_THROW(this->setName(test), std::invalid_argument)
	std::string test2 = "gemartin";
	this->setName(test2);
	ASSERT_EQ(this->__name, test2)
	std::string test3 = "marvin";
	this->setName(test3);
	ASSERT_EQ(this->__name, test3);
}

void
ft_irc::ChannelUT::test_setTopic(void) {
	std::string test = "";
	ASSERT_THROW(this->setTopic(test), std::invalid_argument)
	std::string test2 = "gemartin";
	this->setTopic(test2);
	ASSERT_EQ(this->_topic, test2)
	std::string test3 = "marvin";
	this->setTopic(test3);
	ASSERT_EQ(this->_topic, test3);
}

void
ft_irc::ChannelUT::test_setKey(void) {
	std::string test = "";
	ASSERT_THROW(this->setKey(test), std::invalid_argument)
	std::string test2 = "gemartin";
	this->setKey(test2);
	ASSERT_EQ(this->_key, test2)
	std::string test3 = "marvin";
	this->setKey(test3);
	ASSERT_EQ(this->_key, test3);
}

void
ft_irc::ChannelUT::test_getName(void) {
	this->__name = "gemartin";
	ASSERT_EQ(this->getName(), "gemartin")
	this->__name = "marvin";
	ASSERT_EQ(this->getName(), "marvin")
}

void
ft_irc::ChannelUT::test_getTopic(void) {
	this->_topic = "gemartin";
	ASSERT_EQ(this->getTopic(), "gemartin")
	this->_topic = "marvin";
	ASSERT_EQ(this->getTopic(), "marvin")
}

void
ft_irc::ChannelUT::test_getKey(void) {
	this->_key = "gemartin";
	ASSERT_EQ(this->getKey(), "gemartin")
	this->_key = "marvin";
	ASSERT_EQ(this->getKey(), "marvin")
	this->_key = "";
}

void
ft_irc::ChannelUT::test_addClient(void) {
	Client test(42, sockaddr_in());
	ASSERT(this->addClient(test))
	ASSERT(!this->addClient(test))
	this->_clients.clear();
}

void
ft_irc::ChannelUT::test_banClient(void) {
	std::string test = "smiro";
	ASSERT(this->banClient(test))
	ASSERT(!this->banClient(test))
	this->_banned.clear();
}

void
ft_irc::ChannelUT::test_inviteClient(void) {
	std::string test = "smiro";
	ASSERT(this->inviteClient(test))
	ASSERT(!this->inviteClient(test))
	this->_invited.clear();
}

void
ft_irc::ChannelUT::test_toggleMode(void) {
	this->toggleMode(I);
	ASSERT(this->_mode & I)
	this->toggleMode(I);
	ASSERT(this->_mode ^ I)
	this->toggleMode(M);
	ASSERT(this->_mode & M)
	this->toggleMode(M);
	ASSERT(this->_mode ^ M)
	this->toggleMode(S);
	ASSERT(this->_mode & S)
	this->toggleMode(S);
	ASSERT(this->_mode ^ S)
	this->toggleMode(_T);
	ASSERT(this->_mode & _T)
	this->toggleMode(_T);
	ASSERT(this->_mode ^ _T)
	this->toggleMode(N);
	ASSERT(this->_mode & N)
	this->toggleMode(N);
	ASSERT(this->_mode ^ N)
	ASSERT_THROW(this->toggleMode(-1), std::invalid_argument)
}

// void
// ft_irc::ChannelUT::test_join(void) {
// 	Client test(42, sockaddr_in());
// 	std::string name = "test";
// 	test.setNickname(name);
// 	ASSERT(ft_irc::Channel::join(test))
// 	this->banClient(name);
// 	ASSERT_THROW(ft_irc::Channel::join(test), ft_irc::Channel::BannedClient)
// 	this->_banned.clear();
// 	std::string key = "1234";
// 	this->setKey(key);
// 	ASSERT_THROW(ft_irc::Channel::join(test), std::invalid_argument)
// 	ASSERT_THROW(ft_irc::Channel::join(test, "0000"), std::invalid_argument)
// 	ASSERT(ft_irc::Channel::join(test, "1234"))
// }
