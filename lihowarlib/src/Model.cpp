#include <lihowarlib/Model.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

Model::Model(ModelName modelName)
    : _modelName(modelName)
{
    if (DEBUG) cout << "[Model::Model] modelName: " << _modelName << endl;
    initGeometry(modelName);
    initVBO();
    initIBO();
    initVAO();
}


Model::~Model()
{
    if (DEBUG) cout << "[Model::~Model] modelName: " << _modelName << endl;
    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, &_vao);
}


void Model::initGeometry(ModelName modelName)
{
    string filename;

    // Get model name from ModelName
    switch (modelName) {
        case Platonoid:
            filename = "platonoid";
            break;
        case Cube:
            filename = "cube";
            break;
        case Character:
            filename = "character";
            break;
        case Twist:
            filename = "twist";
            break;
        case Sphere:
            filename = "sphere";
            break;
        default:
            throw LihowarException("Unknown path for specified ModelName", __FILE__, __LINE__);
    }

    if (DEBUG) cout << "[Model::initGeometry] modelName: " << filename << endl;

    glimac::FilePath objPath = PATH_ASSETS + "models/" + filename + ".obj";
    glimac::FilePath mtlPath = PATH_ASSETS + "models/" + filename + ".mtl";

    if (!_geometry.loadOBJ(objPath, mtlPath, true))
        throw LihowarException("OBJ loading failed: " + filename, __FILE__, __LINE__);
}


void Model::initVBO()
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(
            GL_ARRAY_BUFFER,
            _geometry.getVertexCount() * sizeof(glimac::Geometry::Vertex),
            _geometry.getVertexBuffer(),
            GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    _vbo = vbo;
}


void Model::initIBO()
{
    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            _geometry.getIndexCount() * sizeof(uint32_t),
            _geometry.getIndexBuffer(),
            GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    _ibo = ibo;
}


void Model::initVAO()
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXCOORD = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORD);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glVertexAttribPointer(
            VERTEX_ATTR_POSITION,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(glimac::Geometry::Vertex),
            (const GLvoid*) offsetof(glimac::Geometry::Vertex, m_Position));

    glVertexAttribPointer(
            VERTEX_ATTR_NORMAL,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(glimac::Geometry::Vertex),
            (const GLvoid*) offsetof(glimac::Geometry::Vertex, m_Normal));

    glVertexAttribPointer(
            VERTEX_ATTR_TEXCOORD,
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(glimac::Geometry::Vertex),
            (const GLvoid*) offsetof(glimac::Geometry::Vertex, m_TexCoords));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
    _vao = vao;
}

}
