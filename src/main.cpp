#include <iostream>
#include <string>

//https://github.com/janl/mustache.js/ - See all the possibilities
//https://mustache.github.io/mustache.5.html - All items
//https://mustache.github.io/mustache.1.html - cli

class Lexer {
    std::string text;
    std::string ElementStart = "{{";
    std::string ElementEnd = "}}";
    
    
    int position = 0;
    char getChar() noexcept {
        
    }
    
    void charGoFowardUntil(char a) noexcept {
        
    }
    
    void charBack() {
        
    }
    
    void charNext() {
        
    }
    
    
public:
    Lexer(const std::string str) : text(str) {
        
    }
    
    
};


int main(int argc, char **argv) {
    std::string mustache_string{"Hello {{name}}"};            
        
    Lexer lex{mustache_string};
    
    //lexer -> Create tokens 
    
    
    
    
    
    //parser -> Syntax tree
    //Evaluator -> res
    
    
    return 0;
}

