#include <lihowarlib/Mesh.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

Mesh::Mesh(MeshName meshName)
    : _meshName(meshName)
{
    if (DEBUG) cout << "[Mesh::Mesh] meshName: " << (int) _meshName << endl;
    initGeometry(meshName);
    initVBO();
    initIBO();
    initVAO();
}


Mesh::~Mesh()
{
    if (DEBUG) cout << "[Mesh::Mesh meshName: " << (int) _meshName << endl;
    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, &_vao);
}


void Mesh::initGeometry(MeshName meshName)
{
    string filename;

    // Get mesh name from MeshName
    switch (meshName) {
        case MeshName::ISLAND1:
            filename = "island1_lod2";
            break;
        case MeshName::BEACON1:
            filename = "beacon1";
            break;
        case MeshName::CUBE:
            filename = "cube";
            break;
        case MeshName::BALLOON:
            filename = "balloon";
            break;
        case MeshName::SPHERE:
            filename = "sphere";
            break;
        default:
            throw LihowarException("Unknown path for specified MeshName", __FILE__, __LINE__);
    }

    if (DEBUG) cout << "[Mesh::initGeometry] meshName: " << filename << endl;

    glimac::FilePath objPath = PATH_ASSETS + "meshes/" + filename + ".obj";
    glimac::FilePath mtlPath = PATH_ASSETS + "meshes/" + "default" + ".mtl";

    if (!_geometry.loadOBJ(objPath, mtlPath, true))
        throw LihowarException("OBJ loading failed: " + filename, __FILE__, __LINE__);
}


void Mesh::initVBO()
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


void Mesh::initIBO()
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


void Mesh::initVAO()
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
