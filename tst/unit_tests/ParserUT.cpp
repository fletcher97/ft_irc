#include "Parser.hpp"

#include "ParserUT.hpp"

ParserUT::ParserUT(void) : flt::Testable<ParserUT>("Client") {}

ParserUT::~ParserUT(void) {}

void
ParserUT::test_delimiter_msg(void) {}

void
ParserUT::test_tag_presence(void) {}

void
ParserUT::test_tag_single_simple(void) {}

void
ParserUT::test_tag_multi_simple(void) {}

void
ParserUT::test_tag_single_kv(void) {}

void
ParserUT::test_tag_multi_kv(void) {}

void
ParserUT::test_source_presence(void) {}

void
ParserUT::test_command_valid(void) {}

void
ParserUT::test_command_invalid(void) {}

void
ParserUT::test_command_missing(void) {}

void
ParserUT::test_arguments_single(void) {}

void
ParserUT::test_arguments_multi(void) {}

void
ParserUT::test_arguments_missing(void) {}

void
ParserUT::test_arguments_colon(void) {}

void
ParserUT::test_arguments_multi_colon(void) {}
