#include <iostream>

#include "ChannelUT.hpp"
#include "ServerUT.hpp"
#include "ClientUT.hpp"

int
main() {
	ADD_TEST(ft_irc::ChannelUT)
	ADD_TEST(ft_irc::ClientUT)
	ADD_TEST(ft_irc::ServerUT)

	flt::TestCollection::instance().test();
	flt::TestCollection::instance().report(std::cout);

}
