#include <lihowarlib/GameController.hpp>
#include <lihowarlib/AssetManager.hpp>
#include <lihowarlib/LightPoint.hpp>
#include <lihowarlib/LightDirectional.hpp>
#include <lihowarlib/ObjectDynamic.hpp>
#include <lihowarlib/Material.hpp>
#include <lihowarlib/objects/Island.hpp>
#include <lihowarlib/objects/Beacon.hpp>
#include <lihowarlib/objects/Pentaball.hpp>
#include <lihowarlib/objects/Plateform.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

GameController::GameController()
    : _scene(new Scene()),
      _gRenderer(GameRenderer::instance(_scene->player()))
{

    _scene->add(new Island(
            MeshName::ISLAND1,
            Object::PRS(
                    glm::vec3(70., -40., 0.),
                    glm::vec3(0., 0., 0.),
                    glm::vec3(2.))) );

    _scene->islands()[0]->add(new Beacon(
            MeshName::BEACON1,
            *new Material(
                    AssetManager::texId(TextureName::BEACON1_DIFF), 0,
                    AssetManager::texId(TextureName::BEACON1_LUMIN) ),
            Object::PRS(
                    glm::vec3(-5.621, 28.893, 5.174),
                    glm::vec3(180., 0., 0.),
                    glm::vec3(1.5))) );

    _scene->add(new Island(
            MeshName::ISLAND2,
            Object::PRS(
                    glm::vec3(500., -40., 0.),
                    glm::vec3(0., 0., 0.),
                    glm::vec3(4.))) );

    _scene->islands()[1]->add(new Pentaball(Object::PRS(
            glm::vec3( -3.198,    4.464,    5.886),
            glm::vec3(0.),
            glm::vec3(.5))) );

    _scene->islands()[1]->add(new Pentaball(Object::PRS(
            glm::vec3(-43.191,    7.150,   26.150),
            glm::vec3(0.),
            glm::vec3(.5))) );

    _scene->islands()[1]->add(new Pentaball(Object::PRS(
            glm::vec3(-12.695,    1.741,   61.437),
            glm::vec3(0.),
            glm::vec3(.5))) );

    _scene->islands()[1]->add(new Plateform(Object::PRS(
            glm::vec3( 42.450,    1.773,  -45.637),
            glm::vec3(0., -35., 0.),
            glm::vec3(.5))) );

    _scene->islands()[1]->add(new Plateform(Object::PRS(
            glm::vec3( 69.441,    3.874,  -33.820),
            glm::vec3(0., 40., 0.),
            glm::vec3(.5))) );

    _scene->islands()[1]->add(new Plateform(Object::PRS(
            glm::vec3( 50.660,    9.905,  -21.183),
            glm::vec3(0.),
            glm::vec3(.5))) );

    _scene->islands()[1]->add(new Beacon(
            MeshName::BEACON1,
            *new Material(
                    AssetManager::texId(TextureName::BEACON2_DIFF), 0,
                    AssetManager::texId(TextureName::BEACON2_LUMIN) ),
            Object::PRS(
                    glm::vec3( 51.521,   20.539,  -35.154),
                    glm::vec3(180., 0., 0.),
                    glm::vec3(1.5))) );

    _scene->add(new LightPoint(
            glm::vec3(.25, .15, .1),
            _scene->player().prs().pos(),
            glm::vec3(0., -.5, 0.)) );

    _scene->add(new LightDirectional(
            glm::vec3(.95, .85, .83), glm::vec3(0., -.8, 1.)) );

    _scene->add(new LightDirectional(
            glm::vec3(.21, .18, .13), glm::vec3(0., 1., 0.)) );


    /*_scene->player().add(new ObjectDynamic(
            *AssetManager::meshes()[MeshName::CUBE],
            AssetManager::NO_TEXTURE,
            Object::PRS( glm::vec3(4.))) );*/

    SceneSerializer::save(*_scene);

    if (cfg::DEBUG) cout << "[GameController::GameController] END" << endl;
}


void GameController::update()
{
    auto test = _scene->objects().begin()->get();
    //test->prs().rot() += glm::vec3(1., 0., 0.);
    auto beacon1 = _scene->islands()[0].get()->subobjects().begin()->get();
    beacon1->material().kl() = .5 + .5 * glm::cos(.1 * _scene->player().prs().pos().x * 5.);
    _scene->skybox().setCenter(_gRenderer.camera().targetPRS().pos());
    _scene->player().update();
    auto it = _scene->islands().begin();
    while(it != _scene->islands().end()) {
        (**it).update();
        ++it;
    }
}

}
