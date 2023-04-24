#include <netinet/in.h>

#include "ChannelUT.hpp"
#include "Log.hpp"

ft_irc::ChannelUT::ChannelUT(void) :
	flt::Testable< ChannelUT >("Channel"),
	ft_irc::Channel()
{
	REGISTER(ChannelUT, test_constructor)

	REGISTER(ChannelUT, test_setName)
	REGISTER(ChannelUT, test_setTopic)
	REGISTER(ChannelUT, test_setKey)
	REGISTER(ChannelUT, test_setClientLimit)

	REGISTER(ChannelUT, test_getName)
	REGISTER(ChannelUT, test_getTopic)
	REGISTER(ChannelUT, test_getKey)
	REGISTER(ChannelUT, test_addClient)
	REGISTER(ChannelUT, test_deleteClient)
	REGISTER(ChannelUT, test_banMask)
	REGISTER(ChannelUT, test_toggleMode)
	REGISTER(ChannelUT, test_isInChannel)

	REGISTER(ChannelUT, test_invite)
	REGISTER(ChannelUT, test_join)
}


ft_irc::ChannelUT::~ChannelUT(void) {}

void
ft_irc::ChannelUT::test_constructor(void)
{
	std::string test1 = "#channel1";
	std::string test2 = "#channel2";

	ft_irc::Channel channel1(test1);
	ft_irc::Channel channel2(test2);

	LOG_TRACE("Testing constructor with different names")
	ASSERT_NEQ(channel1.getName(), channel2.getName())

	LOG_TRACE("Testing asign operator")
	channel1 = channel2;
	ASSERT_EQ(channel1.getName(), channel2.getName())

	LOG_TRACE("Testing that asign operator is a deep copy")
	channel1.setName(test1);
	ASSERT_NEQ(channel1.getName(), channel2.getName())

	LOG_TRACE("Testing that copy constructo")
	ft_irc::Channel channel3(channel1);

	ASSERT_EQ(channel1.getName(), channel3.getName())

	LOG_TRACE("Testing that copy constructor is a deep copy")
	channel3.setName(test2);
	ASSERT_NEQ(channel1.getName(), channel3.getName())
}	// ChannelUT::test_constructor


void
ft_irc::ChannelUT::test_setName(void)
{
	LOG_TRACE("Testing setName with empty string")
	std::string test = "";

	ASSERT_THROW(ft_irc::Channel::setName(test), std::invalid_argument)

	LOG_TRACE("Testing setName with an invalid Channel name")
	test = "channel";
	ASSERT_THROW(ft_irc::Channel::setName(test), std::invalid_argument)

	LOG_TRACE("Testing setName with a Channel name with invalid character: SPACE")
	test = "#channel 1";
	ASSERT_THROW(ft_irc::Channel::setName(test), std::invalid_argument)

	LOG_TRACE("Testing setName with a Channel name with invalid character: COMMA")
	test = "#channel,1";
	ASSERT_THROW(ft_irc::Channel::setName(test), std::invalid_argument)

	LOG_TRACE("Testing setName with a Channel name with invalid character: G^BELL(0x07)")
	test = "#channel";
	test.at(1) = char(0x07);
	ASSERT_THROW(ft_irc::Channel::setName(test), std::invalid_argument)

	LOG_TRACE("Testing setName with a Channel name with invalid character: SPACE")
	test = "&channel 1";
	ASSERT_THROW(ft_irc::Channel::setName(test), std::invalid_argument)

	LOG_TRACE("Testing setName with a Channel name with invalid character: COMMA")
	test = "&channel,1";
	ASSERT_THROW(ft_irc::Channel::setName(test), std::invalid_argument)

	LOG_TRACE("Testing setName with a Channel name with invalid character: G^BELL(0x07)")
	test = "&channel";
	test.at(1) = char(0x07);
	ASSERT_THROW(ft_irc::Channel::setName(test), std::invalid_argument)

	LOG_TRACE("Testing setName with a valid name: #channel")
	test = "#channel";
	ASSERT_NOTHROW(ft_irc::Channel::setName(test))
	ASSERT_EQ(ft_irc::Channel::_name, test)

	LOG_TRACE("Testing setName with a valid name: &channel")
	test = "&channel";
	ASSERT_NOTHROW(ft_irc::Channel::setName(test);)
	ASSERT_EQ(ft_irc::Channel::_name, test)
}	// ChannelUT::test_setName


void
ft_irc::ChannelUT::test_setTopic(void)
{
	ft_irc::Client test(42, sockaddr_in());
	std::string topic = "";


	LOG_TRACE("Testing setTopic with a client not on channel")
	ASSERT_THROW(ft_irc::Channel::setTopic(test, topic), ft_irc::Channel::NotOnChannel);

	ft_irc::Channel::addClient(test);
	this->_clients.at(test.getFd()).mode = 0;

	LOG_TRACE("Testing setTopic with a client with no privileges on ProtectedTopic mode")
	ft_irc::Channel::toggleMode(PROTECTED_TOPIC);
	ASSERT_THROW(ft_irc::Channel::setTopic(test, topic), ft_irc::Channel::NoPrivsOnChannel);

	LOG_TRACE("Testing setTopic with a client with privileges (OPERATOR) on ProtectedTopic mode")
	topic = "gemartin";
	ft_irc::Channel::_clients.at(test.getFd()).mode = OPERATOR;
	ASSERT_NOTHROW(ft_irc::Channel::setTopic(test, topic));
	ASSERT_EQ(ft_irc::Channel::_topic, topic)

	LOG_TRACE("Testing setTopic with a client with privileges (HALFOP) on ProtectedTopic mode")
	ft_irc::Channel::_clients.at(test.getFd()).mode = HALFOP;
	ASSERT_NOTHROW(ft_irc::Channel::setTopic(test, topic));
	ASSERT_EQ(ft_irc::Channel::_topic, topic)

	LOG_TRACE("Testing setTopic with a client with privileges (PROTECTED) on ProtectedTopic mode")
	ft_irc::Channel::_clients.at(test.getFd()).mode = PROTECTED;
	ASSERT_NOTHROW(ft_irc::Channel::setTopic(test, topic));
	ASSERT_EQ(ft_irc::Channel::_topic, topic)
	ft_irc::Channel::toggleMode(PROTECTED_TOPIC);

	LOG_TRACE("Testing setTopic with no ProtectedTopic mode")
	ft_irc::Channel::_clients.at(test.getFd()).mode = 0;
	topic = "marvin";
	ASSERT_NOTHROW(ft_irc::Channel::setTopic(test, topic));
	ASSERT_EQ(ft_irc::Channel::_topic, topic)
	ft_irc::Channel::_clients.clear();
}	// ChannelUT::test_setTopic


void
ft_irc::ChannelUT::test_setKey(void)
{
	std::string test = "";

	LOG_TRACE("Testing setKey with empty string")
	ASSERT_THROW(ft_irc::Channel::setKey(test), std::invalid_argument)

	test = "gemartin";
	ft_irc::Channel::setKey(test);
	LOG_TRACE("Testing setKey with 'gmartin'")
	ASSERT_EQ(ft_irc::Channel::_key, test)

	test = "marvin";
	LOG_TRACE("Testing setKey with 'marvin'")
	ft_irc::Channel::setKey(test);
	ASSERT_EQ(ft_irc::Channel::_key, test)
}	// ChannelUT::test_setKey


void
ft_irc::ChannelUT::test_setClientLimit(void)
{
	LOG_TRACE("Testing setClientLimit invalid argumnets: 0")
	ASSERT_THROW(ft_irc::Channel::setClientLimit(0), std::invalid_argument)
	LOG_TRACE("Testing setClientLimit invalid argumnets: -10")
	ASSERT_THROW(ft_irc::Channel::setClientLimit(-10), std::invalid_argument)

	ft_irc::Channel::setClientLimit(42);
	LOG_TRACE("Testing setClientLimit with: 42")
	ASSERT_EQ(ft_irc::Channel::_client_limit, 42)

	ft_irc::Channel::setClientLimit(10);
	LOG_TRACE("Testing setClientLimit with: 10")
	ASSERT_EQ(ft_irc::Channel::_client_limit, 10)
	ft_irc::Channel::_client_limit = 0;
}	// ChannelUT::test_setClientLimit


void
ft_irc::ChannelUT::test_getName(void)
{
	ft_irc::Channel::_name = "gemartin";
	LOG_TRACE("Testing getName: gmartin")
	ASSERT_EQ(ft_irc::Channel::getName(), "gemartin")

	ft_irc::Channel::_name = "marvin";
	LOG_TRACE("Testing getName: marvin")
	ASSERT_EQ(ft_irc::Channel::getName(), "marvin")
}	// ChannelUT::test_getName


void
ft_irc::ChannelUT::test_getTopic(void)
{
	ft_irc::Channel::_topic = "gemartin";
	LOG_TRACE("Testing getTopic: gmartin")
	ASSERT_EQ(ft_irc::Channel::getTopic(), "gemartin")

	ft_irc::Channel::_topic = "marvin";
	LOG_TRACE("Testing getTopic: marvin")
	ASSERT_EQ(ft_irc::Channel::getTopic(), "marvin")
}	// ChannelUT::test_getTopic


void
ft_irc::ChannelUT::test_getKey(void)
{
	ft_irc::Channel::_key = "gemartin";
	LOG_TRACE("Testing getKey: gmartin")
	ASSERT_EQ(ft_irc::Channel::getKey(), "gemartin")

	ft_irc::Channel::_key = "marvin";
	LOG_TRACE("Testing getKey: marvin")
	ASSERT_EQ(ft_irc::Channel::getKey(), "marvin")
	ft_irc::Channel::_key = "";
}	// ChannelUT::test_getKey


void
ft_irc::ChannelUT::test_addClient(void)
{
	Client test(42, sockaddr_in());

	LOG_TRACE("Testing addClient valid input")
	ASSERT(ft_irc::Channel::addClient(test))

	LOG_TRACE("Testing addClient, first client has FOUNDER mode")
	ASSERT(ft_irc::Channel::_clients.at(test.getFd()).mode & (FOUNDER))
	LOG_TRACE("Testing addClient, first client has OPERATOR mode")
	ASSERT(ft_irc::Channel::_clients.at(test.getFd()).mode & (OPERATOR))

	LOG_TRACE("Testing addClient dosen't add a client that is already on channel")
	ASSERT(!ft_irc::Channel::addClient(test))
	ft_irc::Channel::_clients.clear();
}	// ChannelUT::test_addClient


void
ft_irc::ChannelUT::test_deleteClient(void)
{
	Client test1(42, sockaddr_in());
	Client test2(84, sockaddr_in());

	LOG_TRACE("test deleteClient: client not in channel")
	ASSERT_THROW(ft_irc::Channel::deleteClient(test1), ft_irc::Channel::NotOnChannel)

	ft_irc::Channel::addClient(test1);
	ft_irc::Channel::addClient(test2);

	LOG_TRACE("test deleteClient: delete one of two")
	ASSERT(!ft_irc::Channel::deleteClient(test1))
	ASSERT_THROW(ft_irc::Channel::deleteClient(test1), ft_irc::Channel::NotOnChannel)

	LOG_TRACE("test deleteClient: delete last client")
	ASSERT(ft_irc::Channel::deleteClient(test2))
	ASSERT_THROW(ft_irc::Channel::deleteClient(test2), ft_irc::Channel::NotOnChannel)
}	// ChannelUT::test_deleteClient


void
ft_irc::ChannelUT::test_isInChannel(void)
{
	Client test(42, sockaddr_in());
	Client test2(84, sockaddr_in());
	std::string test_nick = "42";
	std::string test2_nick = "84";

	test.setNickname(test_nick);
	test2.setNickname(test2_nick);

	LOG_TRACE("Testing isInChannle with a client on an empty channel by reference")
	ASSERT(!ft_irc::Channel::isInChannel(test))

	LOG_TRACE("Testing isInChannle with a client on an empty channel by nickname")
	ASSERT(!ft_irc::Channel::isInChannel(test.getNickname()))

	ft_irc::Channel::addClient(test);
	LOG_TRACE("Testing isInChannle with a client on channel by reference")
	ASSERT(ft_irc::Channel::isInChannel(test))

	LOG_TRACE("Testing isInChannle with a client on channel by nickname")
	ASSERT(ft_irc::Channel::isInChannel(test.getNickname()))

	LOG_TRACE("Testing isInChannle with a client not on channel by reference")
	ASSERT(!ft_irc::Channel::isInChannel(test2))

	LOG_TRACE("Testing isInChannle with a client not on channel by nickname")
	ASSERT(!ft_irc::Channel::isInChannel(test2.getNickname()))
	ft_irc::Channel::_clients.clear();
}	// ChannelUT::test_isInChannel


void
ft_irc::ChannelUT::test_banMask(void)
{
	std::string test = "smiro!*@*";

	LOG_TRACE("Testing banMask with correct input")
	ASSERT(ft_irc::Channel::banMask(test))

	LOG_TRACE("Testing banMask with a mask that is already banned")
	ASSERT(!ft_irc::Channel::banMask(test))
	ft_irc::Channel::_masks.clear();

	LOG_TRACE("Testing banMask with a mask that is already in mask map but not banned")
	ft_irc::Channel::_masks.insert(std::make_pair< std::string, mask_mode >(test, INVITE));
	ASSERT(ft_irc::Channel::banMask(test))
	ft_irc::Channel::_masks.clear();
}	// ChannelUT::test_banMask


void
ft_irc::ChannelUT::test_toggleMode(void)
{
	LOG_TRACE("Testing toggleMode: INVITE_ONLY")
	ft_irc::Channel::toggleMode(INVITE_ONLY);
	ASSERT(ft_irc::Channel::_mode & (INVITE_ONLY))
	ft_irc::Channel::toggleMode(INVITE_ONLY);
	ASSERT(!(ft_irc::Channel::_mode & (INVITE_ONLY)))

	LOG_TRACE("Testing toggleMode: MODERATE")
	ft_irc::Channel::toggleMode(MODERATE);
	ASSERT(ft_irc::Channel::_mode & (MODERATE))
	ft_irc::Channel::toggleMode(MODERATE);
	ASSERT(!(ft_irc::Channel::_mode & (MODERATE)))

	LOG_TRACE("Testing toggleMode: SECRET")
	ft_irc::Channel::toggleMode(SECRET);
	ASSERT(ft_irc::Channel::_mode & (SECRET))
	ft_irc::Channel::toggleMode(SECRET);
	ASSERT(!(ft_irc::Channel::_mode & (SECRET)))

	LOG_TRACE("Testing toggleMode: PROTECTED_TOPIC")
	ft_irc::Channel::toggleMode(PROTECTED_TOPIC);
	ASSERT(ft_irc::Channel::_mode & (PROTECTED_TOPIC))
	ft_irc::Channel::toggleMode(PROTECTED_TOPIC);
	ASSERT(!(ft_irc::Channel::_mode & (PROTECTED_TOPIC)))

	LOG_TRACE("Testing toggleMode: NOT_EXTERNAL_MSGS")
	ft_irc::Channel::toggleMode(NOT_EXTERNAL_MSGS);
	ASSERT(ft_irc::Channel::_mode & (NOT_EXTERNAL_MSGS))
	ft_irc::Channel::toggleMode(NOT_EXTERNAL_MSGS);
	ASSERT(!(ft_irc::Channel::_mode & (NOT_EXTERNAL_MSGS)))

	LOG_TRACE("Testing toggleMode: invalid argument: -1")
	ASSERT_THROW(ft_irc::Channel::toggleMode(-1), std::invalid_argument)

	LOG_TRACE("Testing toggleMode: invalid argument: 100")
	ASSERT_THROW(ft_irc::Channel::toggleMode(100), std::invalid_argument)
}	// ChannelUT::test_toggleMode


void
ft_irc::ChannelUT::test_invite(void)
{
	Client client(42, sockaddr_in());
	std::string nickname = "smiro";


	LOG_TRACE("Testing invite with a client not on channel")
	ASSERT_THROW(ft_irc::Channel::invite(client, nickname), ft_irc::Channel::NotOnChannel)
	ft_irc::Channel::addClient(client);
	ft_irc::Channel::_clients.at(client.getFd()).mode ^= OPERATOR;

	LOG_TRACE("Testing invite a nickname that is already tracked but not invited")
	ft_irc::Channel::_masks.insert(std::make_pair< std::string, mask_mode >(nickname, BAN));
	ASSERT(ft_irc::Channel::invite(client, nickname))
	ft_irc::Channel::_masks.clear();

	LOG_TRACE("Testing invite with a client with no privileges on InviteOnly mode")
	ft_irc::Channel::toggleMode(INVITE_ONLY);
	ASSERT_THROW(ft_irc::Channel::invite(client, nickname), ft_irc::Channel::NoPrivsOnChannel)
	ft_irc::Channel::toggleMode(INVITE_ONLY);

	LOG_TRACE("Testing invite correct input")
	ASSERT(ft_irc::Channel::invite(client, nickname))
	LOG_TRACE("Testing invite dosent invite a client that is already invited")
	ASSERT(!ft_irc::Channel::invite(client, nickname))


	client.setNickname(nickname);
	LOG_TRACE("Testing invite a client that is already on channel")
	ASSERT_THROW(ft_irc::Channel::invite(client, nickname), ft_irc::Channel::AlreadyOnChannel)
	ft_irc::Channel::_masks.clear();
	ft_irc::Channel::_clients.clear();
}	// ChannelUT::test_invite


void
ft_irc::ChannelUT::test_join(void)
{
	ft_irc::Client test = ft_irc::Client(42, sockaddr_in());
	ft_irc::Client tmp = ft_irc::Client(20, sockaddr_in());
	std::string name = "test";
	std::string key = "1234";

	test.setNickname(name);

	LOG_TRACE("Testing join with a banned client")
	ft_irc::Channel::banMask(test.getMask());
	ASSERT_THROW(ft_irc::Channel::join(test), ft_irc::Channel::BannedClient)
	ft_irc::Channel::_masks.clear();

	ft_irc::Channel::setKey(key);
	LOG_TRACE("Testing join a channel with key: no key")
	ASSERT_THROW(ft_irc::Channel::join(test), std::invalid_argument)
	LOG_TRACE("Testing join a channel with key: wrong key")
	ASSERT_THROW(ft_irc::Channel::join(test, "0000"), std::invalid_argument)
	LOG_TRACE("Testing join a channel with key: correct key")
	ASSERT(ft_irc::Channel::join(test, "1234"))
	ft_irc::Channel::_clients.clear();
	ft_irc::Channel::_key = "";

	ft_irc::Channel::addClient(tmp);
	ft_irc::Channel::toggleMode(INVITE_ONLY);
	LOG_TRACE("Testing join a channel with InviteOnly mode: not invited client")
	ASSERT_THROW(ft_irc::Channel::join(test), ft_irc::Channel::InviteOnlyChannel)
	ft_irc::Channel::invite(tmp, test.getMask());
	LOG_TRACE("Testing join a channel with InviteOnly mode: invited client")
	ASSERT(ft_irc::Channel::join(test))
	ft_irc::Channel::_clients.clear();
	ft_irc::Channel::toggleMode(INVITE_ONLY);

	ft_irc::Channel::addClient(tmp);
	ft_irc::Channel::setClientLimit(1);
	LOG_TRACE("Testing join a full channel")
	ASSERT_THROW(ft_irc::Channel::join(test), ft_irc::Channel::ChannelIsFull)
	ft_irc::Channel::_client_limit = 0;

	LOG_TRACE("Testing join valid client")
	ASSERT(ft_irc::Channel::join(test))
	LOG_TRACE("Testing join doesnt join a client that is already on channel")
	ASSERT(!ft_irc::Channel::join(test))
	ft_irc::Channel::_clients.clear();
}	// ChannelUT::test_join
