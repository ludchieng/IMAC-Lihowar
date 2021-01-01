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

/**
 * @brief Singleton class to handle JSON scene description files loading
 */
class SceneSerializer : public Serializer {

private: // singleton
    // CONSTRUCTORS & DESTRUCTORS

    /**
     * @brief SceneSerializer class default constructor
     */
    SceneSerializer() : Serializer() {}

public:
    // INTERFACE

    /**
     * @brief Creates a Scene from JSON scene description file
     * @param sceneFilePath  Scene description file
     * @return Returns a Scene instance corresponding to the description file
     */
    static std::unique_ptr<Scene> load(
            const std::string &sceneFilePath = cfg::PATH_SCENES + cfg::SCENE);

    /**
     * @brief Tries to execute a function. Returns a fallback value if it fails
     * @tparam T        Expected return type of the function
     * @param fct       Function to execute
     * @param fallback  Value to return if the function execution fails
     * @return Returns the return value of the provided function if it succeed, or fallback, otherwise.
     */
    template<typename T>
    static T dataTry(std::function<T()> fct, T fallback) {
        try {
            return (T) fct();
        } catch (std::exception &e) {
            return fallback;
        }
    }

    /**
     * @brief Fill in the given list from JSON data
     * @tparam T        Type of objects to put in the list
     * @param data      JSON data
     * @param destList  List to fill in
     */
    template<typename T>
    static void deserializeArrayIntoList(
            const tao::json::value &data,
            std::list<std::unique_ptr<T>> &destList);

    /**
     * @brief Fill in the given vector from JSON data
     * @tparam T          Type of objects to put in the vector
     * @param data        JSON data
     * @param destVector  Vector to fill in
     */
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
    /**
     * @brief Format string for string comparison
     * @param s  String to format
     * @return Returns the formatted string
     */
    static std::string format(const std::string &s) {
        // to lowercase
        std::string res(s);
        std::transform(res.begin(), res.end(), res.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        return res;
    }

    /**
     * @brief Gets texture GL ID from its corresponding string value
     * @param data  JSON data
     * @param key   String in the JSON file which corresponds to a texture
     * @return the GL ID of the corresponding texture
     */
    static GLuint getTexId(const tao::json::value &data, const std::string &key);
};

}


#endif //LIHOWAR_SCENESERIALIZER_HPP
