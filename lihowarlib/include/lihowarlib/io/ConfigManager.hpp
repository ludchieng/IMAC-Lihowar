#ifndef LIHOWAR_CONFIGMANAGER_HPP
#define LIHOWAR_CONFIGMANAGER_HPP

#include <lihowarlib/common.hpp>
#include <lihowarlib/exceptions/LihowarIOException.hpp>

namespace lihowar {

class ConfigManager {
    
public:
    // INTERFACE
    static void load(const std::string &filename = "config");

};

}


#endif //LIHOWAR_CONFIGMANAGER_HPP
