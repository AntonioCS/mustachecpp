
#ifndef VALUE_H
#define VALUE_H
namespace Mustache {
    namespace Values {

        template<typename T>
        class Value {
        public:

            enum class Types {
                SIMPLE,
                BOOL,
                LAMBDA,
                LIST,
                ARRAY
            };
            Value(T v) : m_value(v){

            }
            virtual T getValue() const noexcept {
                return m_value;
            }
        private:
            T m_value;


        };
    }
}

#endif /* VALUE_H */

