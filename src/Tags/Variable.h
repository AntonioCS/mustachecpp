
#ifndef VARIABLE_H
#define VARIABLE_H

namespace Mustache {
    namespace Tags {

        template<typename T>
        class Variable {
        public:
            Variable(T t);

            void setValue(T value);
            T getValue() const noexcept;
        private:
            T m_value;
        };
    }
}
#endif /* VARIABLE_H */

