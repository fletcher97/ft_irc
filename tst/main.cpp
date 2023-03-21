#include <iostream>

#include "ChannelUT.hpp"
#include "ServerUT.hpp"
#include "ClientUT.hpp"

int
main() {
	ADD_TEST(ChannelUT)
	ADD_TEST(ClientUT)
	ADD_TEST(ServerUT)

	flt::TestCollection::instance().test();
	flt::TestCollection::instance().report(std::cout);

}
