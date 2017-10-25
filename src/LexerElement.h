
#ifndef LEXERELEMENT_H
#define LEXERELEMENT_H

#include <string>

namespace Mustache {

    enum class LexerElementType {
        TAG,
        TEXT
    };

    class LexerElement {
        std::string m_data;
        LexerElementType m_type;
    public:

        LexerElement(std::string data, LexerElementType m = LexerElementType::TEXT) : m_data(data), m_type(m) {
        };

        std::string getData() const noexcept {
            return m_data;
        }

        LexerElementType getType() const noexcept {
            return m_type;
        }

    };
}
#endif /* LEXERELEMENT_H */

