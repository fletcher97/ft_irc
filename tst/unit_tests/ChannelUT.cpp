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
	REGISTER(ChannelUT, test_banMask);
	REGISTER(ChannelUT, test_toggleMode);

	REGISTER(ChannelUT, test_invite);
	REGISTER(ChannelUT, test_join);
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
	ASSERT(this->_clients.at(test.getFd()).mode & O);
	ASSERT(!this->addClient(test))
	this->_clients.clear();
}

void
ft_irc::ChannelUT::test_banMask(void) {
	std::string test = "smiro!*@*";
	ASSERT(this->banMask(test))
	ASSERT(!this->banMask(test))
	this->_masks.clear();
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

void
ft_irc::ChannelUT::test_invite(void) {
	Client client(42, sockaddr_in());
	std::string nickname = "smiro";

	ASSERT_THROW(ft_irc::Channel::invite(client, nickname), ft_irc::Channel::NotOnChannel)
	ft_irc::Channel::addClient(client);
	this->_clients.at(client.getFd()).mode ^= O;

	this->toggleMode(I);
	ASSERT_THROW(ft_irc::Channel::invite(client, nickname), ft_irc::Channel::NotOperOnChannel)
	this->toggleMode(I);

	ASSERT(ft_irc::Channel::invite(client, nickname))
	ASSERT(!ft_irc::Channel::invite(client, nickname))

	client.setNickname(nickname);
	ASSERT_THROW(ft_irc::Channel::invite(client, nickname), ft_irc::Channel::AlreadyOnChannel)
	this->_masks.clear();
	this->_clients.clear();
}

void
ft_irc::ChannelUT::test_join(void) {
	ft_irc::Client test = ft_irc::Client(42, sockaddr_in());
	ft_irc::Client tmp = ft_irc::Client(20, sockaddr_in());
	std::string name = "test";
	std::string key = "1234";
	test.setNickname(name);

	ASSERT(ft_irc::Channel::join(test))
	this->_clients.clear();

	this->banMask(test.getMask());
	ASSERT_THROW(ft_irc::Channel::join(test), ft_irc::Channel::BannedClient)
	this->_masks.clear();

	this->setKey(key);
	ASSERT_THROW(ft_irc::Channel::join(test), std::invalid_argument)
	ASSERT_THROW(ft_irc::Channel::join(test, "0000"), std::invalid_argument)
	ASSERT(ft_irc::Channel::join(test, "1234"))
	this->_clients.clear();
	this->_key = "";

	this->addClient(tmp);
	this->toggleMode(I);
	ASSERT_THROW(ft_irc::Channel::join(test), ft_irc::Channel::InviteOnlyChannel)
	this->invite(tmp, name);
	ASSERT(ft_irc::Channel::join(test))
	this->_clients.clear();
	this->toggleMode(I);

	this->addClient(tmp);
	this->setClientLimit(1);
	ASSERT_THROW(ft_irc::Channel::join(test), ft_irc::Channel::ChannelIsFull)
	this->_client_limit = 0;

	ASSERT(ft_irc::Channel::join(test))
	ASSERT(!ft_irc::Channel::join(test))
	this->_clients.clear();
}
