#if !defined(SERVERUT_HPP)
#define SERVERUT_HPP

#include "Server.hpp"

#include "Testable.tpp"

namespace ft_irc
{

class ServerUT : public flt::Testable<ServerUT>, ft_irc::Server
{
public:
	ServerUT(void);
	~ServerUT(void);

	void test_42(void);
};

} // namespace ft_irc

#endif // SERVERUT_HPP
