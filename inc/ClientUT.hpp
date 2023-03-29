#if !defined(CLIENTUT_HPP)
#define CLIENTUT_HPP

#include "Client.hpp"

#include "Testable.tpp"

class ClientUT : public flt::Testable<ClientUT>, Client
{
public:
	ClientUT(void);
	~ClientUT(void);

	void test_setNickname(void);
	void test_setUsername(void);
	void test_setRealname(void);
	void test_setStatus(void);

	void test_getFd(void);
	void test_getAddress(void);
	void test_getHostname(void);
	void test_getNickname(void);
	void test_getUsername(void);
	void test_getRealname(void);
	void test_getStatus(void);
};

#endif // CLIENTUT_HPP
