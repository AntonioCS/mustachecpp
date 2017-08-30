#define CATCH_CONFIG_MAIN

#include <string>
#include "catch.hpp"
#include "../src/Lexer.h"

std::string mustache_string
{
    "Text1 {{tag1}} Text2 {{Tag2}}"
};

TEST_CASE("Lexer return correct elements", "[lexer]") {
    mustache::Lexer lex{mustache_string};
    lex.dump_elements();
}


