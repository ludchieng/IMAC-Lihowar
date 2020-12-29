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
#include <lihowarlib/GameRenderer.hpp>
#include <lihowarlib/programs/Program.hpp>
#include <lihowarlib/programs/DirLightProgram.hpp>
#include <lihowarlib/programs/NormalProgram.hpp>
#include <lihowarlib/programs/MultiLightsProgram.hpp>
#include <lihowarlib/LightDirectional.hpp>
#include <lihowarlib/LightPoint.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

GameRenderer::GameRenderer(Player &camTarget)
   : _tbcam( TrackballCamera(camTarget) ),
     _matProj( glm::perspective(glm::radians(_tbcam.fov()), cfg::ASPECT_RATIO, cfg::Z_NEAR, cfg::Z_FAR) ),
     _matMV( glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -5.f)) ),
     _matNormal( glm::transpose(glm::inverse(_matMV)) ),
     _matView( glm::mat4(1.f) ),
     _program( &MultiLightsProgram::instance() )
{
    _matView = _tbcam.getMatView();

    if (cfg::USE_ANTIALIASING)
        glEnable(GL_MULTISAMPLE);
}


GameRenderer::~GameRenderer() {}


void GameRenderer::use(Program &program)
{
    if (_program == &program)
        return;
    _program = &program;
    _program->use();
}


void GameRenderer::bindUniformVariables(const Object &object, const Scene &scene)
{
    //if (cfg::DEBUG) cout << "[GameRenderer::bindUniformMatrices] " << endl;

    // send matrices to GPU
    glUniformMatrix4fv(_program->uMatMVP(), 1, GL_FALSE, glm::value_ptr(_matProj * _matMV));
    glUniformMatrix4fv(_program->uMatMV(), 1, GL_FALSE, glm::value_ptr(_matMV));
    glUniformMatrix4fv(_program->uMatNormal(), 1, GL_FALSE, glm::value_ptr(_matNormal));

    // send extra variables to GPU depending on program (and shader) type
    switch(_program->type()) {
        case ProgramType::DIRLIGHT:
        {
            glm::vec4 lightDir = _matView * glm::vec4(1.f, 1.f, 1.f, 0.f);
            DirLightProgram &p = *( dynamic_cast<DirLightProgram*>(_program) );
            glUniform1f(p.uKd(), object.material().kd());
            glUniform1f(p.uKs(), object.material().ks());
            glUniform1f(p.uShininess(), object.material().shininess());
            glUniform3fv(p.uLightDir(), 1, glm::value_ptr( glm::normalize(glm::vec3(lightDir)) ));
            glUniform3fv(p.uLightIntensity(), 1, glm::value_ptr( glm::vec3(1.) ));
            glUniform1i(p.uHasTexture(), object.material().hasDiffuseMap() );
            break;
        }
        case ProgramType::MULTILIGHTS:
        {
            MultiLightsProgram &p = *( dynamic_cast<MultiLightsProgram*>(_program) );
            glUniform1f(p.uKd(), object.material().kd());
            glUniform1f(p.uKs(), object.material().ks());
            glUniform1f(p.uKl(), object.material().kl());
            glUniform1f(p.uKao(), object.material().kao());
            glUniform1f(p.uKn(), object.material().kn());
            glUniform1f(p.uShininess(), object.material().shininess());
            glUniform1i(p.uHasDiffuseMap(), object.material().hasDiffuseMap());
            glUniform1i(p.uHasSpecularMap(), object.material().hasSpecularMap());
            glUniform1i(p.uHasLuminMap(), object.material().hasLuminMap());
            glUniform1i(p.uHasAOMap(), object.material().hasAOMap());
            glUniform1i(p.uHasNormalMap(), object.material().hasNormalMap());
            glUniform1i(p.uDiffuseMap(), Texture::TEX_UNIT_DIFFUSE);
            glUniform1i(p.uSpecularMap(), Texture::TEX_UNIT_SPECULAR);
            glUniform1i(p.uLuminMap(), Texture::TEX_UNIT_LUMIN);
            glUniform1i(p.uAOMap(), Texture::TEX_UNIT_AO);
            glUniform1i(p.uNormalMap(), Texture::TEX_UNIT_NORMAL);
            glUniform3fv(p.uLightAmbient(), 1, glm::value_ptr( scene.lightAmbient().intensity() ));

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
    //if (cfg::DEBUG) cout << "[GameRenderer::update]" << endl;
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
    _matProj = glm::perspective(glm::radians(_tbcam.fov()), cfg::ASPECT_RATIO, cfg::Z_NEAR, cfg::Z_FAR);
}


void GameRenderer::render(const Scene &scene)
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    use(SkyboxProgram::instance());
    render(scene, scene.skybox());

    use(NormalProgram::instance());
    use(MultiLightsProgram::instance());
    render(scene, scene.player());
    render(scene, scene.islands());
    render(scene, scene.objects());
}


void GameRenderer::render(
        const Scene &scene,
        const std::list< std::unique_ptr<Object> > &objectsList,
        const glm::mat4 &matModelParent)
{
    auto it = objectsList.begin();
    while (it != objectsList.end()) {
        render(scene, **it, matModelParent);
        ++it;
    }
}


void GameRenderer::render(
        const Scene &scene,
        const std::vector< std::unique_ptr<Island> > &objectsList,
        const glm::mat4 &matModelParent)
{
    auto it = objectsList.begin();
    while (it != objectsList.end()) {
        render(scene, **it, matModelParent);
        ++it;
    }
}


void GameRenderer::render(
        const Scene &scene,
        const Object &object,
        const glm::mat4 &matModelParent)
{
    updateMatMV(matModelParent * object.matModel());
    bindUniformVariables(object, scene);
    object.render();
    render(scene, object.subobjects(), object.matModel());
}


}
