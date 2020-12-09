#include <lihowarlib/Controller.hpp>

using namespace lihowar;

namespace lihowar {

void Controller::render()
{
    AssetManager &am = AssetManager::instance();

    Model cube = am.models()[ModelID::Cube];

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(cube.vao());
    glDrawElements(
            GL_TRIANGLES,
            cube.geometry().getIndexCount(),
            GL_UNSIGNED_INT,
            0);
    glLoadIdentity();
}

}