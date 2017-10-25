#ifndef MUSTACHE_H
#define MUSTACHE_H

#include <vector>
#include <string>
#include <unordered_map>
#include "Values/Value.h"


namespace Mustache {

    class Mustache {
    public:
        Mustache();
        Mustache(const Mustache& orig);
        virtual ~Mustache();
        template <typename T>
        void add(std::string key, T v) {
            values[key] = new Values::Value<T>(v);
        }

    private:
        std::unordered_map<std::string, Values::Value*> values;
    };
}
#endif /* MUSTACHE_H */

