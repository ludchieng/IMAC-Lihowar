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
    : _scene(SceneSerializer::load()),
      _gRenderer(GameRenderer::instance(_scene->player()))
{
    _scene->add(new LightPoint(
            glm::vec3(.05, .03, .02),
            _scene->player().prs().pos(),
            glm::vec3(0., -.5, 0.)) );

    _scene->add(new LightDirectional(
            glm::vec3(.95, .85, .83), glm::vec3(0., -.8, 1.)) );

    _scene->add(new LightDirectional(
            glm::vec3(.21, .18, .13), glm::vec3(0., 1., 0.)) );

    if (cfg::DEBUG) cout << "[GameController::GameController] END" << endl << endl << endl;
}


void GameController::update()
{
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
