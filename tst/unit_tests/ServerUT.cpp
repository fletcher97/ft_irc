#include "ServerUT.hpp"

ft_irc::ServerUT::ServerUT(void) :
	flt::Testable< ft_irc::ServerUT >("Server"),
	ft_irc::Server()
{
	REGISTER(ft_irc::ServerUT, test_42)
}


ft_irc::ServerUT::~ServerUT(void) {}

void
ft_irc::ServerUT::test_42(void)
{
	ASSERT(42)
}	// ServerUT::test_42
