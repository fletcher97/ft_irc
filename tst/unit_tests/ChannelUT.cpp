#include "ChannelUT.hpp"

ChannelUT::ChannelUT(void) : flt::Testable<ChannelUT>("Channel"), Channel() {
	REGISTER(ChannelUT, test_setName);
	REGISTER(ChannelUT, test_setTopic);
	REGISTER(ChannelUT, test_setKey);

	REGISTER(ChannelUT, test_getName);
	REGISTER(ChannelUT, test_getTopic);
	REGISTER(ChannelUT, test_getKey);
}

ChannelUT::~ChannelUT(void) {}

void ClientUT::test_setName(void) {
	ASSERT_THROW(this->setName(""), std::invalid_argument)
	this->setName("gemartin");
	ASSERT_EQ(this->_name, "gemartin")
	this->setName("marvin");
	ASSERT_EQ(this->_name, "marvin");
}

void ClientUT::test_setTopic(void) {
	ASSERT_THROW(this->setTopic(""), std::invalid_argument)
	this->setTopic("gemartin");
	ASSERT_EQ(this->_topic, "gemartin")
	this->setTopic("marvin");
	ASSERT_EQ(this->_topic, "marvin");
}

void ClientUT::test_setKey(void) {
	ASSERT_THROW(this->setKey(""), std::invalid_argument)
	this->setKey("gemartin");
	ASSERT_EQ(this->_key, "gemartin")
	this->setKey("marvin");
	ASSERT_EQ(this->_key, "marvin");
}

void ClientUT::test_getName(void) {
	this->_name = "gemartin";
	ASSERT_EQ(this->getName(), "gemartin")
	this->_name = "marvin";
	ASSERT_EQ(this->getName(), "marvin")
}

void ClientUT::test_getTopic(void) {
	this->_topic = "gemartin";
	ASSERT_EQ(this->getTopic(), "gemartin")
	this->_topic = "marvin";
	ASSERT_EQ(this->getTopic(), "marvin")
}

void ClientUT::test_getKey(void) {
	this->_key = "gemartin";
	ASSERT_EQ(this->getKey(), "gemartin")
	this->_key = "marvin";
	ASSERT_EQ(this->getKey(), "marvin")
}