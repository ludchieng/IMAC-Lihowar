#include <lihowarlib/GameController.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

GameController::GameController()
    : _assetManager(AssetManager::instance()),
      _gRenderer(GameRenderer::instance())
{
    _gObjects.push_back(GameObject( *_assetManager.models()[ModelID::Character],
        GameObject::PRS(
            glm::vec3(1.f, 0.f, 0.f),
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(1.f, 1.f, 1.f)  )));
}

void GameController::render()
{
    GameObject &g = _gObjects.front();
    g.translate(glm::vec3(.002));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    _gRenderer.useProgram();
    _gRenderer.updateMatMV(g.matModel());
    _gRenderer.bindUniformVariables();

    g.render();

    glLoadIdentity();
}

}