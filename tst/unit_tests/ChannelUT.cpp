#include "ChannelUT.hpp"

ChannelUT::ChannelUT(void) : flt::Testable<ChannelUT>("Channel"), Channel("test chn") {
	REGISTER(ChannelUT, test_constructor)
}

ChannelUT::~ChannelUT(void) {}

void
ChannelUT::test_constructor(void) {
	ASSERT_THROW(Channel(""), std::invalid_argument)
}
