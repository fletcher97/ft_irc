#include "CommunicationsUT.hpp"

CommunicationsUT::CommunicationsUT(void) : flt::Testable<CommunicationsUT>("Communications"), Communications() {
	REGISTER(CommunicationsUT, test_getFd);
	REGISTER(CommunicationsUT, test_addPfd);
}

CommunicationsUT::~CommunicationsUT(void) {}

void CommunicationsUT::test_getFd(void) {
	this->_fd = 42;
	ASSERT_EQ(this->getFd(), 42)
	this->_fd = 84;
	ASSERT_EQ(this->getFd(), 84)
}

void CommunicationsUT::test_addPfd(void) {
	this->addPfd(42);
	ASSERT_EQ(this->_pfds[this->_pfds.size()-1], 42)
	this->addPfd(84);
	ASSERT_EQ(this->_pfds[this->_pfds.size()-1], 84)
}