#if !defined(PARSER_HPP)
#define PARSER_HPP

#include <list>
#include <map>
#include <string>

#include "codes.hpp"

namespace ft_irc
{

class Parser
{
public:
	typedef struct cmd_s
	{
		std::map< std::string, std::string > tags;
		ft_irc::commands cmd;
		std::list< std::string > args;
	} cmd_t;
protected:
	static void check_delimiter(std::string &msg);
	static void parse_tags(cmd_t *cmd, std::string &msg);
	static void check_source(std::string &msg);
	static void parse_command(cmd_t *cmd, std::string &msg);
	static void parse_arguments(cmd_t *cmd, std::string &msg);

public:
	static cmd_t* parse_msg(std::string &msg);
};	// class Parser

}	// namespace ft_irc

#endif // PARSER_HPP
