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
#pragma once
#ifndef LIHOWAR_TEXTURE_HPP
#define LIHOWAR_TEXTURE_HPP

#include <map>
#include <GL/glew.h>
#include <glimac/Image.hpp>
#include <lihowarlib/GameConfig.hpp>

namespace lihowar {

enum class TextureName {
    SKY,
    BEACON1_DIFF, BEACON1_LUMIN,
    BEACON2_DIFF, BEACON2_LUMIN,
    AIRSHIP_BALLOON_DIFF  , AIRSHIP_BALLOON_AO  , AIRSHIP_BALLOON_NORMAL,
    AIRSHIP_NACELLE_DIFF  , AIRSHIP_NACELLE_AO  , AIRSHIP_NACELLE_NORMAL,
    AIRSHIP_WOODFLOOR_DIFF, AIRSHIP_WOODFLOOR_AO,
    PENTABALL_DIFF, PENTABALL_AO, PENTABALL_NORMAL, PENTABALL_LUMIN, PENTABALL_SPEC,
    PLATEFORM_DIFF, PLATEFORM_AO, PLATEFORM_NORMAL,
    first = SKY, last = PLATEFORM_NORMAL
};

class Texture {

public:
    // CONSTANTS
    const static std::map<TextureName, std::string> PATHS;
    static const unsigned int TEX_UNIT_DIFFUSE = 0;
    static const unsigned int TEX_UNIT_SPECULAR = 1;
    static const unsigned int TEX_UNIT_LUMIN = 2;
    static const unsigned int TEX_UNIT_AO = 3;
    static const unsigned int TEX_UNIT_NORMAL = 4;

private:
    // MEMBERS
    TextureName _textureName;
    GLuint _id;
    std::unique_ptr<glimac::Image> _img;

public:
    // CONSTRUCTORS & DESTRUCTORS
    explicit Texture(TextureName texName);
    ~Texture();
    
public:
    // INTERFACE
    GLuint &id() { return _id; }

private:
    std::string &getPath(TextureName texName);

};

}


#endif //LIHOWAR_TEXTURE_HPP
