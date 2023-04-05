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
}

void
ft_irc::ChannelUT::test_addClient(void) {
	Client test(42, sockaddr_in());
	ASSERT(this->addClient(test))
	ASSERT(!this->addClient(test))
}
