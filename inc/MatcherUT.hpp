#if !defined(MATCHERUT_HPP)
#define MATCHERUT_HPP

#include "Testable.tpp"

namespace ft_irc
{

class MatcherUT :
	public flt::Testable< ft_irc::MatcherUT >
{
public:
	MatcherUT();
	~MatcherUT();

	void test_matcher_empty_str(void);
	void test_matcher_star_single(void);
	void test_matcher_star_multi(void);
	void test_matcher_question_single(void);
	void test_matcher_question_multi(void);
	void test_matcher_esc(void);
	void test_matcher_mix(void);

	void test_vec_matcher_no_patterns(void);
	void test_vec_matcher_mix(void);
};	// class MatcherUT

}	// namespace ft_irc

#endif // MATCHERUT_HPP
