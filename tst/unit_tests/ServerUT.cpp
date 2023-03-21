#include "ServerUT.hpp"

ServerUT::ServerUT(void) : flt::Testable<ServerUT>("Server"), Server("test srv") {
	REGISTER(ServerUT, test_constructor)
}

ServerUT::~ServerUT(void) {}

void
ServerUT::test_constructor(void) {
	ASSERT_THROW(Server(""), std::invalid_argument)
}
