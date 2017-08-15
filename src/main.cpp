#include <iostream>
#include <string>

//https://github.com/janl/mustache.js/ - See all the possibilities
//https://mustache.github.io/mustache.5.html - All items
//https://mustache.github.io/mustache.1.html - cli

namespace mustache {
    constexpr size_t min_string_len = 4;

    class Elements {
        std::string data;
    public:
        void add(const char a) noexcept {
            data += a;
        }
    };

    class Tag : public Elements {
    };

    class Text : public Elements {
    };

    class Lexer {
        std::string text;

        std::string TagStart = "{{";
        std::string TagEnd = "}}";

        std::size_t position = 0;
        std::size_t position_marker = 0;
        std::string::size_type size;

        const char &getChar() noexcept {
            return text.at(position);
        }

        void charGoFowardUntil(char a) noexcept {

        }

        void charBack() noexcept {
            position--;
        }

        void charNext() noexcept {
            position++;
        }

        void mark_position() {
            position_marker = position;
        }

        void reset_position_to_marker() {
            position = position_marker;
        }

        bool isTagStart() {
            mark_position();
            bool is_tag = false;
            std::cout << "current char: " << getChar() << '\n';

            for (const char &s : TagStart) {
                if (s == '\n') {
                    break;
                }

                if (s == getChar()) {
                    charNext();
                    is_tag = true;
                    continue;
                }

                is_tag = false;
                break;
            }

            if (is_tag == false)
                reset_position_to_marker();

            return is_tag;
        }
        
        void lex() {            
            while (position < size) {
                if (isTagStart()) {

                } else {
                    //create Text holder
                }
                charNext();
            }
        }

    public:       
        
        Lexer(const std::string &str) : text(str), size(str.size()) {
            if (size <= min_string_len) {
                throw "String too small";
            }

            lex();
        }
        
        void lex(const std::string &str) {
            text = str;
            size = str.size();
            
            lex();
        }


    };
}

int main(int argc, char **argv) {
    std::string mustache_string{"Hello {{name}}"};
    //std::string mustache_string{"Hll"};

    try {
        mustache::Lexer lex{mustache_string};
    } catch (char const *e) {
        std::cout << "Error: " << e << '\n';
    }
    //lexer -> Create tokens 





    //parser -> Syntax tree
    //Evaluator -> res


    return 0;
}

