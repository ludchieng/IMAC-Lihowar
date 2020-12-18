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
   : _tbcam( TrackballCamera(.3f, 15.f, 30.f) ),
     _matProj( glm::perspective(glm::radians(_tbcam.fov()), ASPECT_RATIO, Z_NEAR, Z_FAR) ),
     _matMV( glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -5.f)) ),
     _matNormal( glm::transpose(glm::inverse(_matMV)) ),
     _matView( glm::mat4(1.f) )
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
        case ProgramType::DIRLIGHT:
        {
            glm::vec4 lightDir = _matView * glm::vec4(1.f, 1.f, 1.f, 0.f);
            DirLightProgram &p = *( dynamic_cast<DirLightProgram*>(&prog) );
            glUniform1f(p.uKd(), gObject.material().kd());
            glUniform1f(p.uKs(), gObject.material().ks());
            glUniform1f(p.uShininess(), gObject.material().shininess());
            glUniform3fv(p.uLightDir(), 1, glm::value_ptr( glm::normalize(glm::vec3(lightDir)) ));
            glUniform3fv(p.uLightIntensity(), 1, glm::value_ptr( glm::vec3(1.) ));
            glUniform1i(p.uHasTexture(), gObject.material().hasTexture() );
            break;
        }
        case ProgramType::MULTILIGHTS:
        {
            MultiLightsProgram &p = *( dynamic_cast<MultiLightsProgram*>(&prog) );
            glUniform1f(p.uKd(), gObject.material().kd());
            glUniform1f(p.uKs(), gObject.material().ks());
            glUniform1f(p.uShininess(), gObject.material().shininess());
            glUniform3fv(p.uLightAmbient(), 1, glm::value_ptr( scene.lightAmbient()->intensity() ));
            glUniform1i(p.uHasTexture(), gObject.material().hasTexture());

            unsigned int ldIndex = 0; // LightDirectional array index cursor
            unsigned int lpIndex = 0; // LightoPoint array index cursor
            auto it = scene.lights().begin();
            while (it != scene.lights().end()) {
                auto *ld = dynamic_cast<LightDirectional*>(it->get());
                auto *lp = dynamic_cast<LightPoint*>(it->get());
                if (nullptr != ld) {
                    // downcast to LightDirectional succeeded
                    glUniform3fv(p.uLightsDir(ldIndex, "dir"), 1, glm::value_ptr( _matView * glm::vec4(ld->dir(), 0.) ));
                    glUniform3fv(p.uLightsDir(ldIndex, "intensity"), 1, glm::value_ptr( ld->intensity() ));
                    ldIndex++;
                } else if (nullptr != lp){
                    // downcast to LightPoint succeeded
                    glUniform3fv(p.uLightsPoint(lpIndex, "pos"), 1, glm::value_ptr( _matView * glm::vec4(lp->pos(), 1.) ));
                    glUniform3fv(p.uLightsPoint(lpIndex, "intensity"), 1, glm::value_ptr( lp->intensity() ));
                    lpIndex++;
                } else {
                    throw LihowarException("Downcast Light instance failed", __FILE__, __LINE__);
                }
                ++it;
            }

            //if (DEBUG) cout << "ldIndex: " << ldIndex << endl;
            //if (DEBUG) cout << "lpIndex: " << lpIndex << endl;

            glUniform1i(p.uLightsDirCount(), ldIndex );
            glUniform1i(p.uLightsPointCount(), lpIndex );
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
    updateMatProj();
}


void GameRenderer::updateMatMV(const glm::mat4 &matModel)
{
    _matView = _tbcam.getMatView();
    _matMV = _matView * matModel;
    _matNormal = glm::transpose(glm::inverse(_matMV));
}

void GameRenderer::updateMatProj()
{
    _matProj = glm::perspective(glm::radians(_tbcam.fov()), ASPECT_RATIO, Z_NEAR, Z_FAR);
}

}
