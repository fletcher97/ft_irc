#include <iostream>

#include "TestCollection.hpp"

flt::TestCollection::TestCollection(void) {}

flt::TestCollection::~TestCollection(void) {}

flt::TestCollection&
flt::TestCollection::instance(void)
{
	static flt::TestCollection instance;

	return instance;
}	// TestCollection::instance


void
flt::TestCollection::addTest(flt::ITestable &t)
{
	this->_tests.push_back(&t);
}	// TestCollection::addTest


void
flt::TestCollection::test(void)
{
	for (std::list< flt::ITestable* >::iterator it = this->_tests.begin(); it != this->_tests.end(); it++) {
		(*it)->init();
		(*it)->run();
		(*it)->term();
		this->_count++;
		this->_failed = (*it)->get_failed_count();
		this->_passed = (*it)->get_passed_count();
	}
}	// TestCollection::test


void
flt::TestCollection::report(std::ostream &out) const
{
	std::cout << "Ran " << this->_count << " groups." << std::endl;
	for (std::list< flt::ITestable* >::const_iterator it = this->_tests.begin(); it != this->_tests.end(); it++) {
		(*it)->report(out);
	}
}	// TestCollection::report


unsigned long
flt::TestCollection::get_failed_count() const
{
	return this->_failed;
}	// TestCollection::get_failed_count


unsigned long
flt::TestCollection::get_passed_count() const
{
	return this->_passed;
}	// TestCollection::get_passed_count
