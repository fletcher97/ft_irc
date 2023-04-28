#include <netinet/in.h>

#include "ClientUT.hpp"

ft_irc::ClientUT::ClientUT(void) :
	flt::Testable< ft_irc::ClientUT >("Client"),
	ft_irc::Client()
{
	REGISTER(ft_irc::ClientUT, test_add_mode)
	REGISTER(ft_irc::ClientUT, test_remove_mode)
}


ft_irc::ClientUT::~ClientUT(void) {}

void
ft_irc::ClientUT::test_add_mode(void)
{
	struct sockaddr_in clientSocket;
	ft_irc::Client c = ft_irc::Client(0, clientSocket);
	bool changed;

	ASSERT_EQ(c.getMode(), 0);

	ASSERT_NOTHROW(changed = c.addMode(CL_INVISIBLE))
	ASSERT(changed)
	ASSERT_EQ(c.getMode(), CL_INVISIBLE);

	ASSERT_NOTHROW(changed = c.addMode(CL_INVISIBLE))
	ASSERT(!changed)
	ASSERT_EQ(c.getMode(), CL_INVISIBLE);

	ASSERT_NOTHROW(changed = c.addMode(CL_LOCALOP))
	ASSERT(changed)
	ASSERT_EQ(c.getMode(), (CL_INVISIBLE | CL_LOCALOP));

	ASSERT_NOTHROW(changed = c.addMode(CL_LOCALOP))
	ASSERT(!changed)
	ASSERT_EQ(c.getMode(), (CL_INVISIBLE | CL_LOCALOP));

	ASSERT_NOTHROW(changed = c.addMode(CL_OP))
	ASSERT(changed)
	ASSERT_EQ(c.getMode(), (CL_INVISIBLE | CL_LOCALOP | CL_OP));

	ASSERT_NOTHROW(changed = c.addMode(CL_INVISIBLE))
	ASSERT(!changed)
	ASSERT_EQ(c.getMode(), (CL_INVISIBLE | CL_LOCALOP | CL_OP));

	ASSERT_NOTHROW(changed = c.addMode(CL_WALLOPS))
	ASSERT(changed)
	ASSERT_EQ(c.getMode(), (CL_INVISIBLE | CL_LOCALOP | CL_OP | CL_WALLOPS));

	ASSERT_NOTHROW(changed = c.addMode(CL_WALLOPS))
	ASSERT(!changed)
	ASSERT_EQ(c.getMode(), (CL_INVISIBLE | CL_LOCALOP | CL_OP | CL_WALLOPS));
}	// ClientUT::test_add_mode


void
ft_irc::ClientUT::test_remove_mode(void)
{
	struct sockaddr_in clientSocket;
	ft_irc::Client c = ft_irc::Client(0, clientSocket);
	bool changed;

	ASSERT_EQ(c.getMode(), 0);

	ASSERT_NOTHROW(c.addMode(CL_INVISIBLE))
	ASSERT_NOTHROW(c.addMode(CL_LOCALOP))
	ASSERT_NOTHROW(c.addMode(CL_OP))
	ASSERT_NOTHROW(c.addMode(CL_WALLOPS))
	ASSERT_EQ(c.getMode(), (CL_INVISIBLE | CL_LOCALOP | CL_OP | CL_WALLOPS));

	ASSERT_NOTHROW(changed = c.removeMode(CL_WALLOPS))
	ASSERT(changed)
	ASSERT_EQ(c.getMode(), (CL_INVISIBLE | CL_LOCALOP | CL_OP));

	ASSERT_NOTHROW(changed = c.removeMode(CL_WALLOPS))
	ASSERT(!changed)
	ASSERT_EQ(c.getMode(), (CL_INVISIBLE | CL_LOCALOP | CL_OP));

	ASSERT_NOTHROW(changed = c.removeMode(CL_OP))
	ASSERT(changed)
	ASSERT_EQ(c.getMode(), (CL_INVISIBLE | CL_LOCALOP));

	ASSERT_NOTHROW(changed = c.removeMode(CL_LOCALOP))
	ASSERT(changed)
	ASSERT_EQ(c.getMode(), CL_INVISIBLE);

	ASSERT_NOTHROW(changed = c.removeMode(CL_INVISIBLE))
	ASSERT(changed)
	ASSERT_EQ(c.getMode(), 0);
}	// ClientUT::test_remove_mode
