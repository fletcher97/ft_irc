#if !defined(CHANNELUT_HPP)
#define CHANNELUT_HPP

#include "Channel.hpp"

#include "Testable.tpp"

namespace ft_irc
{

class ChannelUT :
	public flt::Testable< ChannelUT >, ft_irc::Channel
{
public:
	ChannelUT(void);
	~ChannelUT(void);

	void test_42(void);
};	// class ChannelUT

}	// namespace ft_irc

#endif // CHANNELUT_HPP
