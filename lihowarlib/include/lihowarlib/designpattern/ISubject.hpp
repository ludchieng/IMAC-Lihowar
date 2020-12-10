#ifndef LIHOWAR_ISUBJECT_HPP
#define LIHOWAR_ISUBJECT_HPP

#include <lihowarlib/common.hpp>
#include <lihowarlib/designpattern/IObserver.hpp>

using namespace lihowar;

namespace lihowar {

namespace dp {

class ISubject {
public:
    virtual ~ISubject() = default;
    virtual void attach(IObserver *o) = 0;
    virtual void detach(IObserver *o) = 0;
    virtual void notify() = 0;
};

}

}


#endif //LIHOWAR_ISUBJECT_HPP
