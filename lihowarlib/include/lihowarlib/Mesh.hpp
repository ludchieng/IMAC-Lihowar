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

enum class MeshName {
    ISLAND1, ISLAND2,
    BEACON1, CUBE, SPHERE, PENTABALL, PLATEFORM,
    AIRSHIP_BALLOON, AIRSHIP_NACELLE, AIRSHIP_WOODFLOOR,
    first = ISLAND1, last = AIRSHIP_WOODFLOOR
};

class Mesh {

public:
    // CONSTANTS
    const static std::map<MeshName, std::string> PATHS;

private:
    // MEMBERS
    MeshName _meshName;
    glimac::Geometry _geometry;
    GLuint _vbo;
    GLuint _ibo;
    GLuint _vao;

public:
    // CONSTRUCTORS & DESTRUCTORS
    explicit Mesh(MeshName meshName);

    Mesh(const Mesh& m)
            : _meshName(m._meshName ),
              _geometry( m._geometry ),
              _vbo( m._vbo ),
              _ibo( m._ibo ),
              _vao( m._vao )
    {}

    ~Mesh();

public:
    // INTERFACE
    glimac::Geometry geometry() const { return _geometry; }
    GLuint vao() const { return _vao; };
    GLuint vbo() const { return _vbo; };
    GLuint ibo() const { return _ibo; };
    glm::vec3 center() const { return glimac::center(_geometry.getBoundingBox()); }
    glm::vec3 size() const { return _geometry.getBoundingBox().size(); }

private:
    void initGeometry(MeshName meshName);
    void initVBO();
    void initIBO();
    void initVAO();

private:
    std::string &getPath(MeshName meshName);

};

}


#endif //LIHOWAR_MESH_HPP
