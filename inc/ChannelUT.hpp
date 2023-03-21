#if !defined(CHANNELUT_HPP)
#define CHANNELUT_HPP

#include "Channel.hpp"

#include "Testable.tpp"

class ChannelUT : public flt::Testable<ChannelUT>, Channel
{
public:
	ChannelUT(void);
	~ChannelUT(void);

	void test_constructor(void);
};

#endif // CHANNELUT_HPP
