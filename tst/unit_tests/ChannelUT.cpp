#include "ChannelUT.hpp"

ft_irc::ChannelUT::ChannelUT(void) :
	flt::Testable< ft_irc::ChannelUT >("Channel"),
	ft_irc::Channel()
{
	REGISTER(ChannelUT, test_42)
}


ft_irc::ChannelUT::~ChannelUT(void) {}

void
ft_irc::ChannelUT::test_42(void)
{
	ASSERT(42)
}	// ChannelUT::test_42
