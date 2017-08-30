#include "Lexer.h"

namespace mustache {

    Lexer::Lexer(const std::string &str) : m_text(str), m_size(str.size()) {
        if (m_size <= min_string_len) {
            throw "String too small";
        }

        lex();
    }

    Lexer::Lexer(const Lexer& orig) {
    }

    Lexer::~Lexer() {
    }

    void Lexer::lex(const std::string &str) {
        m_text = str;
        m_size = str.size();

        lex();
    }

    const char &Lexer::getChar() const noexcept {
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

    void Lexer::lex() {
        Mode mode = Mode::TEXT;
        size_t pos = 0;

        while (getChar() != EOF) {
            switch (mode) {
                case Mode::TEXT:
                    if (isTagStart()) {
                        if (m_position > 0) {
                            size_t len = m_position - m_TagEnd.length() - pos;
                            m_elements.emplace_back(m_text.substr(pos, len));
                            pos = len;
                        }

                        mode = Mode::TAG_END_SEARCH;
                    }
                    break;

                case Mode::TAG_END_SEARCH:
                    if (isTagEnd()) {
                        m_elements.emplace_back(
                                m_text.substr(pos, m_position - pos),
                                ElementTypes::TAG
                                );

                        pos = m_position;
                        mode = Mode::TEXT;
                    }
                    break;
            }

            charNext();
        }
    }


}