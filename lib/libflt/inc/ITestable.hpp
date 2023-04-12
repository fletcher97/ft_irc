#if !defined(ITESTABLE_HPP)
#define ITESTABLE_HPP

#include <ostream>

namespace flt
{

class ITestable
{
public:
	virtual void init(void) = 0;
	virtual void term(void) = 0;
	virtual void run(void) = 0;
	virtual void report(std::ostream &out) const = 0;
};	// class ITestable

}	// namespace flt

#endif // ITESTABLE_HPP
