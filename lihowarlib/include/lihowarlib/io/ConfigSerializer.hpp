#ifndef LIHOWAR_CONFIGSERIALIZER_HPP
#define LIHOWAR_CONFIGSERIALIZER_HPP

#include <tao/json.hpp>
#include <string>
#include <iostream>
#include <lihowarlib/exceptions/LihowarIOException.hpp>

namespace lihowar {

class ConfigSerializer {

private:
    // MEMBERS
    tao::json::value _cfg;

private:
    // CONSTRUCTORS & DESTRUCTORS
    ConfigSerializer() = default;

    ~ConfigSerializer() = default;

public:
    /// \brief get instance of the ConfigSerializer singleton class
    static ConfigSerializer& instance() {
        static ConfigSerializer instance;
        return instance;
    }
    // prevent instance duplication
    ConfigSerializer(const ConfigSerializer&) = delete;
    ConfigSerializer(ConfigSerializer&&) = delete;
    ConfigSerializer& operator=(const ConfigSerializer&) = delete;
    ConfigSerializer& operator=(ConfigSerializer&&) = delete;

public:
    // INTERFACE
    static void load(const std::string &configFilePath) {
        try {
            instance()._cfg = tao::json::parse_file(configFilePath);
        } catch (tao::json_pegtl::input_error &err) {
            throw LihowarIOException("Unable to read a valid json config file at: " + configFilePath, __FILE__, __LINE__);
        }
    }

    template<typename T>
    static T get(std::string key) {
        return instance()._cfg.at(key).as<T>();
    }
};

}


#endif //LIHOWAR_CONFIGSERIALIZER_HPP
