#include <lihowarlib/Object.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

const glm::vec3 Object::PRS::X = glm::vec3(1., 0., 0.);
const glm::vec3 Object::PRS::Y = glm::vec3(0., 1., 0.);
const glm::vec3 Object::PRS::Z = glm::vec3(0., 0., 1.);
const glm::vec4 Object::PRS::vec4_X = glm::vec4(1., 0., 0., 0.);
const glm::vec4 Object::PRS::vec4_Y = glm::vec4(0., 1., 0., 0.);
const glm::vec4 Object::PRS::vec4_Z = glm::vec4(0., 0., 1., 0.);

glm::mat4 Object::matModel() const {
    glm::mat4 res(1.);
    res = glm::rotate( res, _prs.rotRadians().y, PRS::Y );
    res = glm::rotate( res, _prs.rotRadians().x, PRS::X );
    res = glm::rotate( res, _prs.rotRadians().z, PRS::Z );
    res = glm::translate( glm::mat4(1.) , _prs.pos() ) * res;
    res = glm::scale( res, _prs.sca() );
    return res;
}


void Object::add(std::unique_ptr<Object> object)
{
    _subobjects.push_back(std::move(object));
}


void Object::update()
{
    auto it = _subobjects.begin();
    while(it != _subobjects.end()) {
        (**it).update();
        ++it;
    }
}


void Object::render() const
{
    if (_material->hasDiffuseMap()) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _material->diffuseTexId());
    }
    if (_material->hasSpecularMap()) {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, _material->specularTexId());
    }
    if (_material->hasLuminMap()) {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, _material->luminTexId());
    }
    if (_material->hasAOMap()) {
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, _material->aoTexId());
    }
    if (_material->hasNormalMap()) {
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, _material->normalTexId());
    }

    glBindVertexArray(_mesh.vao());
    glDrawElements(GL_TRIANGLES, _mesh.geometry().getIndexCount(),
                   GL_UNSIGNED_INT, 0);


    if (_material->hasDiffuseMap()) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    if (_material->hasSpecularMap()) {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    if (_material->hasLuminMap()) {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    if (_material->hasAOMap()) {
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    if (_material->hasNormalMap()) {
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    glBindVertexArray(0);
}

}
