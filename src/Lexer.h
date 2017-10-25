
#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>
#include <stdexcept>      // std::out_of_range
#include <cstdio>       //EOF
#include <cctype> //isspace
#include <algorithm> //find_if
#include <functional>
#include "LexerElement.h"

namespace Mustache {
    constexpr size_t min_string_len = 4;

    namespace {
        auto isSpaceFunc = [](const int &ch) {
                return !std::isspace(ch);
        };
    }

    enum class Mode {
        TEXT,
        TAG_END_SEARCH
    };

    class Lexer {
        std::string m_text;
        size_t m_total_tags{0};

        std::string m_TagStart{"{{"};
        std::string m_TagEnd{"}}"};

        size_t m_position{0};
        std::string::size_type m_size;

        std::vector<LexerElement> m_elements;

        const char getChar() const noexcept;

        inline void charBack(size_t n = 1) noexcept {
            m_position -= n;
        }

        inline void charNext() noexcept {
            m_position++;
        }

        bool isTagPart(std::string part) noexcept;

        inline bool isTagStart() noexcept {
            return isTagPart(m_TagStart);
        }

        inline bool isTagEnd() noexcept {
            return isTagPart(m_TagEnd);
        }

        inline void addElementFromText(size_t start, size_t length, LexerElementType type = LexerElementType::TEXT) noexcept {
            m_elements.emplace_back(m_text.substr(start, length), type);
        }

        //https://stackoverflow.com/a/217605/8715
        inline void ltrim(std::string &s) {
            s.erase(
                s.begin(),
                std::find_if(
                    s.begin(),
                    s.end(),
                    isSpaceFunc
                )
            );
        }

        // trim from end (in place)
        inline void rtrim(std::string &s) {
            //http://en.cppreference.com/w/cpp/iterator/reverse_iterator/base
            s.erase(
                std::find_if(
                    s.rbegin(),
                    s.rend(),
                    isSpaceFunc
                ).base(), s.end());
        }

        inline void trim(std::string &s) {
            ltrim(s);
            rtrim(s);
        }

        void lex();
    public:
        Lexer(const std::string &str);
        virtual ~Lexer();

        void lex(const std::string &str);

        void dump_elements() const;

        std::vector<LexerElement> getElements() const noexcept;

    };
}
#endif /* LEXER_H */

