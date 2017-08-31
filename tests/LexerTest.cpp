#include <string>
#include "catch.hpp"
#include "../src/Lexer.h"

TEST_CASE("Lexer return correct elements", "[lexer]") {
    mustache::Lexer lex{"Text1 {{tag1}} Text2 {{Tag2}}"};
    const auto res = lex.getElements();

    REQUIRE(res.size() == 4);

    REQUIRE(res.at(0).getData() == "Text1 ");
    REQUIRE(res.at(1).getData() == "{{tag1}}");
    REQUIRE(res.at(2).getData() == " Text2 ");
    REQUIRE(res.at(3).getData() == "{{Tag2}}");
}

TEST_CASE("Lexer change delimiter", "[lexer]") {

    mustache::Lexer lex{"*{{default_tags}} {{=<% %>=}} * <% erb_style_tags %> <%={{ }}=%> * {{ default_tags_again }}"};
    const auto res = lex.getElements();

    lex.dump_elements();
    //REQUIRE(res.size() == 4);
}


