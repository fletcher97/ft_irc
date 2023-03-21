#include "ClientUT.hpp"

ClientUT::ClientUT(void) : flt::Testable<ClientUT>("Client"), Client("test client", "address", "user") {
	REGISTER(ClientUT, test_constructor)
}

ClientUT::~ClientUT(void) {}

void
ClientUT::test_constructor(void) {
	ASSERT_THROW(Client("", "", ""), std::invalid_argument)
}
