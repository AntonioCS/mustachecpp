
#ifndef LEXERELEMENT_H
#define LEXERELEMENT_H

#include <string>

namespace mustache {

    enum class LexerElementTypes {
        TAG,
        TEXT
    };

    class LexerElement {
        std::string m_data;
        LexerElementTypes m_type;
    public:

        LexerElement(std::string data, LexerElementTypes m = LexerElementTypes::TEXT) : m_data(data), m_type(m) {
        };

        std::string getData() const {
            return m_data;
        }
    };
}
#endif /* LEXERELEMENT_H */

