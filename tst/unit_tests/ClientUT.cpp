#include <netinet/in.h>

#include "Log.hpp"

#include "ClientUT.hpp"

ft_irc::ClientUT::ClientUT(void) :
	flt::Testable< ClientUT >("Client"),
	Client()
{
	REGISTER(ClientUT, test_constructor)
	REGISTER(ClientUT, test_setNickname)
	REGISTER(ClientUT, test_setUsername)
	REGISTER(ClientUT, test_setRealname)
	REGISTER(ClientUT, test_setStatus)
	REGISTER(ClientUT, test_toggleMode)

	REGISTER(ClientUT, test_getFd)
	REGISTER(ClientUT, test_getHostname)
	REGISTER(ClientUT, test_getNickname)
	REGISTER(ClientUT, test_getUsername)
	REGISTER(ClientUT, test_getRealname)
	REGISTER(ClientUT, test_getStatus)
	REGISTER(ClientUT, test_getMask)
}


ft_irc::ClientUT::~ClientUT(void) {}


void
ft_irc::ClientUT::test_constructor(void)
{
	ft_irc::Client client1(42, sockaddr_in());
	ft_irc::Client client2(84, sockaddr_in());

	client1.setNickname("client1");
	client2.setNickname("client2");
	LOG_TRACE("test client constructor: different clients")
	ASSERT_NEQ(client1.getFd(), client2.getFd())
	ASSERT_NEQ(client1.getNickname(), client2.getNickname())

	LOG_TRACE("test client constructor: asign operator")
	client1 = client2;
	ASSERT_EQ(client1.getFd(), client2.getFd())
	ASSERT_EQ(client1.getNickname(), client2.getNickname())

	LOG_TRACE("test client constructor: asign operator: deep copy")
	client1.setNickname("client1");
	ASSERT_NEQ(client1.getNickname(), client2.getNickname())

	LOG_TRACE("test client constructor: copy constructor")
	ft_irc::Client client3(client1);

	ASSERT_EQ(client1.getNickname(), client3.getNickname())

	client3.setNickname("client3");

	LOG_TRACE("test client constructor: copy constructor: deep copy")
	ASSERT_NEQ(client1.getNickname(), client3.getNickname())
}	// ChannelUT::test_constructor


void
ft_irc::ClientUT::test_setNickname(void)
{
	LOG_TRACE("test setNickname: empty string")
	ASSERT_THROW(ft_irc::Client::setNickname(""), std::invalid_argument)

	LOG_TRACE("test setNickname: invalid character: ' '")
	ASSERT_THROW(ft_irc::Client::setNickname("sm iro"), std::invalid_argument)

	LOG_TRACE("test setNickname: invalid character: ','")
	ASSERT_THROW(ft_irc::Client::setNickname("sm,iro"), std::invalid_argument)

	LOG_TRACE("test setNickname: invalid character: '*'")
	ASSERT_THROW(ft_irc::Client::setNickname("sm*iro"), std::invalid_argument)

	LOG_TRACE("test setNickname: invalid character: '?'")
	ASSERT_THROW(ft_irc::Client::setNickname("smiro?"), std::invalid_argument)

	LOG_TRACE("test setNickname: invalid character: '!'")
	ASSERT_THROW(ft_irc::Client::setNickname("smiro!"), std::invalid_argument)

	LOG_TRACE("test setNickname: invalid character: '@'")
	ASSERT_THROW(ft_irc::Client::setNickname("@smiro"), std::invalid_argument)

	LOG_TRACE("test setNickname: invalid character: '$'")
	ASSERT_THROW(ft_irc::Client::setNickname("$smiro$"), std::invalid_argument)

	LOG_TRACE("test setNickname: invalid character: '#'")
	ASSERT_THROW(ft_irc::Client::setNickname("#smiro"), std::invalid_argument)

	LOG_TRACE("test setNickname: invalid character: ':'")
	ASSERT_THROW(ft_irc::Client::setNickname(":smiro"), std::invalid_argument)

	LOG_TRACE("test setNickname: invalid character: '&'")
	ASSERT_THROW(ft_irc::Client::setNickname("&smiro"), std::invalid_argument)

	LOG_TRACE("test setNickname: invalid character: '.'")
	ASSERT_THROW(ft_irc::Client::setNickname(".s.miro"), std::invalid_argument)

	LOG_TRACE("test setNickname: valid parameter: smiro")
	ASSERT_NOTHROW(ft_irc::Client::setNickname("smiro"))
	ASSERT_EQ(ft_irc::Client::_nickname, "smiro")

	LOG_TRACE("test setNickname: valid parameter: marvin")
	ASSERT_NOTHROW(ft_irc::Client::setNickname("marvin"))
	ASSERT_EQ(ft_irc::Client::_nickname, "marvin");
}	// ClientUT::test_setNickname


void
ft_irc::ClientUT::test_setUsername(void)
{
	LOG_TRACE("test setUsername: empty string")
	ASSERT_THROW(ft_irc::Client::setUsername(""), std::invalid_argument)

	LOG_TRACE("test setUsername: valid parameter: smiro")
	ft_irc::Client::setUsername("smiro");
	ASSERT_EQ(ft_irc::Client::_username, "smiro")

	LOG_TRACE("test setUsername: valid parameter: marvin")
	ft_irc::Client::setUsername("marvin");
	ASSERT_EQ(ft_irc::Client::_username, "marvin");
}	// ClientUT::test_setUsername


void
ft_irc::ClientUT::test_setRealname(void)
{
	LOG_TRACE("test setRealname: empty string")
	ASSERT_THROW(ft_irc::Client::setRealname(""), std::invalid_argument)

	LOG_TRACE("test setRealname: valid parameter: 'Sebastian Miro'")
	ft_irc::Client::setRealname("Sebastian Miro");
	ASSERT_EQ(ft_irc::Client::_realname, "Sebastian Miro")

	LOG_TRACE("test setRealname: valid parameter: 'Marvin'")
	ft_irc::Client::setRealname("Marvin");
	ASSERT_EQ(ft_irc::Client::_realname, "Marvin");
}	// ClientUT::test_setRealname


void
ft_irc::ClientUT::test_setStatus(void)
{
	LOG_TRACE("test setStatus: 'PASSWORD'")
	ft_irc::Client::setStatus(Client::PASSWORD);
	ASSERT_EQ(ft_irc::Client::_status, Client::PASSWORD)

	LOG_TRACE("test setStatus: 'REGISTER'")
	ft_irc::Client::setStatus(Client::REGISTER);
	ASSERT_EQ(ft_irc::Client::_status, Client::REGISTER)

	LOG_TRACE("test setStatus: 'ONLINE'")
	ft_irc::Client::setStatus(Client::ONLINE);
	ASSERT_EQ(ft_irc::Client::_status, Client::ONLINE)

	LOG_TRACE("test setStatus: 'AWAY'")
	ft_irc::Client::setStatus(Client::AWAY);
	ASSERT_EQ(ft_irc::Client::_status, Client::AWAY)

	LOG_TRACE("test setStatus: 'DELETE'")
	ft_irc::Client::setStatus(Client::DELETE);
	ASSERT_EQ(ft_irc::Client::_status, Client::DELETE)
}	// ClientUT::test_setStatus


void
ft_irc::ClientUT::test_toggleMode(void)
{
	LOG_TRACE("test toggleMode: invalid parameter: larger number '127'")
	ASSERT_THROW(ft_irc::Client::toggleMode(127), ft_irc::Client::InvalidMode)

	LOG_TRACE("test toggleMode: invalid parameter: larger number '-10'")
	ASSERT_THROW(ft_irc::Client::toggleMode(-10), ft_irc::Client::InvalidMode)

	LOG_TRACE("test toggleMode: 'CL_NETWORK_OPER'")
	ASSERT_NOTHROW(ft_irc::Client::toggleMode(CL_NETWORK_OPER))
	ASSERT(ft_irc::Client::_mode & CL_NETWORK_OPER)

	LOG_TRACE("test toggleMode: 'CL_LOCAL_OPER'")
	ASSERT_NOTHROW(ft_irc::Client::toggleMode(CL_LOCAL_OPER))
	ASSERT(ft_irc::Client::_mode & (CL_LOCAL_OPER | CL_NETWORK_OPER))

	LOG_TRACE("test toggleMode: 'CL_INVISIBLE'")
	ASSERT_NOTHROW(ft_irc::Client::toggleMode(CL_INVISIBLE))
	ASSERT(ft_irc::Client::_mode & (CL_LOCAL_OPER | CL_NETWORK_OPER | CL_INVISIBLE))

	LOG_TRACE("test toggleMode: 'CL_WALLOPS'")
	ASSERT_NOTHROW(ft_irc::Client::toggleMode(CL_WALLOPS))
	ASSERT(ft_irc::Client::_mode & (CL_LOCAL_OPER | CL_NETWORK_OPER | CL_INVISIBLE | CL_WALLOPS))

	ASSERT_NOTHROW(ft_irc::Client::toggleMode(CL_WALLOPS))
	ASSERT(!(ft_irc::Client::_mode & (CL_WALLOPS)))

	ASSERT_NOTHROW(ft_irc::Client::toggleMode(CL_INVISIBLE))
	ASSERT(!(ft_irc::Client::_mode & (CL_INVISIBLE)))

	ASSERT_NOTHROW(ft_irc::Client::toggleMode(CL_LOCAL_OPER))
	ASSERT(!(ft_irc::Client::_mode & (CL_LOCAL_OPER)))

	ASSERT_NOTHROW(ft_irc::Client::toggleMode(CL_NETWORK_OPER))
	ASSERT(!(ft_irc::Client::_mode & (CL_NETWORK_OPER)))

	LOG_TRACE("test toggleMode: All at the same time")
	ASSERT_NOTHROW(ft_irc::Client::toggleMode(CL_LOCAL_OPER | CL_NETWORK_OPER | CL_INVISIBLE | CL_WALLOPS))
	ASSERT(ft_irc::Client::_mode & (CL_LOCAL_OPER | CL_NETWORK_OPER | CL_INVISIBLE | CL_WALLOPS))
	ASSERT_NOTHROW(ft_irc::Client::toggleMode(CL_LOCAL_OPER | CL_NETWORK_OPER | CL_INVISIBLE | CL_WALLOPS))
}	// ClientUT::test_toggleMode


void
ft_irc::ClientUT::test_getFd(void)
{
	LOG_TRACE("test getFd: '42'")
	ft_irc::Client::_fd = 42;
	ASSERT_EQ(ft_irc::Client::getFd(), 42)

	LOG_TRACE("test getFd: '84'")
	ft_irc::Client::_fd = 84;
	ASSERT_EQ(ft_irc::Client::getFd(), 84)
}	// ClientUT::test_getFd


void
ft_irc::ClientUT::test_getHostname(void)
{
	LOG_TRACE("test getHostname: 'localhost'")
	ft_irc::Client::_hostname = "localhost";
	ASSERT_EQ(ft_irc::Client::getHostname(), "localhost")

	LOG_TRACE("test getHostname: 'irc.com'")
	ft_irc::Client::_hostname = "irc.com";
	ASSERT_EQ(ft_irc::Client::getHostname(), "irc.com")
}	// ClientUT::test_getHostname


void
ft_irc::ClientUT::test_getNickname(void)
{
	LOG_TRACE("test getNickname: 'smiro'")
	ft_irc::Client::_nickname = "smiro";
	ASSERT_EQ(ft_irc::Client::getNickname(), "smiro")

	LOG_TRACE("test getNickname: 'marvin'")
	ft_irc::Client::_nickname = "marvin";
	ASSERT_EQ(ft_irc::Client::getNickname(), "marvin")
}	// ClientUT::test_getNickname


void
ft_irc::ClientUT::test_getUsername(void)
{
	LOG_TRACE("test getUsername: 'smiro'")
	ft_irc::Client::_username = "smiro";
	ASSERT_EQ(ft_irc::Client::getUsername(), "smiro")

	LOG_TRACE("test getUsername: 'marvin'")
	ft_irc::Client::_username = "marvin";
	ASSERT_EQ(ft_irc::Client::getUsername(), "marvin")
}	// ClientUT::test_getUsername


void
ft_irc::ClientUT::test_getRealname(void)
{
	LOG_TRACE("test getRealname: 'smiro'")
	ft_irc::Client::_realname = "smiro";
	ASSERT_EQ(ft_irc::Client::getRealname(), "smiro")

	LOG_TRACE("test getRealname: 'marvin'")
	ft_irc::Client::_realname = "marvin";
	ASSERT_EQ(ft_irc::Client::getRealname(), "marvin")
}	// ClientUT::test_getRealname


void
ft_irc::ClientUT::test_getStatus(void)
{
	LOG_TRACE("test getStatus: 'PASSWORD'")
	ft_irc::Client::_status = ft_irc::Client::PASSWORD;
	ASSERT_EQ(ft_irc::Client::getStatus(), ft_irc::Client::PASSWORD)

	LOG_TRACE("test getStatus: 'REGISTER'")
	ft_irc::Client::_status = ft_irc::Client::REGISTER;
	ASSERT_EQ(ft_irc::Client::getStatus(), ft_irc::Client::REGISTER)

	LOG_TRACE("test getStatus: 'ONLINE'")
	ft_irc::Client::_status = ft_irc::Client::ONLINE;
	ASSERT_EQ(ft_irc::Client::getStatus(), ft_irc::Client::ONLINE)

	LOG_TRACE("test getStatus: 'AWAY'")
	ft_irc::Client::_status = ft_irc::Client::AWAY;
	ASSERT_EQ(ft_irc::Client::getStatus(), ft_irc::Client::AWAY)

	LOG_TRACE("test getStatus: 'DELETE'")
	ft_irc::Client::_status = ft_irc::Client::DELETE;
	ASSERT_EQ(ft_irc::Client::getStatus(), ft_irc::Client::DELETE)
}	// ClientUT::test_getStatus


void
ft_irc::ClientUT::test_getMask(void)
{
	ft_irc::Client::_nickname = "smiro";
	ft_irc::Client::_username = "smiro";
	ft_irc::Client::_hostname = "localhost.com";

	LOG_TRACE("test getMastk: 'smiro!smiro@localhost.com'")
	ASSERT_EQ(ft_irc::Client::getMask(), "smiro!smiro@localhost.com")
}	// ClientUT::test_getMask
