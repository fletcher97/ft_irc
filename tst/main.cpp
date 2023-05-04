#include <iostream>

#include "ChannelUT.hpp"
#include "ClientUT.hpp"
#include "CommunicationsUT.hpp"
#include "MatcherUT.hpp"
#include "ParserUT.hpp"
#include "ReplyUT.hpp"
#include "ServerUT.hpp"

using ft_irc::ChannelUT;
using ft_irc::ClientUT;
using ft_irc::CommunicationsUT;
using ft_irc::MatcherUT;
using ft_irc::ParserUT;
using ft_irc::ServerUT;
using ft_irc::ReplyUT;

int
main(void)
{
	ADD_TEST(ChannelUT)
	ADD_TEST(ClientUT)
	ADD_TEST(CommunicationsUT)
	ADD_TEST(MatcherUT)
	ADD_TEST(ParserUT)
	ADD_TEST(ServerUT)
	ADD_TEST(ReplyUT)

	flt::TestCollection::instance().test();
	flt::TestCollection::instance().report(std::cout);
}	// main
