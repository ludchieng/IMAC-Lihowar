#include <lihowarlib/GameController.hpp>

using namespace lihowar;

namespace lihowar {

void GameController::render()
{
    AssetManager &am = AssetManager::instance();

    //Model *a = am.models()[ModelID::Platonoid];
    Model *a = am.models()[ModelID::Character];
    //Model *cube = am.models()[ModelID::Cube];

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    _gRenderer.useProgram();
    _gRenderer.bindUniformVariables();

    glBindVertexArray(a->vao());
    glDrawElements(
            GL_TRIANGLES,
            a->geometry().getIndexCount(),
            GL_UNSIGNED_INT,
            0);

    /*glBindVertexArray(cube->vao());
    glDrawElements(
            GL_TRIANGLES,
            cube->geometry().getIndexCount(),
            GL_UNSIGNED_INT,
            0);*/
    glLoadIdentity();
}

}