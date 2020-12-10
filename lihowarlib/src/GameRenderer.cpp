#include <lihowarlib/GameRenderer.hpp>

using namespace lihowar;

namespace lihowar {

GameRenderer::GameRenderer()
   :_matProj( glm::perspective(glm::radians(FOV), ASPECT_RATIO, Z_NEAR, Z_FAR) ),
    _matMV( glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -5.f)) ),
    _matNormal( glm::transpose(glm::inverse(_matMV)) ),
    _matGlobal( glm::mat4(1.f) ),
    _tbcam( TrackballCamera(5.f, 0.f, 0.f) )
{
    _matGlobal = _tbcam.getMatView();
}


TrackballCamera GameRenderer::camera() const
{
    return _tbcam;
}


TrackballCamera& GameRenderer::camera()
{
    _matGlobal = _tbcam.getMatView();
    _matMV = _matGlobal;
    return _tbcam;
}


void GameRenderer::useProgram()
{
    lihowar::program::Normal::instance().use();
}


void GameRenderer::bindUniformVariables()
{
    //if (DEBUG) cout << "[GameRenderer::bindUniformVariables] " << endl;
    auto &pNormal = lihowar::program::Normal::instance();
    glUniformMatrix4fv(pNormal.uMatMVP(), 1, GL_FALSE, glm::value_ptr(_matProj * _matMV));
    glUniformMatrix4fv(pNormal.uMatMV(), 1, GL_FALSE, glm::value_ptr(_matMV));
    glUniformMatrix4fv(pNormal.uMatNormal(), 1, GL_FALSE, glm::value_ptr(_matNormal));
}

}