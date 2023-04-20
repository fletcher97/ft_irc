#include <iostream>

#include "ChannelUT.hpp"
#include "ClientUT.hpp"
#include "ServerUT.hpp"

using ft_irc::ChannelUT;
using ft_irc::ClientUT;
using ft_irc::ServerUT;

int
main(void)
{
	ADD_TEST(ChannelUT)
	ADD_TEST(ClientUT)
	ADD_TEST(ServerUT)

	flt::TestCollection::instance().test();
	flt::TestCollection::instance().report(std::cout);
}	// main
