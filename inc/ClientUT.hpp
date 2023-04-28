#if !defined(CLIENTUT_HPP)
#define CLIENTUT_HPP

#include "Client.hpp"

#include "Testable.tpp"

namespace ft_irc
{

class ClientUT :
	public flt::Testable< ClientUT >, ft_irc::Client
{
public:
	ClientUT(void);
	~ClientUT(void);

	void test_42(void);
};	// class ClientUT

}	// namespace ft_irc

#endif // CLIENTUT_HPP
