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
#include <lihowarlib/Mesh.hpp>
#include <lihowarlib/exceptions/LihowarException.hpp>
#include <iostream>

using namespace std;
using namespace lihowar;

namespace lihowar {

const map<MeshName, string> Mesh::PATHS = {
        { MeshName::ISLAND1           , "island1/island1_lod2.obj"  },
        { MeshName::ISLAND2           , "island2/island2_lod2.obj"  },
        { MeshName::BEACON1           , "beacons/beacon1.obj"       },
        { MeshName::CUBE              , "cube.obj"                  },
        { MeshName::SPHERE            , "sphere.obj"                },
        { MeshName::PENTABALL         , "pentaball.obj"             },
        { MeshName::PLATEFORM         , "plateform.obj"             },
        { MeshName::AIRSHIP_BALLOON   , "airship/balloon.obj"       },
        { MeshName::AIRSHIP_NACELLE   , "airship/nacelle.obj"       },
        { MeshName::AIRSHIP_WOODFLOOR , "airship/woodfloor.obj"     },
};


Mesh::Mesh(MeshName meshName)
    : _meshName(meshName)
{
    initGeometry(meshName);
    initVBO();
    initIBO();
    initVAO();
}


Mesh::~Mesh()
{
    if (cfg::DEBUG) cout << "[Mesh::~Mesh] meshName: " << (int) _meshName << endl;
    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, &_vao);
}


string &Mesh::getPath(MeshName meshName)
{
    try {
        return const_cast<string &>(PATHS.at(meshName));
    } catch (out_of_range &e) {
        throw LihowarException("Unknown path for specified MeshName: index: " + to_string((int) meshName), __FILE__, __LINE__);
    }
}


void Mesh::initGeometry(MeshName meshName)
{
    glimac::FilePath objPath = cfg::PATH_ASSETS + "meshes/" + getPath(meshName);
    glimac::FilePath mtlPath = cfg::PATH_ASSETS + "meshes/default.mtl";

    if (!_geometry.loadOBJ(objPath, mtlPath, true))
        throw LihowarException("OBJ loading failed: " + objPath.str(), __FILE__, __LINE__);

    if (cfg::DEBUG) cout << "[Mesh::initGeometry] successfully loaded mesh at: " << getPath(meshName) << endl << endl;
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
