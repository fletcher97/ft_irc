#include "ClientUT.hpp"

ClientUT::ClientUT(void) : flt::Testable<ClientUT>("Client"), Client() {
	REGISTER(ClientUT, test_42)
}

ClientUT::~ClientUT(void) {}

void ClientUT::test_42(void) {
	ASSERT(42)
}
