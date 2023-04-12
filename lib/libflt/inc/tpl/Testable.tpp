#if !defined(TESTABLE_TPP)
#define TESTABLE_TPP

#include <string>
#include <vector>

#include "ITestable.hpp"
#include "TestResults.hpp"

#define REGISTER(CLS, X) {this->tests.push_back(&CLS::X);}

namespace flt
{

template< typename T >
class Testable :
	public ITestable
{
protected:
	const std::string _name;
	TestResults _batch;
	std::vector< void (T::*)(void) > tests;

public:
	Testable(const std::string name);
	virtual ~Testable(void);

	virtual void run(void);
	virtual void init(void);
	virtual void term(void);
	virtual void report(std::ostream &out) const;
};	// class Testable

}	// namespace flt

#include "Testable.ipp"

#endif // TESTABLE_TPP
