#ifndef LIHOWAR_IOBSERVER_HPP
#define LIHOWAR_IOBSERVER_HPP

#include <lihowarlib/common.hpp>
#include <lihowarlib/designpattern/ISubject.hpp>

namespace lihowar {

namespace dp {

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update() = 0;
};

}

}


#endif //LIHOWAR_IOBSERVER_HPP
