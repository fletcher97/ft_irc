#if !defined(COMMUNICATIONSUT_HPP)
#define COMMUNICATIONSUT_HPP

#include "Communications.hpp"

#include "Testable.tpp"

class CommunicationsUT : public flt::Testable<CommunicationsUT>, Communications
{
public:
	CommunicationsUT(void);
	~CommunicationsUT(void);

	void test_getFd(void);

	void test_addPfd(void);
	
	class EmptyArgument : public std::invalid_argument
	{
	public:
			EmptyArgument(std::string msg);
	};
};

#endif // COMMUNICATIONSUT_HPP
