#if !defined(CHANNELUT_HPP)
#define CHANNELUT_HPP

#include "Channel.hpp"

#include "Testable.tpp"

class ChannelUT : public flt::Testable<ChannelUT>, Channel
{
public:
	ChannelUT(void);
	~ChannelUT(void);

	void test_getName(void);
	void test_getTopic(void);
	void test_getKey(void);

	void test_setName(void);
	void test_setTopic(void);
	void test_setKey(void);
};

#endif // CHANNELUT_HPP
