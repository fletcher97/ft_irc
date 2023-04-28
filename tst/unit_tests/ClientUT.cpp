#include "ClientUT.hpp"

ft_irc::ClientUT::ClientUT(void) :
	flt::Testable< ft_irc::ClientUT >("Client"),
	ft_irc::Client()
{
	REGISTER(ft_irc::ClientUT, test_42)
}


ft_irc::ClientUT::~ClientUT(void) {}

void
ft_irc::ClientUT::test_42(void)
{
	ASSERT(42)
}	// ClientUT::test_42
