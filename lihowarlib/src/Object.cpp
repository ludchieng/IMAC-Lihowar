#include <lihowarlib/Object.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

glm::mat4 Object::matModel() const {
    glm::mat4 res(1.);
    res = glm::translate( res, _prs.pos() );
    res = glm::rotate( res, glm::radians(_prs.rot().x), glm::vec3(1., 0., 0.) );
    res = glm::rotate( res, glm::radians(_prs.rot().y), glm::vec3(0., 1., 0.) );
    res = glm::rotate( res, glm::radians(_prs.rot().z), glm::vec3(0., 0., 1.) );
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
    if (_material->hasTexture())
        glBindTexture(GL_TEXTURE_2D, _material->textureId());

    glBindVertexArray(_mesh.vao());
    glDrawElements(GL_TRIANGLES, _mesh.geometry().getIndexCount(),
                   GL_UNSIGNED_INT, 0);

    if (_material->hasTexture())
        glBindTexture(GL_TEXTURE_2D, 0);

    glBindVertexArray(0);
}

}
