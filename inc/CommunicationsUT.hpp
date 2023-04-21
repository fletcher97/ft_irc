#if !defined(COMMUNICATIONSUT_HPP)
#define COMMUNICATIONSUT_HPP

#include "Communications.hpp"

#include "Testable.tpp"

namespace ft_irc
{

class CommunicationsUT :
	public flt::Testable< CommunicationsUT >, ft_irc::Communications
{
public:
	CommunicationsUT(void);
	~CommunicationsUT(void);

	void test_getFd(void);

	void test_addPfd(void);

	class EmptyArgument :
		public std::invalid_argument
	{
public:
		EmptyArgument(std::string msg);
	};	// class EmptyArgument
};	// class CommunicationsUT

}	// namespace ft_irc

#endif // COMMUNICATIONSUT_HPP
