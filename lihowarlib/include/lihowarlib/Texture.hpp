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

/**
 * @brief Enumeration of the usable texture name
 */
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

/**
 * @brief Represents a Texture image of a material
 */
class Texture {

public:
    // CONSTANTS

    /**
     * @brief Map of image file paths indexed with a TextureName
     */
    const static std::map<TextureName, std::string> PATHS;
    static const unsigned int TEX_UNIT_DIFFUSE = 0;
    static const unsigned int TEX_UNIT_SPECULAR = 1;
    static const unsigned int TEX_UNIT_LUMIN = 2;
    static const unsigned int TEX_UNIT_AO = 3;
    static const unsigned int TEX_UNIT_NORMAL = 4;

private:
    // MEMBERS

    /**
     * @brief The corresponding TextureName
     */
    TextureName _textureName;

    /**
     * @brief GL ID of the texture
     */
    GLuint _id;

    /**
     * Pointer to the Image instance
     */
    std::unique_ptr<glimac::Image> _img;

public:
    // CONSTRUCTORS & DESTRUCTORS

    /**
     * @brief Texture class constructor
     * @param texName  The corresponding texture name
     */
    explicit Texture(TextureName texName);

    /**
     * @brief Texture class destructor
     */
    ~Texture();
    
public:
    // INTERFACE

    /**
     * Gets the GL ID of the texture
     * @return  Returns the GL ID of the texture
     */
    GLuint &id() { return _id; }

private:
    /**
     * @brief Gets the file path corresponding to a given TextureName
     * @param texName  The requested texture name
     * @return  Returns the file path of the image
     */
    std::string &getPath(TextureName texName);

};

}


#endif //LIHOWAR_TEXTURE_HPP
