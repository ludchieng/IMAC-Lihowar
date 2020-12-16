#include <lihowarlib/GameController.hpp>
#include <lihowarlib/programs/DirLightProgram.hpp>
#include <lihowarlib/programs/DirLightTexProgram.hpp>

#include <glimac/Sphere.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

GameController::GameController()
    : _assetManager(AssetManager::instance()),
      _gRenderer(GameRenderer::instance())
{
    _gObjects.push_back(unique_ptr<GameObject>(
        new GameObjectTextured(
            *_assetManager.meshes()[MeshName::Character],
            _assetManager.textureId(TextureName::Earth),
            DirLightTexProgram::instance()  )));

    for (int i = 0; i < 20; ++i) {
        _gObjects.push_back(unique_ptr<GameObject>(
            new GameObjectTextured(
                *_assetManager.meshes()[MeshName::Character],
                _assetManager.textureId(TextureName::Moon),
                DirLightTexProgram::instance(),
                GameObject::PRS(
                    glm::sphericalRand(3.f),
                    glm::sphericalRand(360.f),
                    glm::vec3(1.f, 1.f, 1.f)  ))));
    }

    //if (DEBUG) cout << "[GameController::GameController] END" << endl;
}


void GameController::render()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto it = _gObjects.begin();
    while (it != _gObjects.end()) {
        GameObject &g = **it;
        g.translate(g.prs().pos() * .0005f);
        g.rotate(glm::vec3(.2f, .05f, .1f));
        g.program().use();
        _gRenderer.updateMatMV(g.matModel());
        _gRenderer.bindUniformVariables(g);
        g.render();
        ++it;
        //if (DEBUG) cout << "\n---------------------- NEXT OBJECT\n" << endl;
    }

    //if (DEBUG) cout << "\n====================== NEXT FRAME\n\n" << endl;
}

}
