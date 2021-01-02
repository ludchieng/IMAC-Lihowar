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
#ifndef LIHOWAR_DP_SUBJECT_HPP
#define LIHOWAR_DP_SUBJECT_HPP

#include <list>
#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/designpattern/ISubject.hpp>
#include <lihowarlib/designpattern/IObserver.hpp>

using namespace lihowar;

namespace lihowar {

namespace dp {

/**
 * @brief Subject class for the Observer design pattern
 */
class Subject : public ISubject {

private:
    // MEMBERS
    std::list<IObserver*> _observers;

public:
    // CONSTRUCTORS & DESTRUCTORS
    Subject() = default;
    ~Subject() override = default;

public:
    // INTERFACE
    void attach(IObserver *o) override { _observers.push_back(o); }
    void detach(IObserver *o) override { _observers.remove(o); }
    void notify() override {
        // Update all observers
        auto it = _observers.begin();
        while (it != _observers.end()) {
            (*it)->update();
            ++it;
        }
    }

};

}

}


#endif //LIHOWAR_DP_SUBJECT_HPP
