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
#ifndef LIHOWAR_MESH_HPP
#define LIHOWAR_MESH_HPP

#include <map>
#include <GL/glew.h>
#include <glimac/FilePath.hpp>
#include <glimac/Geometry.hpp>
#include <lihowarlib/GameConfig.hpp>

namespace lihowar {

/**
 * @brief Enumeration of the usable mesh name
 */
enum class MeshName {
    ISLAND1, ISLAND2,
    BEACON1, CUBE, SPHERE, PENTABALL, PLATEFORM,
    AIRSHIP_BALLOON, AIRSHIP_NACELLE, AIRSHIP_WOODFLOOR,
    first = ISLAND1, last = AIRSHIP_WOODFLOOR
};

/**
 * @brief Represents a 3D model of a game object
 */
class Mesh {

public:
    // CONSTANTS

    /**
     * @brief Map of OBJ file paths indexed with a MeshName
     */
    const static std::map<MeshName, std::string> PATHS;

private:
    // MEMBERS

    /**
     * @brief The corresponding MeshName
     */
    MeshName _meshName;

    /**
     * @brief Geometry data
     */
    glimac::Geometry _geometry;

    /**
     * Vertex buffer object
     */
    GLuint _vbo;

    /**
     * Index buffer object
     */
    GLuint _ibo;

    /**
     * Vertex array object
     */
    GLuint _vao;

public:
    // CONSTRUCTORS & DESTRUCTORS

    /**
     * @brief Mesh class constructor
     * @param meshName  The corresponding mesh name
     */
    explicit Mesh(MeshName meshName);

    /**
     * @brief Mesh class destructor
     */
    ~Mesh();

public:
    // INTERFACE

    /**
     * @brief Gets the Geometry instance
     * @return Returns the Geometry instance
     */
    glimac::Geometry geometry() const { return _geometry; }

    /**
     * @brief Gets the Vertex array object
     * @return Returns the Vertex array object
     */
    GLuint vao() const { return _vao; };

    /**
     * @brief Gets the Vertex buffer object
     * @return Returns the Vertex buffer object
     */
    GLuint vbo() const { return _vbo; };

    /**
     * @brief Gets the Index buffer object
     * @return Returns the Index buffer object
     */
    GLuint ibo() const { return _ibo; };

    /**
     * @brief Computes the position of the mesh bounding box center of mass
     * @return Returns the position of the mesh bounding box center of mass
     */
    glm::vec3 center() const { return glimac::center(_geometry.getBoundingBox()); }

    /**
     * @brief Gets the size of the mesh bounding box
     * @return Returns the size of the mesh bounding box
     */
    glm::vec3 size() const { return _geometry.getBoundingBox().size(); }

private:
    std::string &getPath(MeshName meshName);
    void initGeometry(MeshName meshName);
    void initVBO();
    void initIBO();
    void initVAO();

};

}


#endif //LIHOWAR_MESH_HPP
