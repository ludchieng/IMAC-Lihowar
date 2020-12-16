#include <lihowarlib/GameController.hpp>
#include <lihowarlib/programs/DirLightProgram.hpp>

#include <glimac/Sphere.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

GameController::GameController()
    : _assetManager(AssetManager::instance()),
      _gRenderer(GameRenderer::instance()),
      _scene(new Scene())
{
    _scene->add(unique_ptr<GameObject>(
        new GameObject(
            *_assetManager.meshes()[MeshName::Character],
            _assetManager.textureId(TextureName::Earth),
            DirLightProgram::instance()  )));

    for (int i = 0; i < 20; ++i) {
        _scene->add(unique_ptr<GameObject>(
            new GameObject(
                *_assetManager.meshes()[MeshName::Character],
                _assetManager.textureId(TextureName::Moon),
                DirLightProgram::instance(),
                GameObject::PRS(
                    glm::sphericalRand(3.f),
                    glm::sphericalRand(360.f),
                    glm::vec3(1.f, 1.f, 1.f)  ))));
    }

    SceneSerializer::save(*_scene);

    //if (DEBUG) cout << "[GameController::GameController] END" << endl;
}


void GameController::render()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto it = _scene->gObjects().begin();
    while (it != _scene->gObjects().end()) {
        GameObject &g = **it;
        g.translate(g.prs().pos() * .0005f);
        g.rotate(glm::vec3(.2f, .05f, .1f));
        g.program().use();
        _gRenderer.updateMatMV(g.matModel());
        _gRenderer.bindUniformVariables(g, *_scene);
        g.render();
        ++it;
        //if (DEBUG) cout << "\n---------------------- NEXT OBJECT\n" << endl;
    }

    //if (DEBUG) cout << "\n====================== NEXT FRAME\n\n" << endl;
}

}
