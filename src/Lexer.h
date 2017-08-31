
#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>
#include <stdexcept>      // std::out_of_range
#include <cstdio>       //EOF
#include "LexerElement.h"

namespace mustache {
    constexpr size_t min_string_len = 4;

    enum class Mode {
        TEXT,
        TAG_END_SEARCH
    };

    class Lexer {
        std::string m_text;

        std::string m_TagStart{"{{"};
        std::string m_TagEnd{"}}"};

        std::size_t m_position{0};
        std::size_t m_position_marker{0};
        std::string::size_type m_size;

        std::vector<LexerElement> m_elements;

        const char getChar() const noexcept;

        void charBack() noexcept {
            m_position--;
        }

        void charNext() noexcept {
            m_position++;
        }

        void mark_position() noexcept {
            m_position_marker = m_position;
        }

        void reset_position_to_marker() noexcept {
            m_position = m_position_marker;
        }

        bool isTagPart(std::string part) noexcept;

        bool isTagStart() noexcept {
            return isTagPart(m_TagStart);
        }

        bool isTagEnd() noexcept {
            return isTagPart(m_TagEnd);
        }

        void lex();
    public:
        Lexer(const std::string &str);
        virtual ~Lexer();

        void lex(const std::string &str);

        void dump_elements() const ;

        std::vector<LexerElement> getElements() const noexcept;

    };
}
#endif /* LEXER_H */

