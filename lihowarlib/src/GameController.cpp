#include <lihowarlib/GameController.hpp>

using namespace lihowar;

namespace lihowar {

void GameController::render()
{
    AssetManager &am = AssetManager::instance();

    Model platonic = am.models()[ModelID::Platonoid];
    Model cube = am.models()[ModelID::Cube];

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(platonic.vao());
    glDrawElements(
            GL_TRIANGLES,
            platonic.geometry().getIndexCount(),
            GL_UNSIGNED_INT,
            0);

    /*glBindVertexArray(cube.vao());
    glDrawElements(
            GL_TRIANGLES,
            cube.geometry().getIndexCount(),
            GL_UNSIGNED_INT,
            0);*/
    glLoadIdentity();
}

}