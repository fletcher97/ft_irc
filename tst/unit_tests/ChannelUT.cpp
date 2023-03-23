#include "ChannelUT.hpp"

ChannelUT::ChannelUT(void) : flt::Testable<ChannelUT>("Channel"), Channel() {
	REGISTER(ChannelUT, test_42)
}

ChannelUT::~ChannelUT(void) {}

void
ChannelUT::test_42(void) {
	ASSERT(42)
}
