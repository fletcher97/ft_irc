#if !defined(TESTRESULTS_HPP)
#define TESTRESULTS_HPP

#include <list>
#include <string>

#include "AssertError.hpp"

namespace flt
{

class TestResults
{
private:
	std::list< AssertError > _errors;

public:
	unsigned long _good;

public:
	TestResults(void);

	void error(flt::AssertError &e);
	void report(std::ostream &out, const std::string &name) const;
	void pass(void);
};	// class TestResults

}	// namespace flt

#endif // TESTRESULTS_HPP
