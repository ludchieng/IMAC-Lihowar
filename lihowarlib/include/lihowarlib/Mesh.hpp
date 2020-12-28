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
    friend class SceneSerializer;

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
