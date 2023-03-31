#include <iostream>

#include "ChannelUT.hpp"
#include "ServerUT.hpp"
#include "ClientUT.hpp"
#include "CommunicationsUT.hpp"

int
main(void) {

	ADD_TEST(ChannelUT)
	ADD_TEST(ClientUT)
	ADD_TEST(ServerUT)
	ADD_TEST(CommunicationsUT)

	flt::TestCollection::instance().test();
	flt::TestCollection::instance().report(std::cout);
}
