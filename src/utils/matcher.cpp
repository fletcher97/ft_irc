#include "matcher.hpp"
#include "Log.hpp"

static bool priv_match(const std::string &pattern, const std::string &value);

static bool
matchStar(const std::string &pattern, const std::string &value)
{
	std::string tmp;
	std::string sub_pattern;

	if (pattern[1] == '*') {
		LOG_TRACE("Multi star skip")

		return priv_match(pattern.substr(1, pattern.size()), value);
	}
	sub_pattern = pattern.substr(1, pattern.find_first_of("*?\\", 1) - 1);
	LOG_TRACE("Matching sub pattern \"" << sub_pattern << "\"")
	tmp = value;
	while (tmp.find(sub_pattern) != tmp.npos) {
		tmp = tmp.substr(tmp.find(sub_pattern) + sub_pattern.size(), tmp.size());
		LOG_TRACE("Trying matching pattern \"" << pattern.substr(sub_pattern.size() + 1,
			pattern.size()) << "\" with value \"" << tmp << "\"")
		if (priv_match(pattern.substr(sub_pattern.size() + 1, pattern.size()), tmp)) {
			return true;
		}
		if (!tmp.size()) {
			LOG_TRACE("No match found")

			return false;
		}
		if (!sub_pattern.size()) {
			tmp = tmp.substr(1, tmp.size());
		}
	}

	LOG_TRACE("No match found")

	return false;
}	// matchStar


static bool
priv_match(const std::string &pattern, const std::string &value)
{
	std::string sub_pattern;

	if (!pattern.size() && !value.size()) {
		LOG_TRACE("Match found")

		return true;
	}
	if ((pattern.size() == 1) && (pattern[0] == '*')) {
		LOG_TRACE("Match found")

		return true;
	}
	if (!pattern.size() && value.size()) {
		LOG_TRACE("No match found")

		return false;
	}
	if (pattern[0] == '\\') {
		if (!value.size() || (pattern[1] != value[0])) {
			LOG_TRACE("No match found")

			return false;
		}
		LOG_TRACE("Escaping " << pattern[1])

		return priv_match(pattern.substr(2, pattern.size()), value.substr(1, value.size()));
	}
	if (pattern[0] == '?') {
		if (!value.size()) {
			LOG_TRACE("No match found")

			return false;
		}

		return priv_match(pattern.substr(1, pattern.size()), value.substr(1, value.size()));
	}

	if (pattern[0] == '*') {
		return matchStar(pattern, value);
	}

	sub_pattern = pattern.substr(0, pattern.find_first_of("*?\\", 1));
	if (value.find(sub_pattern) == 0) {
		return priv_match(pattern.substr(sub_pattern.size(), pattern.size()),
				value.substr(sub_pattern.size(), value.size()));
	}

	LOG_TRACE("No match found")

	return false;
}	// match


bool
ft_irc::match(const std::string &pattern, const std::string &value)
{
	LOG_DEBUG("Matching pattern \"" << pattern << "\" with value \"" << value << "\"")

	return priv_match(pattern, value);
}	// ft_irc::match


bool
ft_irc::match(const std::vector< std::string > &pattern, const std::string &value)
{
	std::vector< std::string > ret;

	LOG_DEBUG("Looking for value \"" << value << "\" in pattern list")
	for (std::vector< std::string >::const_iterator it = pattern.begin(); it != pattern.end(); it++) {
		if (ft_irc::match(*it, value)) {
			return true;
		}
	}

	return false;
}	// ft_irc::matchList
