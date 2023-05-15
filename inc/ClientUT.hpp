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

	void test_constructor(void);
	void test_setNickname(void);
	void test_setUsername(void);
	void test_setRealname(void);
	void test_setStatus(void);

	void test_getFd(void);
	void test_getHostname(void);
	void test_getNickname(void);
	void test_getUsername(void);
	void test_getRealname(void);
	void test_getStatus(void);
	void test_getMask(void);
	void test_add_mode(void);
	void test_remove_mode(void);
};	// class ClientUT

}	// namespace ft_irc

#endif // CLIENTUT_HPP
