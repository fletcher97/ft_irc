#if !defined(CHANNELUT_HPP)
#define CHANNELUT_HPP

#include "Channel.hpp"

#include "Testable.tpp"
namespace ft_irc
{

class ChannelUT : public flt::Testable<ChannelUT>, ft_irc::Channel
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
	void test_addClient(void);
	void test_banClient(void);
	void test_toggleMode(void);
	void test_inviteClient(void);

	void test_join(void);
};

} // namespace ft_irc

#endif // CHANNELUT_HPP
