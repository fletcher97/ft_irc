#if !defined(REPLYUT_HPP)
#define REPLYUT_HPP

#include "Testable.tpp"

namespace ft_irc
{

class ReplyUT :
	public flt::Testable< ft_irc::ReplyUT >
{
public:
	ReplyUT();
	~ReplyUT();

	void replies_tests(void);
};	// class ReplyUT

}	// namespace ft_irc

#endif // REPLYUT_HPP
