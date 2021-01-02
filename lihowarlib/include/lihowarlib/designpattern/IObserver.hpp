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
#ifndef LIHOWAR_DP_IOBSERVER_HPP
#define LIHOWAR_DP_IOBSERVER_HPP

#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/designpattern/ISubject.hpp>

namespace lihowar {

/**
 * @brief Design pattern namespace for design patterns
 * requiring abstract classes
 */
namespace dp {

/**
 * @brief Interface for Observer class design pattern
 */
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update() = 0;
};

}

}


#endif //LIHOWAR_DP_IOBSERVER_HPP
