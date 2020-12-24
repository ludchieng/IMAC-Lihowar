#ifndef LIHOWAR_MESH_HPP
#define LIHOWAR_MESH_HPP

#include <GL/glew.h>
#include <glimac/FilePath.hpp>
#include <glimac/Geometry.hpp>
#include <lihowarlib/GameConfig.hpp>

namespace lihowar {

enum class MeshName {
    ISLAND1,
    BEACON1, CUBE, BALLOON, SPHERE,
    first = ISLAND1, last = SPHERE
};

class Mesh {
    friend class SceneSerializer;

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
};

}


#endif //LIHOWAR_MESH_HPP
