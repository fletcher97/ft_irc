#if !defined(SERVERUT_HPP)
#define SERVERUT_HPP

#include "Server.hpp"

#include "Testable.tpp"

namespace ft_irc
{

class ServerUT :
	public flt::Testable< ServerUT >, ft_irc::Server
{
public:
	ServerUT(void);
	~ServerUT(void);

	void test_getClient_fd(void);
	void test_getClient_nick(void);
};	// class ServerUT

}	// namespace ft_irc


#endif // SERVERUT_HPP
