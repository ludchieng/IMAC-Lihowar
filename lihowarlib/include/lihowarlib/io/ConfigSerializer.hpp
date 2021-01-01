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
#ifndef LIHOWAR_CONFIGSERIALIZER_HPP
#define LIHOWAR_CONFIGSERIALIZER_HPP

#include <lihowarlib/io/Serializer.hpp>
#include <lihowarlib/exceptions/LihowarIOException.hpp>

namespace lihowar {

class ConfigSerializer : public Serializer {

private: // singleton
    // CONSTRUCTORS & DESTRUCTORS
    ConfigSerializer() : Serializer() {}

public:
    // INTERFACE
    static void load(const std::string &configFilePath)
    {
        try {
            instance()._data = tao::json::parse_file(configFilePath);
        } catch (tao::json_pegtl::input_error &err) {
            throw LihowarIOException("Unable to read a valid json config file at: " + configFilePath, __FILE__, __LINE__);
        }
    }
};

}


#endif //LIHOWAR_CONFIGSERIALIZER_HPP
