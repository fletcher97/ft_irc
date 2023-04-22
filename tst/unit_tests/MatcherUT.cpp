#include "Log.hpp"

#include "MatcherUT.hpp"
#include "matcher.hpp"

ft_irc::MatcherUT::MatcherUT() :
	flt::Testable< ft_irc::MatcherUT >("Matcher")
{
	REGISTER(ft_irc::MatcherUT, test_matcher_empty_str)
	REGISTER(ft_irc::MatcherUT, test_matcher_star_single)
	REGISTER(ft_irc::MatcherUT, test_matcher_star_multi)
	REGISTER(ft_irc::MatcherUT, test_matcher_question_single)
	REGISTER(ft_irc::MatcherUT, test_matcher_question_multi)
	REGISTER(ft_irc::MatcherUT, test_matcher_esc)
	REGISTER(ft_irc::MatcherUT, test_matcher_mix)
	REGISTER(ft_irc::MatcherUT, test_vec_matcher_no_patterns)
	REGISTER(ft_irc::MatcherUT, test_vec_matcher_mix)
}	// MatcherUT::MatcherUT


ft_irc::MatcherUT::~MatcherUT() {}	// MatcherUT::~MatcherUT

void
ft_irc::MatcherUT::test_matcher_empty_str(void)
{
	ASSERT(ft_irc::match("", ""));
	ASSERT(!ft_irc::match("", "abc"));
	ASSERT(!ft_irc::match("abc", ""));
}	// MatcherUT::test_matcher_empty_str


void
ft_irc::MatcherUT::test_matcher_star_single(void)
{
	ASSERT(ft_irc::match("*", ""));
	ASSERT(ft_irc::match("*", "abc"));
	ASSERT(ft_irc::match("*a", "a"));
	ASSERT(ft_irc::match("*a", "aa"));
	ASSERT(ft_irc::match("*a", "abca"));
	ASSERT(!ft_irc::match("*a", "abc"));
	ASSERT(ft_irc::match("a*", "a"));
	ASSERT(ft_irc::match("a*", "aa"));
	ASSERT(ft_irc::match("a*", "abca"));
	ASSERT(!ft_irc::match("a*", "bca"));
	ASSERT(!ft_irc::match("a*a", "a"));
	ASSERT(ft_irc::match("a*a", "aa"));
	ASSERT(ft_irc::match("a*a", "abca"));
	ASSERT(!ft_irc::match("a*a", "bca"));
}	// MatcherUT::test_matcher_star_single


void
ft_irc::MatcherUT::test_matcher_star_multi(void)
{
	ASSERT(ft_irc::match("**", ""));
	ASSERT(ft_irc::match("**", "a"));
	ASSERT(ft_irc::match("**", "ab"));
	ASSERT(ft_irc::match("**", "abc"));
	ASSERT(ft_irc::match("*****", ""));
	ASSERT(ft_irc::match("*****", "abcdefghijklmnopqrstuvwxyz"));
	ASSERT(!ft_irc::match("*a*", "bcd"));
	ASSERT(ft_irc::match("*a*", "abc"));
	ASSERT(ft_irc::match("*a*", "bca"));
	ASSERT(ft_irc::match("*a*", "bab"));
	ASSERT(ft_irc::match("*a*", "baba"));
	ASSERT(ft_irc::match("*1*", "a1"));
	ASSERT(!ft_irc::match("*1*", "x2"));
	ASSERT(!ft_irc::match("*1*2", "o2oe"));
	ASSERT(ft_irc::match("*1*2*", "q1w2erty"));
}	// MatcherUT::test_matcher_star_multi


void
ft_irc::MatcherUT::test_matcher_question_single(void)
{
	ASSERT(!ft_irc::match("?", ""));
	ASSERT(!ft_irc::match("?", "abc"));
	ASSERT(ft_irc::match("?", "a"));
	ASSERT(!ft_irc::match("?a", "a"));
	ASSERT(ft_irc::match("?a", "aa"));
	ASSERT(!ft_irc::match("?a", "aaa"));
	ASSERT(ft_irc::match("?a", "ba"));
	ASSERT(!ft_irc::match("a?", "a"));
	ASSERT(ft_irc::match("a?", "aa"));
	ASSERT(!ft_irc::match("a?", "abca"));
	ASSERT(!ft_irc::match("a?a", "a"));
	ASSERT(!ft_irc::match("a?a", "aa"));
	ASSERT(ft_irc::match("a?a", "aaa"));
	ASSERT(ft_irc::match("a?a", "aca"));
	ASSERT(!ft_irc::match("a?a", "acaa"));
}	// MatcherUT::test_matcher_question_single


void
ft_irc::MatcherUT::test_matcher_question_multi(void)
{
	ASSERT(!ft_irc::match("??", ""));
	ASSERT(!ft_irc::match("??", "a"));
	ASSERT(ft_irc::match("??", "ab"));
	ASSERT(!ft_irc::match("??", "abc"));
	ASSERT(!ft_irc::match("?a?", "bcd"));
	ASSERT(ft_irc::match("?a?", "bad"));
	ASSERT(!ft_irc::match("?a?", "abc"));
	ASSERT(!ft_irc::match("?a?", "bca"));
	ASSERT(ft_irc::match("?a?", "bab"));
	ASSERT(ft_irc::match("?a?a", "baba"));
	ASSERT(ft_irc::match("1?1?", "1a1a"));
	ASSERT(!ft_irc::match("?1?2", "o2oe"));
	ASSERT(ft_irc::match("?1?2????", "q1w2erty"));
}	// MatcherUT::test_matcher_question_multi


void
ft_irc::MatcherUT::test_matcher_esc(void)
{
	ASSERT(!ft_irc::match("a\\*a", "aa"))
	ASSERT(ft_irc::match("\\*", "*"))
	ASSERT(ft_irc::match("a\\*a", "a*a"))
	ASSERT(!ft_irc::match("\\*", "a"))
	ASSERT(!ft_irc::match("a\\a", "a\\a"))
	ASSERT(ft_irc::match("a\\a", "aa"))
}	// MatcherUT::test_matcher_mix


void
ft_irc::MatcherUT::test_matcher_mix(void)
{
	ASSERT(!ft_irc::match("a?*a", "aa"))
	ASSERT(ft_irc::match("a?*a", "aaa"))
	ASSERT(!ft_irc::match("a*?a", "aa"))
	ASSERT(ft_irc::match("a*?a", "aaa"))
}	// MatcherUT::test_matcher_mix


void
ft_irc::MatcherUT::test_vec_matcher_no_patterns(void)
{
	std::vector< std::string > patterns;

	patterns = std::vector< std::string >();

	ASSERT(!ft_irc::match(patterns, ""));
	ASSERT(!ft_irc::match(patterns, "asd"));
}	// test_vec_matcher_empty_pattern


void
ft_irc::MatcherUT::test_vec_matcher_mix(void)
{
	std::vector< std::string > patterns;

	patterns = std::vector< std::string >();
	patterns.push_back("*john*");
	patterns.push_back("Local*");
	patterns.push_back("*asd");
	patterns.push_back("Literal");

	ASSERT(!ft_irc::match(patterns, ""));
	ASSERT(ft_irc::match(patterns, "Literal"));
	ASSERT(ft_irc::match(patterns, "asd"));
	ASSERT(ft_irc::match(patterns, "Local bakery"));
	ASSERT(!ft_irc::match(patterns, "local bakery"));
	ASSERT(ft_irc::match(patterns, "local bakery asd"));
	ASSERT(ft_irc::match(patterns, "Here's johnnny "));
	ASSERT(!ft_irc::match(patterns, "Here's jhonnny "));
}	// test_vec_matcher_empty_pattern
