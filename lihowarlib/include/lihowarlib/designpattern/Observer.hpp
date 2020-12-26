#ifndef LIHOWAR_DP_OBSERVER_HPP
#define LIHOWAR_DP_OBSERVER_HPP

#include <list>
#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/designpattern/ISubject.hpp>
#include <lihowarlib/designpattern/IObserver.hpp>

namespace lihowar {

namespace dp {

class Observer : public IObserver {

private:
    // MEMBERS
    std::list<ISubject*> _subjects;

public:
    // CONSTRUCTORS & DESTRUCTORS
    Observer() = default;
    ~Observer() override = default;

public:
    // INTERFACE
    void update() override {}
    void addSubject(ISubject *s) {
        _subjects.push_back(s);
        s->attach(this);
    }

    void removeSubject(ISubject *s) {
        _subjects.remove(s);
        s->detach(this);
    }
};

}

}


#endif //LIHOWAR_DP_OBSERVER_HPP
