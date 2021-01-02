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
#ifndef LIHOWAR_PLATEFORM_HPP
#define LIHOWAR_PLATEFORM_HPP

#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/Object.hpp>

namespace lihowar {

/**
 * @brief Represents a plateform game object
 */
class Plateform : public Object {

private:
    // MEMBERS

public:
    // CONSTRUCTORS & DESTRUCTORS

    /**
     * @brief Plateform class constructor
     * @param prs  Position, rotation and scale state
     */
    explicit Plateform(PRS prs = PRS())
       :Object(
            *AssetManager::mesh(MeshName::PLATEFORM),
            *new Material(
                    AssetManager::texId(TextureName::PLATEFORM_DIFF),
                    AssetManager::NO_TEXTURE,
                    AssetManager::NO_TEXTURE,
                    AssetManager::texId(TextureName::PLATEFORM_AO),
                    AssetManager::texId(TextureName::PLATEFORM_NORMAL)),
            prs)
    {}
    
public:
    // INTERFACE

};

}


#endif //LIHOWAR_PLATEFORM_HPP
