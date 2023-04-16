#include <iostream>

#include "TestResults.hpp"

flt::TestResults::TestResults(void) :
	_good(0)
{}

void
flt::TestResults::error(flt::AssertError &e)
{
	this->_errors.push_back(e);
}	// TestResults::error


void
flt::TestResults::report(std::ostream &out, const std::string &name) const
{
	out << this->_good << "/" << (this->_errors.size() + this->_good) << " tests passed for " << name << "." <<
		std::endl;
	for (std::list< flt::AssertError >::const_iterator it = this->_errors.begin();
		 it != this->_errors.end(); it++)
	{
		it->report(out);
	}
}	// TestResults::report


void
flt::TestResults::pass(void)
{
	this->_good++;
}	// TestResults::pass


unsigned long
flt::TestResults::get_failed_count() const
{
	return this->_errors.size();
}	// TestResults::get_failed_count


unsigned long
flt::TestResults::get_passed_count() const
{
	return this->_good;
}	// TestResults::get_passed_count
