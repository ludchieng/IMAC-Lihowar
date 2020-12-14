#ifndef LIHOWAR_MODEL_HPP
#define LIHOWAR_MODEL_HPP

#include <GL/glew.h>
#include <glimac/FilePath.hpp>
#include <glimac/Geometry.hpp>
#include <lihowarlib/common.hpp>
#include <lihowarlib/exceptions/LihowarException.hpp>

namespace lihowar {

enum ModelID {
    Platonoid, Cube, Character, Twist, Sphere
};

class Model {

private:
    // MEMBERS
    ModelID _modelID;
    glimac::Geometry _geometry;
    GLuint _vbo;
    GLuint _ibo;
    GLuint _vao;

public:
    // CONSTRUCTORS & DESTRUCTORS
    explicit Model(ModelID modelId);

    Model(const Model& m)
            :_modelID( m._modelID ),
             _geometry( m._geometry ),
             _vbo( m._vbo ),
             _ibo( m._ibo ),
             _vao( m._vao )
    {}

    ~Model();

public:
    // INTERFACE
    glimac::Geometry geometry() const { return _geometry; }
    GLuint vao() const { return _vao; };
    GLuint vbo() const { return _vbo; };
    GLuint ibo() const { return _ibo; };

private:
    void initGeometry(ModelID modelId);
    void initVBO();
    void initIBO();
    void initVAO();
};

}


#endif //LIHOWAR_MODEL_HPP
