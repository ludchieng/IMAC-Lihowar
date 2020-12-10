#include <lihowarlib/GameRenderer.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

GameRenderer::GameRenderer()
   : _matProj( glm::perspective(glm::radians(FOV), ASPECT_RATIO, Z_NEAR, Z_FAR) ),
     _matMV( glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -5.f)) ),
     _matNormal( glm::transpose(glm::inverse(_matMV)) ),
     _matView(glm::mat4(1.f) ),
     _tbcam( TrackballCamera(5.f, 0.f, 0.f) )
{
    _matView = _tbcam.getMatView();

    // Design pattern observer on trackballcamera
    addSubject(&_tbcam);
}


GameRenderer::~GameRenderer() {}


void GameRenderer::useProgram()
{
    lihowar::NormalProgram::instance().use();
}


void GameRenderer::bindUniformVariables()
{
    //if (DEBUG) cout << "[GameRenderer::bindUniformVariables] " << endl;
    auto &pNormal = lihowar::NormalProgram::instance();
    glUniformMatrix4fv(pNormal.uMatMVP(), 1, GL_FALSE, glm::value_ptr(_matProj * _matMV));
    glUniformMatrix4fv(pNormal.uMatMV(), 1, GL_FALSE, glm::value_ptr(_matMV));
    glUniformMatrix4fv(pNormal.uMatNormal(), 1, GL_FALSE, glm::value_ptr(_matNormal));
}


void GameRenderer::update()
{
    //if (DEBUG) cout << "[GameRenderer::update]" << endl;
    updateMatMV();
}


void GameRenderer::updateMatMV(const glm::mat4 &matModel)
{
    _matView = _tbcam.getMatView();
    _matMV = _matView * matModel;
}

}