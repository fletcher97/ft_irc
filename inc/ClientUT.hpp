#if !defined(CLIENTUT_HPP)
#define CLIENTUT_HPP

#include "Client.hpp"

#include "Testable.tpp"

class ClientUT : public flt::Testable<ClientUT>, Client
{
public:
	ClientUT(void);
	~ClientUT(void);

	void test_constructor(void);
};

#endif // CLIENTUT_HPP
