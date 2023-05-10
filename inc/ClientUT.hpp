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

	void test_add_mode(void);
	void test_remove_mode(void);
};	// class ClientUT

}	// namespace ft_irc

#endif // CLIENTUT_HPP
