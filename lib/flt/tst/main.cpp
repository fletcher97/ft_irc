#include <iostream>

#include "Log.hpp"

#include "Testable.tpp"
#include "TestCollection.hpp"

class bad
{
public:
	bad(void) {};
	~bad(void) {};
	bool mytrue(void) {return true;};
	bool myfalse(void) {return false;};
	bool inteq(int x, int y) {return x == y;};
	bool intneq(int x, int y) {return x != y;};
	int getmsg(void) {return 404;};
	int small(int x) {if (x>9){throw std::invalid_argument("Number too big");}return x;};
};

class badtest : public flt::Testable<badtest>, bad {
public:
	badtest(void) : flt::Testable<badtest>("badtest"), bad(void) {
		REGISTER(badtest, test_true)
		REGISTER(badtest, test_false)
		REGISTER(badtest, test_msg)
	};

	void test_true(void) {ASSERT(mytrue(void))};
	void test_false(void) {ASSERT(myfalse(void) == false)};
	void test_msg(void) {ASSERT_EQ(getmsg(void), 44)};
};

class badtest2 : public flt::Testable<badtest2>, bad {
public:
	badtest2(void) : flt::Testable<badtest2>("badtest2"), bad() {
		REGISTER(badtest2, test_true)
		REGISTER(badtest2, test_false)
		REGISTER(badtest2, test_msg)
		REGISTER(badtest2, test_small)
		REGISTER(badtest2, test_small_throw1)
		REGISTER(badtest2, test_small_throw2)
	};

	void test_true(void) {ASSERT(mytrue(void))};
	void test_false(void) {ASSERT_EQ(myfalse(void), false)};
	void test_msg(void) {ASSERT_EQ(getmsg(void), 40)};
	void test_small(void) {ASSERT_EQ(small(1), 1)ASSERT_EQ(small(2), 2)ASSERT_EQ(small(1), 1)ASSERT_EQ(small(2), 2)ASSERT_EQ(small(1), 1)};
	void test_small_throw1(void) {ASSERT_THROW(small(9),std::invalid_argument)};
	void test_small_throw2(void) {ASSERT_THROW(small(10),std::invalid_argument)};
};

int
main(void)
{
	ADD_TEST(badtest)
	ADD_TEST(badtest2)

	flt::TestCollection::instance().test();
	flt::TestCollection::instance().report(std::cout);

	LOG_OPEN_FILE("test1.log")

	LOG_TRACE("Message abc ....")
	LOG_DEBUG("Message abc ....")
	LOG_INFO("Message abc ....")
	LOG_WARN("Message abc ....")
	LOG_ERROR("Message abc ....")
	LOG_FATAL("Message abc ....")

	LOG_CLOSE_FILE()
	return 0;
}
