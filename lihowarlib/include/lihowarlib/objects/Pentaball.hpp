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
#ifndef LIHOWAR_PENTABALL_HPP
#define LIHOWAR_PENTABALL_HPP

#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/Object.hpp>

namespace lihowar {

/**
 * @brief Represents a pentaball game object
 */
class Pentaball : public Object {

private:
    // MEMBERS

public:
    // CONSTRUCTORS & DESTRUCTORS

    /**
     * @brief Pentaball class constructor
     * @param prs  Position, rotation and scale state
     */
    explicit Pentaball(PRS prs = PRS())
       :Object(
            *AssetManager::mesh(MeshName::PENTABALL),
            *new Material(
                    AssetManager::texId(TextureName::PENTABALL_DIFF),
                    AssetManager::texId(TextureName::PENTABALL_SPEC),
                    AssetManager::texId(TextureName::PENTABALL_LUMIN),
                    AssetManager::texId(TextureName::PENTABALL_AO),
                    AssetManager::texId(TextureName::PENTABALL_NORMAL)),
            prs)
    {}
    
public:
    // INTERFACE

};

}


#endif //LIHOWAR_PENTABALL_HPP
