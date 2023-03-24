#include "ServerUT.hpp"

ServerUT::ServerUT(void) : flt::Testable<ServerUT>("Server"), Server() {
	REGISTER(ServerUT, test_42)
}

ServerUT::~ServerUT(void) {}

void
ServerUT::test_42(void) {
	ASSERT(42)
}
