#include <lihowarlib/GameObject.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

glm::mat4 GameObject::matModel() const {
    glm::mat4 res(1.);
    res = glm::translate( res, _prs.pos() );
    res = glm::rotate( res, glm::radians(_prs.rot().x), glm::vec3(1., 0., 0.) );
    res = glm::rotate( res, glm::radians(_prs.rot().y), glm::vec3(0., 1., 0.) );
    res = glm::rotate( res, glm::radians(_prs.rot().z), glm::vec3(0., 0., 1.) );
    res = glm::scale( res, _prs.sca() );
    return res;
}


void GameObject::render()
{
    glBindVertexArray(_model.vao());
    glDrawElements(GL_TRIANGLES, _model.geometry().getIndexCount(),
                   GL_UNSIGNED_INT, 0);
}

}