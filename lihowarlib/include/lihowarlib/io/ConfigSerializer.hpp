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
    static void load(const std::string &configFilePath) {
        try {
            instance()._data = tao::json::parse_file(configFilePath);
        } catch (tao::json_pegtl::input_error &err) {
            throw LihowarIOException("Unable to read a valid json config file at: " + configFilePath, __FILE__, __LINE__);
        }
    }
};

}


#endif //LIHOWAR_CONFIGSERIALIZER_HPP
