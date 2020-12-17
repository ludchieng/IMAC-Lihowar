#include <lihowarlib/GameRenderer.hpp>
#include <lihowarlib/programs/Program.hpp>
#include <lihowarlib/programs/DirLightProgram.hpp>
#include <lihowarlib/programs/MultiLightsProgram.hpp>
#include <lihowarlib/LightDirectional.hpp>
#include <lihowarlib/LightPoint.hpp>

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


void GameRenderer::bindUniformVariables(GameObject &gObject, const Scene &scene)
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
            glUniform1f(dlprog.uKd(), gObject.material().kd());
            glUniform1f(dlprog.uKs(), gObject.material().ks());
            glUniform1f(dlprog.uKa(), gObject.material().ka());
            glUniform1f(dlprog.uShininess(), gObject.material().shininess());
            glUniform3fv(dlprog.uLightDir(), 1, glm::value_ptr( glm::normalize(glm::vec3(lightDir)) ));
            glUniform3fv(dlprog.uLightIntensity(), 1, glm::value_ptr( glm::vec3(1.) ));
            glUniform1i(dlprog.uHasTexture(), gObject.material().hasTexture() );
            break;
        }
        case ProgramType::MultiLights:
        {
            MultiLightsProgram &mlprog = *( dynamic_cast<MultiLightsProgram*>(&prog) );
            glUniform1f(mlprog.uKd(), gObject.material().kd());
            glUniform1f(mlprog.uKs(), gObject.material().ks());
            glUniform1f(mlprog.uKa(), gObject.material().ka());
            glUniform1f(mlprog.uShininess(), gObject.material().shininess());
            glUniform1i(mlprog.uHasTexture(), gObject.material().hasTexture());

            unsigned int ldIndex = 0; // LightDirectional array index cursor
            unsigned int lpIndex = 0; // LightoPoint array index cursor
            auto it = scene.lights().begin();
            while (it != scene.lights().end()) {
                LightDirectional *ld = dynamic_cast<LightDirectional*>(it->get());
                LightPoint *lp = dynamic_cast<LightPoint*>(it->get());
                if (NULL != ld) {
                    // downcast to LightDirectional succeeded
                    glUniform3fv(mlprog.uLightsDir(ldIndex, "dir"), 1, glm::value_ptr( _matView * glm::vec4(ld->dir(), 0.) ));
                    glUniform3fv(mlprog.uLightsDir(ldIndex, "intensity"), 1, glm::value_ptr( ld->intensity() ));
                    ldIndex++;
                } else if (NULL != lp){
                    // downcast to LightPoint succeeded
                    glUniform3fv(mlprog.uLightsPoint(lpIndex, "pos"), 1, glm::value_ptr( _matView * glm::vec4(lp->pos(), 1.) ));
                    glUniform3fv(mlprog.uLightsPoint(lpIndex, "intensity"), 1, glm::value_ptr( lp->intensity() ));
                    lpIndex++;
                } else {
                    throw LihowarException("Downcast Light instance failed", __FILE__, __LINE__);
                }
                ++it;
            }

            //if (DEBUG) cout << "ldIndex: " << ldIndex << endl;
            //if (DEBUG) cout << "lpIndex: " << lpIndex << endl;

            glUniform1i(mlprog.uLightsDirCount(), ldIndex );
            glUniform1i(mlprog.uLightsPointCount(), lpIndex );
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
