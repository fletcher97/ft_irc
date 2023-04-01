#if !defined(SERVERUT_HPP)
#define SERVERUT_HPP

#include "Server.hpp"

#include "Testable.tpp"

class ServerUT : public flt::Testable<ServerUT>, Server
{
public:
	ServerUT(void);
	~ServerUT(void);

	void test_getClient_fd(void);
	void test_getClient_nick(void);
};

#endif // SERVERUT_HPP
