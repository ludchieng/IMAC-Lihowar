#include <lihowarlib/GameRenderer.hpp>
#include <lihowarlib/programs/Program.hpp>
#include <lihowarlib/programs/NormalProgram.hpp>
#include <lihowarlib/programs/DirLightProgram.hpp>

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


void GameRenderer::bindUniformVariables(GameObject &gObject)
{
    //if (DEBUG) cout << "[GameRenderer::bindUniformMatrices] " << endl;
    Program &prog = gObject.program();

    // send matrices to GPU
    glUniformMatrix4fv(prog.uMatMVP(), 1, GL_FALSE, glm::value_ptr(_matProj * _matMV));
    glUniformMatrix4fv(prog.uMatMV(), 1, GL_FALSE, glm::value_ptr(_matMV));
    glUniformMatrix4fv(prog.uMatNormal(), 1, GL_FALSE, glm::value_ptr(_matNormal));

    // send extra variables to GPU depending on program (and shader) type
    switch(prog.type()) {
        case ProgramType::DirLight:
        {
            glm::vec4 lightDir = _matView * glm::vec4(1.f, 1.f, 1.f, 0.f);
            DirLightProgram &dlprog = *( dynamic_cast<DirLightProgram*>(&prog) );
            glUniform3fv(dlprog.uLightDir(), 1, glm::value_ptr( glm::normalize(glm::vec3(lightDir)) ));
            break;
        }
        default:
            break;
    }
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
    _matNormal = glm::transpose(glm::inverse(_matMV));
}

}
