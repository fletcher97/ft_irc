#if !defined(TESTABLE_IPP)
#define TESTABLE_IPP

#include "AssertError.hpp"

#include "Testable.tpp"
#include "TestCollection.hpp"

template< typename T >
flt::Testable< T >::Testable(const std::string name) :
	_name(name)
{
	flt::TestCollection::instance().addTest(*this);
}


template< typename T >
flt::Testable< T >::Testable::~Testable(void)
{}

template< typename T >
void
flt::Testable< T >::run(void)
{
	for (typename std::vector< void (T::*)(void) >::iterator it = this->tests.begin(); it != this->tests.end(); it++) {
		try {
			(dynamic_cast< T* >(this)->*(*it))();
			this->_batch.pass();
		} catch (AssertError &e) {
			this->_batch.error(e);
		}
	}
}	// flt::Testable< T >::run


template< typename T >
void flt::Testable< T >::init(void) {}

template< typename T >
void flt::Testable< T >::term(void) {}


template< typename T >
void
flt::Testable< T >::report(std::ostream &out) const
{
	this->_batch.report(out, this->_name);
}	// flt::Testable< T >::report


template< typename T >
unsigned long
flt::Testable< T >::get_failed_count() const
{
	return this->_batch.get_failed_count();
}	// get_failed_count


template< typename T >
unsigned long
flt::Testable< T >::get_passed_count() const
{
	return this->_batch.get_passed_count();
}	// get_passed_count

#endif // TESTABLE_IPP
