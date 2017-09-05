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
        int loops{0};
        bool is_tag{false};

        for (const char &s : part) {
            auto c = getChar();
            loops++;

            if (s == c) {
                charNext();
                is_tag = true;
                continue;
            }

            is_tag = false;
            break;
        }

        if (is_tag == false) {
            //charBack(loops);
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
        size_t grab_from_pos = 0;

        while (getChar() != EOF) {
            switch (mode) {
                case Mode::TEXT:
                    if (isTagStart()) {
                        //A tag is the first element
                        if (m_position - m_TagStart.length() == 0) {
                            grab_from_pos = m_TagStart.length();
                        } else {
                            //If we have multiple tags together there won't be any text to grab
                            size_t len = m_position - m_TagEnd.length() - grab_from_pos;
                            if (len > 0) {
                                addElementFromText(grab_from_pos, len);
                                grab_from_pos = m_position;
                            } else {
                                grab_from_pos += m_TagStart.length();
                            }
                        }

                        mode = Mode::TAG_END_SEARCH;
                    }
                    //charNext();
                    break;

                case Mode::TAG_END_SEARCH:
                    if (isTagEnd()) {
                        m_total_tags++;
                        size_t len = m_position - m_TagEnd.length() - grab_from_pos;

                        addElementFromText(grab_from_pos, len, LexerElementType::TAG);

                        grab_from_pos = m_position;

                        mode = Mode::TEXT;
                        charBack();
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