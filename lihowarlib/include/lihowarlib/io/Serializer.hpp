#ifndef LIHOWAR_SERIALIZER_HPP
#define LIHOWAR_SERIALIZER_HPP

#include <tao/json.hpp>
#include <string>
#include <iostream>

namespace lihowar {

class Serializer {

public:
    // MEMBERS
    tao::json::value _data;

protected:
    // CONSTRUCTORS & DESTRUCTORS
    Serializer() = default;
    ~Serializer() = default;

public:
    /// \brief get instance of the Serializer singleton class
    static Serializer& instance() {
        static Serializer instance;
        return instance;
    }
    // prevent instance duplication
    Serializer(const Serializer&) = delete;
    Serializer(Serializer&&) = delete;
    Serializer& operator=(const Serializer&) = delete;
    Serializer& operator=(Serializer&&) = delete;

public:
    // INTERFACE
    template<typename T>
    static T get(std::string key) {
        return instance()._data.at(key).as<T>();
    }
};

}


#endif //LIHOWAR_SERIALIZER_HPP
