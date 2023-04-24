#if !defined(MATCHER_HPP)
#define MATCHER_HPP

#include <string>
#include <vector>

namespace ft_irc
{

bool match(const std::string &pattern, const std::string &value);
bool match(const std::vector< std::string > &pattern, const std::string &values);

}	// namespace ft_irc

#endif // MATCHER_HPP
