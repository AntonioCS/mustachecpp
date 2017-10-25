
#include "Variable.h"

namespace Mustache {
    namespace Tags {

        Variable::Variable() {
        }

        Variable::Variable(T t) : m_value(t) {

        }

        Variable::Variable(const Variable& orig) {
        }

        void Variable::setValue(T value) {
            m_value = value;
        }
        T Variable::getValue() const noexcept {
            return m_value;
        }
    }
}