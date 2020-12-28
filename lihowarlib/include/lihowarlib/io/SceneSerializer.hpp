#ifndef LIHOWAR_SCENESERIALIZER_HPP
#define LIHOWAR_SCENESERIALIZER_HPP

#include <lihowarlib/io/Serializer.hpp>
#include <lihowarlib/Scene.hpp>
#include <lihowarlib/Object.hpp>
#include <lihowarlib/objects/Island.hpp>
#include <lihowarlib/objects/Beacon.hpp>
#include <lihowarlib/objects/Pentaball.hpp>
#include <lihowarlib/objects/Plateform.hpp>

namespace lihowar {

class SceneSerializer : public Serializer {

private: // singleton
    // CONSTRUCTORS & DESTRUCTORS
    SceneSerializer() : Serializer() {}

public:
    // INTERFACE
    static std::unique_ptr<Scene> load();

    template<typename T>
    static T dataTry(std::function<T()> fct, T fallback) {
        try {
            return (T) fct();
        } catch (std::exception &e) {
            return fallback;
        }
    }

    template<typename T>
    static void deserializeArrayIntoList(
            const tao::json::value &data,
            std::list<std::unique_ptr<T>> &destList);

    template<typename T>
    static void deserializeArrayIntoVector(
            const tao::json::value &data,
            std::vector<std::unique_ptr<T>> &destVector);

    static Object &deserializeObject(const tao::json::value &data);

    static glm::vec3    deserializeVec3     (const tao::json::value &data);
    static Object::PRS &deserializePRS      (const tao::json::value &data);
    static Material    &deserializeMaterial (const tao::json::value &data);
    static Island      &deserializeIsland   (const tao::json::value &data);
    static Beacon      &deserializeBeacon   (const tao::json::value &data);
    static Pentaball   &deserializePentaball(const tao::json::value &data);
    static Plateform   &deserializePlateform(const tao::json::value &data);

private:
    static std::string format(const std::string &s) {
        // to lowercase
        std::string res(s);
        std::transform(res.begin(), res.end(), res.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        return res;
    }

    static GLuint getTexId(const tao::json::value &data, const std::string &key);
};

}


#endif //LIHOWAR_SCENESERIALIZER_HPP
