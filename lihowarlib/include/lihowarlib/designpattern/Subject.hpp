#ifndef LIHOWAR_DP_SUBJECT_HPP
#define LIHOWAR_DP_SUBJECT_HPP

#include <list>
#include <lihowarlib/common.hpp>
#include <lihowarlib/designpattern/ISubject.hpp>
#include <lihowarlib/designpattern/IObserver.hpp>

using namespace lihowar;

namespace lihowar {

namespace dp {

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
