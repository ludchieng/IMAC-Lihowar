/*
 *  Copyright (c) 2020-2021 Lihowar
 *
 *  This software is licensed under OSEF License.
 *
 *  The "Software" is defined as the pieces of code, the documentation files, the config
 *  files, the textures assets, the Wavefront OBJ assets, the screenshot image, the sound
 *  effects and music associated with.
 *
 *  This Software is licensed under OSEF License which means IN ACCORDANCE WITH THE LICENSE
 *  OF THE DEPENDENCIES OF THE SOFTWARE, you can use it as you want for any purpose, but
 *  it comes with no guarantee of any kind, provided that you respects the license of the
 *  software dependencies of the piece of code you want to reuse. The dependencies are
 *  listed at the end of the README given in the directory root of the Lihowar repository.
 */
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
    _scene->skybox().setCenter(_gRenderer.camera().targetPRS().pos());
    _scene->player().update();

    auto beacons = _scene->findAll<Beacon>();
    auto itB = beacons.begin();
    while (itB != beacons.end()) {
        (**itB).material().kl() = .5 + .5 * glm::cos(.1 * _scene->player().prs().pos().x * 5.);
        ++itB;
    }

    auto itI = _scene->islands().begin();
    while(itI != _scene->islands().end()) {
        (**itI).update();
        ++itI;
    }
}

}
