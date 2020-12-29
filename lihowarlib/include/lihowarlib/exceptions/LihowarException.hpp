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
#ifndef LIHOWAR_LIHOWAREXCEPTION_HPP
#define LIHOWAR_LIHOWAREXCEPTION_HPP

#include <exception>
#include <cstdlib>
#include <string>

namespace lihowar {

class LihowarException : public std::exception {

protected:
    // MEMBERS
    std::string _what;

public:
    // CONSTRUCTORS & DESTRUCTORS
    LihowarException(
            const std::string& message,
            const char* file,
            const int line)
       :_what("LihowarException: ["
              + std::string(file) + ":" + std::to_string(line)
              + "]: " + message)
        {}

    ~LihowarException() = default;

public:
    // INTERFACE
    inline const char* what() const noexcept override
    {
        return _what.c_str();
    };

};

}


#endif //LIHOWAR_LIHOWAREXCEPTION_HPP
