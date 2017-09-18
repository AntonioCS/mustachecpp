#include <string>
#include "catch.hpp"
#include "../src/Lexer.h"

TEST_CASE("Lexer return correct elements", "[lexer]") {
    mustache::Lexer lex{"Text1 {{tag1}} Text2 {{Tag2}}"};
    const auto res = lex.getElements();

    REQUIRE(res.size() == 4);

    REQUIRE(res.at(0).getType() == mustache::LexerElementType::TEXT);
    REQUIRE(res.at(0).getData() == "Text1 ");

    REQUIRE(res.at(1).getType() == mustache::LexerElementType::TAG);
    REQUIRE(res.at(1).getData() == "tag1");

    REQUIRE(res.at(2).getType() == mustache::LexerElementType::TEXT);
    REQUIRE(res.at(2).getData() == " Text2 ");

    REQUIRE(res.at(3).getType() == mustache::LexerElementType::TAG);
    REQUIRE(res.at(3).getData() == "Tag2");
}

TEST_CASE("Tag start", "[lexer]") {
    mustache::Lexer lex{"{{tag0}} Text1 {{tag1}} Text2 {{Tag2}}"};
    const auto res = lex.getElements();

    REQUIRE(res.size() == 5);

    REQUIRE(res.at(0).getType() == mustache::LexerElementType::TAG);
    REQUIRE(res.at(0).getData() == "tag0");
    
    REQUIRE(res.at(1).getType() == mustache::LexerElementType::TEXT);
    REQUIRE(res.at(1).getData() == " Text1 ");
    
    REQUIRE(res.at(2).getType() == mustache::LexerElementType::TAG);
    REQUIRE(res.at(2).getData() == "tag1");
    
    REQUIRE(res.at(3).getType() == mustache::LexerElementType::TEXT);
    REQUIRE(res.at(3).getData() == " Text2 ");
    
    REQUIRE(res.at(4).getType() == mustache::LexerElementType::TAG);
    REQUIRE(res.at(4).getData() == "Tag2");

}

TEST_CASE("No tags", "[lexer]") {
    std::string text{"Hello World!"};
    mustache::Lexer lex{text};
    const auto res = lex.getElements();

    REQUIRE(res.size() == 1);
    REQUIRE(res.at(0).getData() == text);
    REQUIRE(res.at(0).getType() == mustache::LexerElementType::TEXT);
}


TEST_CASE("All tags", "[lexer]") {
    mustache::Lexer lex{"{{tag1}}{{tag2}}{{tag3}}{{tag4}}"};
    const auto res = lex.getElements();

    REQUIRE(res.size() == 4);

    REQUIRE(res.at(0).getType() == mustache::LexerElementType::TAG);
    REQUIRE(res.at(0).getData() == "tag1");

    REQUIRE(res.at(1).getType() == mustache::LexerElementType::TAG);
    REQUIRE(res.at(1).getData() == "tag2");

    REQUIRE(res.at(2).getType() == mustache::LexerElementType::TAG);
    REQUIRE(res.at(2).getData() == "tag3");
    
    REQUIRE(res.at(3).getType() == mustache::LexerElementType::TAG);
    REQUIRE(res.at(3).getData() == "tag4");
}

TEST_CASE("Unfinished tag Exception", "[lexer]") {
    REQUIRE_THROWS_WITH(
            [] {
                mustache::Lexer lex{"{{tag1"};
            }(),
    "Mustache-Lexer - Unfinished tag" //Exception message
    );
}

TEST_CASE("No spaces inside tags", "[lexer]") {
    mustache::Lexer lex{"{{ tag1 }}{{      tag2   }}{{                tag3  }}{{                            tag4        }}"};
    const auto res = lex.getElements();

    REQUIRE(res.size() == 4);

    REQUIRE(res.at(0).getType() == mustache::LexerElementType::TAG);
    REQUIRE(res.at(0).getData() == "tag1");

    REQUIRE(res.at(1).getType() == mustache::LexerElementType::TAG);
    REQUIRE(res.at(1).getData() == "tag2");

    REQUIRE(res.at(2).getType() == mustache::LexerElementType::TAG);
    REQUIRE(res.at(2).getData() == "tag3");

    REQUIRE(res.at(3).getType() == mustache::LexerElementType::TAG);
    REQUIRE(res.at(3).getData() == "tag4");
}


/*
TEST_CASE("Lexer change delimiter", "[lexer]") {

    mustache::Lexer lex{"*{{default_tags}} {{=<% %>=}} * <% erb_style_tags %> <%={{ }}=%> * {{ default_tags_again }}"};
    const auto res = lex.getElements();

    lex.dump_elements();
    //REQUIRE(res.size() == 4);
}*/


