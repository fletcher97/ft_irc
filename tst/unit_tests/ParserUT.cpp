#include "Parser.hpp"

#include "ParserUT.hpp"

ft_irc::ParserUT::ParserUT(void) : flt::Testable<ft_irc::ParserUT>("Parser") {}

ft_irc::ParserUT::~ParserUT(void) {}

void
ft_irc::ParserUT::test_delimiter_msg(void) {}

void
ft_irc::ParserUT::test_tag_presence(void) {}

void
ft_irc::ParserUT::test_tag_single_simple(void) {}

void
ft_irc::ParserUT::test_tag_multi_simple(void) {}

void
ft_irc::ParserUT::test_tag_single_kv(void) {}

void
ft_irc::ParserUT::test_tag_multi_kv(void) {}

void
ft_irc::ParserUT::test_source_presence(void) {}

void
ft_irc::ParserUT::test_command_valid(void) {}

void
ft_irc::ParserUT::test_command_invalid(void) {}

void
ft_irc::ParserUT::test_command_missing(void) {}

void
ft_irc::ParserUT::test_arguments_single(void) {}

void
ft_irc::ParserUT::test_arguments_multi(void) {}

void
ft_irc::ParserUT::test_arguments_missing(void) {}

void
ft_irc::ParserUT::test_arguments_colon(void) {}

void
ft_irc::ParserUT::test_arguments_multi_colon(void) {}
