#include <iostream>
#include <string>
#include <stdexcept>      // std::out_of_range
#include <cstdio>       //EOF
#include <vector>
#include <string>

//https://github.com/janl/mustache.js/ - See all the possibilities
//https://mustache.github.io/mustache.5.html - All items
//https://mustache.github.io/mustache.1.html - cli
/*
namespace mustache {
    constexpr size_t min_string_len = 4;

    enum class ElementTypes {
        TAG,
        TEXT
    };

    class Element {
        std::string m_data;
        ElementTypes m_type;
    public:

        Element(std::string a, ElementTypes m = ElementTypes::TEXT) : m_data(a), m_type(m) {
        };
        
        std::string getData() const {
            return m_data;
        }
    };

    enum class Mode {
        TEXT,
        TAG_END_SEARCH
    };

    class Lexer {
        std::string m_text;

        std::string m_TagStart = "{{";
        std::string m_TagEnd = "}}";

        std::size_t m_position = 0;
        std::size_t m_position_marker = 0;
        std::string::size_type m_size;

        std::vector<Element> m_elements;

        const char getChar() noexcept {
            try {
                return m_text.at(m_position);
            } catch (const std::out_of_range& oor) {
                return EOF;
            }
        }

        void charGoFowardUntil(char a) noexcept {

        }

        void charBack() noexcept {
            m_position--;
        }

        void charNext() noexcept {
            m_position++;
        }

        void mark_position() {
            m_position_marker = m_position;
        }

        void reset_position_to_marker() {
            m_position = m_position_marker;
        }

        bool isTagPart(std::string part) {
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

        bool isTagStart() {
            return isTagPart(m_TagStart);
        }

        bool isTagEnd() {
            return isTagPart(m_TagEnd);
        }

        void lex() {
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

    public:
        
        void dump_elements() {
            for (const auto &i : m_elements) {
                std::cout << i.getData() << '\n';                
            }
        }

        Lexer(const std::string &str) : m_text(str), m_size(str.size()) {
            if (m_size <= min_string_len) {
                throw "String too small";
            }

            lex();
        }

        void lex(const std::string &str) {
            m_text = str;
            m_size = str.size();

            lex();
        }


    };
}
*/
int main(int argc, char **argv) {
    std::string mustache_string{"Text1 {{tag1}} Text2 {{Tag2}}"};
    //std::string mustache_string{"Hll"};
/*
    try {
        mustache::Lexer lex{mustache_string};
        
        lex.dump_elements();
    } catch (char const *e) {
        std::cout << "Error: " << e << '\n';
    }
 * */
    //lexer -> Create tokens 





    //parser -> Syntax tree
    //Evaluator -> res


    return 0;
}

