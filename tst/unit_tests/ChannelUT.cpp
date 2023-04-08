#include <netinet/in.h>

#include "ChannelUT.hpp"

ft_irc::ChannelUT::ChannelUT(void) : flt::Testable<ChannelUT>("Channel"), ft_irc::Channel() {
	REGISTER(ChannelUT, test_setName)
	REGISTER(ChannelUT, test_setTopic)
	REGISTER(ChannelUT, test_setKey)
	REGISTER(ChannelUT, test_setClientLimit)

	REGISTER(ChannelUT, test_getName)
	REGISTER(ChannelUT, test_getTopic)
	REGISTER(ChannelUT, test_getKey)
	REGISTER(ChannelUT, test_addClient)
	REGISTER(ChannelUT, test_banMask)
	REGISTER(ChannelUT, test_toggleMode)
	REGISTER(ChannelUT, test_isInChannel)

	REGISTER(ChannelUT, test_invite)
	REGISTER(ChannelUT, test_join)
}

ft_irc::ChannelUT::~ChannelUT(void) {}

void
ft_irc::ChannelUT::test_setName(void) {
	std::string test = "";
	ASSERT_THROW(ft_irc::Channel::setName(test), std::invalid_argument)

	test = "channel";
	ASSERT_THROW(ft_irc::Channel::setName(test), std::invalid_argument)

	test = "#channel 1";
	ASSERT_THROW(ft_irc::Channel::setName(test), std::invalid_argument)

	test = "#channel,1";
	ASSERT_THROW(ft_irc::Channel::setName(test), std::invalid_argument)

	test = "#channel";
	test.at(1) = char(0x07);
	ASSERT_THROW(ft_irc::Channel::setName(test), std::invalid_argument)

	test = "#channel";
	ASSERT_NOTHROW(ft_irc::Channel::setName(test))
	ASSERT_EQ(ft_irc::Channel::_name, test)

	test = "&channel";
	ASSERT_NOTHROW(ft_irc::Channel::setName(test);)
	ASSERT_EQ(ft_irc::Channel::_name, test)
}

void
ft_irc::ChannelUT::test_setTopic(void) {
	ft_irc::Client test(42, sockaddr_in());
	std::string topic = "";


	ASSERT_THROW(ft_irc::Channel::setTopic(test, topic), ft_irc::Channel::NotOnChannel);

	ft_irc::Channel::addClient(test);
	this->_clients.at(test.getFd()).mode = 0;

	ft_irc::Channel::toggleMode(PROTECTED_TOPIC);
	ASSERT_THROW(ft_irc::Channel::setTopic(test, topic), ft_irc::Channel::NoPrivsOnChannel);

	topic = "gemartin";
	ft_irc::Channel::_clients.at(test.getFd()).mode = OPERATOR;
	ASSERT_NOTHROW(ft_irc::Channel::setTopic(test, topic));
	ASSERT_EQ(ft_irc::Channel::_topic, topic)

	ft_irc::Channel::_clients.at(test.getFd()).mode = HALFOP;
	ASSERT_NOTHROW(ft_irc::Channel::setTopic(test, topic));
	ASSERT_EQ(ft_irc::Channel::_topic, topic)

	ft_irc::Channel::_clients.at(test.getFd()).mode = PROTECTED;
	ASSERT_NOTHROW(ft_irc::Channel::setTopic(test, topic));
	ASSERT_EQ(ft_irc::Channel::_topic, topic)
	ft_irc::Channel::toggleMode(PROTECTED_TOPIC);

	ft_irc::Channel::_clients.at(test.getFd()).mode = 0;
	topic = "marvin";
	ASSERT_NOTHROW(ft_irc::Channel::setTopic(test, topic));
	ASSERT_EQ(ft_irc::Channel::_topic, topic)
	ft_irc::Channel::_clients.clear();
}

void
ft_irc::ChannelUT::test_setKey(void) {
	std::string test = "";
	ASSERT_THROW(ft_irc::Channel::setKey(test), std::invalid_argument)

	test = "gemartin";
	ft_irc::Channel::setKey(test);
	ASSERT_EQ(ft_irc::Channel::_key, test)

	test = "marvin";
	ft_irc::Channel::setKey(test);
	ASSERT_EQ(ft_irc::Channel::_key, test)
}

void
ft_irc::ChannelUT::test_setClientLimit(void) {
	ASSERT_THROW(ft_irc::Channel::setClientLimit(0), std::invalid_argument)
	ASSERT_THROW(ft_irc::Channel::setClientLimit(-10), std::invalid_argument)

	ft_irc::Channel::setClientLimit(42);
	ASSERT_EQ(ft_irc::Channel::_client_limit, 42)

	ft_irc::Channel::setClientLimit(10);
	ASSERT_EQ(ft_irc::Channel::_client_limit, 10)
	ft_irc::Channel::_client_limit = 0;
}

void
ft_irc::ChannelUT::test_getName(void) {
	ft_irc::Channel::_name = "gemartin";
	ASSERT_EQ(ft_irc::Channel::getName(), "gemartin")

	ft_irc::Channel::_name = "marvin";
	ASSERT_EQ(ft_irc::Channel::getName(), "marvin")
}

void
ft_irc::ChannelUT::test_getTopic(void) {
	ft_irc::Channel::_topic = "gemartin";
	ASSERT_EQ(ft_irc::Channel::getTopic(), "gemartin")

	ft_irc::Channel::_topic = "marvin";
	ASSERT_EQ(ft_irc::Channel::getTopic(), "marvin")
}

void
ft_irc::ChannelUT::test_getKey(void) {
	ft_irc::Channel::_key = "gemartin";
	ASSERT_EQ(ft_irc::Channel::getKey(), "gemartin")

	ft_irc::Channel::_key = "marvin";
	ASSERT_EQ(ft_irc::Channel::getKey(), "marvin")
	ft_irc::Channel::_key = "";
}

void
ft_irc::ChannelUT::test_addClient(void) {
	Client test(42, sockaddr_in());

	ASSERT(ft_irc::Channel::addClient(test))

	ASSERT(ft_irc::Channel::_clients.at(test.getFd()).mode & OPERATOR)
	ASSERT(ft_irc::Channel::_clients.at(test.getFd()).mode & FOUNDER)

	ASSERT(!ft_irc::Channel::addClient(test))
	ft_irc::Channel::_clients.clear();
}

void
ft_irc::ChannelUT::test_isInChannel(void) {
	Client test(42, sockaddr_in());
	Client test2(84, sockaddr_in());
	std::string	test_nick = "42";
	std::string	test2_nick = "84";
	test.setNickname(test_nick);
	test2.setNickname(test2_nick);

	ft_irc::Channel::addClient(test);
	ASSERT(ft_irc::Channel::isInChannel(test))

	ASSERT(ft_irc::Channel::isInChannel(test.getNickname()))

	ASSERT(!ft_irc::Channel::isInChannel(test2))

	ASSERT(!ft_irc::Channel::isInChannel(test2.getNickname()))
	ft_irc::Channel::_clients.clear();
}

void
ft_irc::ChannelUT::test_banMask(void) {
	std::string test = "smiro!*@*";

	ASSERT(ft_irc::Channel::banMask(test))

	ASSERT(!ft_irc::Channel::banMask(test))
	ft_irc::Channel::_masks.clear();
}

void
ft_irc::ChannelUT::test_toggleMode(void) {
	ft_irc::Channel::toggleMode(INVITE_ONLY);
	ASSERT(ft_irc::Channel::_mode & INVITE_ONLY)
	ft_irc::Channel::toggleMode(INVITE_ONLY);
	ASSERT(!(ft_irc::Channel::_mode & INVITE_ONLY))

	ft_irc::Channel::toggleMode(MODERATE);
	ASSERT(ft_irc::Channel::_mode & MODERATE)
	ft_irc::Channel::toggleMode(MODERATE);
	ASSERT(!(ft_irc::Channel::_mode & MODERATE))

	ft_irc::Channel::toggleMode(SECRET);
	ASSERT(ft_irc::Channel::_mode & SECRET)
	ft_irc::Channel::toggleMode(SECRET);
	ASSERT(!(ft_irc::Channel::_mode & SECRET))

	ft_irc::Channel::toggleMode(PROTECTED_TOPIC);
	ASSERT(ft_irc::Channel::_mode & PROTECTED_TOPIC)
	ft_irc::Channel::toggleMode(PROTECTED_TOPIC);
	ASSERT(!(ft_irc::Channel::_mode & PROTECTED_TOPIC))

	ft_irc::Channel::toggleMode(NOT_EXTERNAL_MSGS);
	ASSERT(ft_irc::Channel::_mode & NOT_EXTERNAL_MSGS)
	ft_irc::Channel::toggleMode(NOT_EXTERNAL_MSGS);
	ASSERT(!(ft_irc::Channel::_mode & NOT_EXTERNAL_MSGS))

	ASSERT_THROW(ft_irc::Channel::toggleMode(-1), std::invalid_argument)
}

void
ft_irc::ChannelUT::test_invite(void) {
	Client client(42, sockaddr_in());
	std::string nickname = "smiro";

	ASSERT_THROW(ft_irc::Channel::invite(client, nickname), ft_irc::Channel::NotOnChannel)
	ft_irc::Channel::addClient(client);
	ft_irc::Channel::_clients.at(client.getFd()).mode ^= OPERATOR;

	ft_irc::Channel::toggleMode(INVITE_ONLY);
	ASSERT_THROW(ft_irc::Channel::invite(client, nickname), ft_irc::Channel::NoPrivsOnChannel)
	ft_irc::Channel::toggleMode(INVITE_ONLY);

	ASSERT(ft_irc::Channel::invite(client, nickname))
	ASSERT(!ft_irc::Channel::invite(client, nickname))

	client.setNickname(nickname);
	ASSERT_THROW(ft_irc::Channel::invite(client, nickname), ft_irc::Channel::AlreadyOnChannel)
	ft_irc::Channel::_masks.clear();
	ft_irc::Channel::_clients.clear();
}

void
ft_irc::ChannelUT::test_join(void) {
	ft_irc::Client test = ft_irc::Client(42, sockaddr_in());
	ft_irc::Client tmp = ft_irc::Client(20, sockaddr_in());
	std::string name = "test";
	std::string key = "1234";
	test.setNickname(name);

	ASSERT(ft_irc::Channel::join(test))
	ft_irc::Channel::_clients.clear();

	ft_irc::Channel::banMask(test.getMask());
	ASSERT_THROW(ft_irc::Channel::join(test), ft_irc::Channel::BannedClient)
	ft_irc::Channel::_masks.clear();

	ft_irc::Channel::setKey(key);
	ASSERT_THROW(ft_irc::Channel::join(test), std::invalid_argument)
	ASSERT_THROW(ft_irc::Channel::join(test, "0000"), std::invalid_argument)
	ASSERT(ft_irc::Channel::join(test, "1234"))
	ft_irc::Channel::_clients.clear();
	ft_irc::Channel::_key = "";

	ft_irc::Channel::addClient(tmp);
	ft_irc::Channel::toggleMode(INVITE_ONLY);
	ASSERT_THROW(ft_irc::Channel::join(test), ft_irc::Channel::InviteOnlyChannel)
	ft_irc::Channel::invite(tmp, test.getMask());
	ASSERT(ft_irc::Channel::join(test))
	ft_irc::Channel::_clients.clear();
	ft_irc::Channel::toggleMode(INVITE_ONLY);

	ft_irc::Channel::addClient(tmp);
	ft_irc::Channel::setClientLimit(1);
	ASSERT_THROW(ft_irc::Channel::join(test), ft_irc::Channel::ChannelIsFull)
	ft_irc::Channel::_client_limit = 0;

	ASSERT(ft_irc::Channel::join(test))
	ASSERT(!ft_irc::Channel::join(test))
	ft_irc::Channel::_clients.clear();
}
