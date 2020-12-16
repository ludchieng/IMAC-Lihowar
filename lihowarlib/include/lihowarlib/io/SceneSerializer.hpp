#ifndef LIHOWAR_SCENESERIALIZER_HPP
#define LIHOWAR_SCENESERIALIZER_HPP

#include <lihowarlib/common.hpp>
#include <lihowarlib/Scene.hpp>
#include <lihowarlib/exceptions/LihowarIOException.hpp>

namespace lihowar {

class SceneSerializer {
    
public:
    // INTERFACE
    static void save(const Scene &s);
    static void load(Scene &s);

    static std::string serialize(const GameObject &g);
    static std::string serialize(const Light &l);

};

}


#endif //LIHOWAR_SCENESERIALIZER_HPP
