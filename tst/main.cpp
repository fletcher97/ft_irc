#include <iostream>

#include "ChannelUT.hpp"
#include "CommunicationsUT.hpp"
#include "ClientUT.hpp"
#include "ParserUT.hpp"
#include "ServerUT.hpp"

using ft_irc::CommunicationsUT;
using ft_irc::ChannelUT;
using ft_irc::ClientUT;
using ft_irc::ServerUT;
using ft_irc::ParserUT;

int
main(void)
{
	ADD_TEST(ChannelUT)
	ADD_TEST(ClientUT)
	ADD_TEST(ServerUT)
	ADD_TEST(ParserUT)
	ADD_TEST(CommunicationsUT)

	flt::TestCollection::instance().test();
	flt::TestCollection::instance().report(std::cout);
}	// main
