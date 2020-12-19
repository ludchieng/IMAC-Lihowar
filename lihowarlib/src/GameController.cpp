#include <lihowarlib/GameController.hpp>
#include <lihowarlib/programs/MultiLightsProgram.hpp>
#include <lihowarlib/Skybox.hpp>
#include <lihowarlib/LightPoint.hpp>
#include <lihowarlib/LightDirectional.hpp>

#include <glimac/Sphere.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

GameController::GameController()
    : _scene(new Scene()),
      _assetManager(AssetManager::instance()),
      _gRenderer(GameRenderer::instance(_scene->player()->prs().pos()))
{

    _scene->add(new Object(
            *_assetManager.meshes()[MeshName::ISLAND1],
            _assetManager.NO_TEXTURE,
            Object::PRS(
                    glm::vec3(70., -40., 0.),
                    glm::vec3(0., -195., 0.)   )));

    _scene->add(new Object(
            *_assetManager.meshes()[MeshName::ISLAND1],
            _assetManager.NO_TEXTURE,
            Object::PRS(
                    glm::vec3(180., -40., -50.),
                    glm::vec3(0., 72., 0.)   )));

    _scene->add(new LightPoint(
            glm::vec3(.25, .15, .1), glm::vec3(0., 1., 0.)) );

    _scene->add(new LightDirectional(
            glm::vec3(.95, .85, .83), glm::vec3(0., -.8, 1.)) );

    _scene->add(new LightDirectional(
            glm::vec3(.21, .18, .13), glm::vec3(0., 1., 0.)) );


    _scene->player()->add( new Object(
            *AssetManager::instance().meshes()[MeshName::CUBE],
            _assetManager.NO_TEXTURE,
            Object::PRS( glm::vec3(5.))) );

    SceneSerializer::save(*_scene);

    //if (DEBUG) cout << "[GameController::GameController] END" << endl;
}


void GameController::render()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _scene->skybox()->setCenter(_gRenderer.camera().target());

    /*LightPoint *lp = dynamic_cast<LightPoint*>(_scene->lights().front().get());
    lp->pos() = glm::vec3(0., -1., 0.);*/

    _scene->player()->translate( glm::vec3(0., 0., .05) );

    _gRenderer.use(SkyboxProgram::instance());
    render(_scene->skybox());

    _gRenderer.use(MultiLightsProgram::instance());
    render(_scene->player());
    render(_scene->objects());

    //if (DEBUG) cout << "\n====================== NEXT FRAME\n\n" << endl;
}


void GameController::render(
        const std::list< std::unique_ptr<Object> > &objectsList,
        const glm::mat4 &matModelParent)
{
    auto it = objectsList.begin();
    while (it != objectsList.end()) {
        render(**it, matModelParent);
        ++it;
    }
}


void GameController::render(
        const Object &object,
        const glm::mat4 &matModelParent)
{
    _gRenderer.updateMatMV(matModelParent * object.matModel());
    _gRenderer.bindUniformVariables(object, *_scene);
    object.render();
    render(object.subobjects(), object.matModel());
}

}
