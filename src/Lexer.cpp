#include "Lexer.h"
#include <iostream>

namespace mustache {

    Lexer::Lexer(const std::string &str) {
        lex(str);
    }

    Lexer::~Lexer() {
    }

    void Lexer::dump_elements() const {

        for (const auto &i : m_elements) {
            std::cout << " - " << i.getData() << '\n';
        }
    }

    std::vector<LexerElement> Lexer::getElements() const noexcept {
        return m_elements;
    }

    const char Lexer::getChar() const noexcept {
        try {
            return m_text.at(m_position);
        } catch (const std::out_of_range& oor) {
            return EOF;
        }
    }

    bool Lexer::isTagPart(std::string part) noexcept {
        mark_position();
        bool is_tag = false;

        for (const char &s : part) {
            if (s == getChar()) {
                charNext();
                is_tag = true;
                continue;
            }

            is_tag = false;
            break;
        }

        if (is_tag == false) {
            reset_position_to_marker();
        }
        return is_tag;
    }

    void Lexer::lex(const std::string &str) {
        if (str.size() <= min_string_len) {
            throw "String too small";
        }

        m_text = str;
        m_size = str.size();

        lex();
    }

    void Lexer::lex() {
        Mode mode = Mode::TEXT;
        size_t pos = 0;

        while (getChar() != EOF) {
            switch (mode) {
                case Mode::TEXT:
                    if (isTagStart()) {
                        //It will be zero if a tag is the first element
                        size_t len = m_position - m_TagEnd.length() - pos;
                        if (len > 0) {
                            addElementFromText(pos, len);
                            //m_elements.emplace_back(m_text.substr(pos, len));
                            pos = m_position - m_TagEnd.length();
                        }

                        mode = Mode::TAG_END_SEARCH;
                    }
                    break;

                case Mode::TAG_END_SEARCH:
                    if (isTagEnd()) {
                        m_total_tags++;
                        addElementFromText(pos, m_position - pos, LexerElementTypes::TAG);
                        //m_elements.emplace_back(m_text.substr(pos, m_position - pos), LexerElementTypes::TAG);

                        pos = m_position;
                        mode = Mode::TEXT;
                    }
                    break;
            }

            charNext();
        }

        if (mode == Mode::TAG_END_SEARCH) {
            throw "Mustache-Lexer - Unfinished tag";
        }

        //It's all text
        if (mode == Mode::TEXT && m_total_tags == 0) {
            addElementFromText(0, m_position);
        }
    }
}