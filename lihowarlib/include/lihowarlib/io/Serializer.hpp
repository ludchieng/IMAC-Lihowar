/*
 *  Copyright (c) 2020-2021 Lihowar
 *
 *  This software is licensed under OSEF License.
 *
 *  The "Software" is defined as the pieces of code, the documentation files, the config
 *  files, the textures assets, the Wavefront OBJ assets, the screenshot image, the sound
 *  effects and music associated with.
 *
 *  This Software is licensed under OSEF License which means IN ACCORDANCE WITH THE LICENSE
 *  OF THE DEPENDENCIES OF THE SOFTWARE, you can use it as you want for any purpose, but
 *  it comes with no guarantee of any kind, provided that you respects the license of the
 *  software dependencies of the piece of code you want to reuse. The dependencies are
 *  listed at the end of the README given in the directory root of the Lihowar repository.
 */
#pragma once
#ifndef LIHOWAR_SERIALIZER_HPP
#define LIHOWAR_SERIALIZER_HPP

#include <tao/json.hpp>
#include <string>
#include <iostream>

namespace lihowar {

/**
 * @brief Singleton class to handle JSON files loading
 */
class Serializer {

public:
    // MEMBERS

    /**
     * @brief JSON data
     */
    tao::json::value _data;

protected:
    // CONSTRUCTORS & DESTRUCTORS

    /**
     * @brief Serializer class default constructor
     */
    Serializer() = default;

    /**
     * @brief Serializer class default destructor
     */
    ~Serializer() = default;

public:
    /**
     * @brief Gets instance of the Serializer singleton class
     */
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

    /**
     * @brief Gets value of a key string
     * @tparam T   Expected type for the value
     * @param key  Key string of the value
     * @return Returns the value associated with its key string
     */
    template<typename T>
    static T get(std::string key) {
        return instance()._data.at(key).as<T>();
    }
};

}


#endif //LIHOWAR_SERIALIZER_HPP
