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
#ifndef LIHOWAR_DP_OBSERVER_HPP
#define LIHOWAR_DP_OBSERVER_HPP

#include <list>
#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/designpattern/ISubject.hpp>
#include <lihowarlib/designpattern/IObserver.hpp>

namespace lihowar {

namespace dp {

/**
 * @brief Observer class for the Observer design pattern
 */
class Observer : public IObserver {

private:
    // MEMBERS

    /**
     * @brief list of subjects that are observed
     */
    std::list<ISubject*> _subjects;

public:
    // CONSTRUCTORS & DESTRUCTORS

    /**
     * @brief Observer class default constructor
     */
    Observer() = default;

    /**
     * @brief Observer class default destructor
     */
    ~Observer() override = default;

public:
    // INTERFACE

    /**
     * @brief Updates state of the instance
     *
     * Update occurs usually when the subjects have changed
     * their state and have notified their observers
     */
    void update() override {}

    /**
     * @brief Adds a subject to the subjects list
     * @param s  Subject to add
     */
    void addSubject(ISubject *s) {
        _subjects.push_back(s);
        s->attach(this);
    }

    /**
     * @brief Removes subject from the subjects list
     * @param s  Subject to remove
     */
    void removeSubject(ISubject *s) {
        _subjects.remove(s);
        s->detach(this);
    }
};

}

}


#endif //LIHOWAR_DP_OBSERVER_HPP
