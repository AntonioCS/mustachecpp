#ifndef SIMPLE_H
#define SIMPLE_H

#include "Value.h"

namespace Mustache {
    namespace Values {
        template <typename S>
        class Simple : public Value<S> {
            Simple(S v) : Value<S>(v) {}
        };
    }
}

#endif /* SIMPLE_H */

