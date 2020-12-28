#ifndef LIHOWAR_LIHOWAREXCEPTION_HPP
#define LIHOWAR_LIHOWAREXCEPTION_HPP

#include <exception>
#include <cstdlib>
#include <string>

namespace lihowar {

class LihowarException : public std::exception {

protected:
    // MEMBERS
    std::string _what;

public:
    // CONSTRUCTORS & DESTRUCTORS
    LihowarException(
            const std::string& message,
            const char* file,
            const int line)
       :_what("LihowarException: ["
              + std::string(file) + ":" + std::to_string(line)
              + "]: " + message)
        {}

    ~LihowarException() = default;

public:
    // INTERFACE
    inline const char* what() const noexcept override
    {
        return _what.c_str();
    };

};

}


#endif //LIHOWAR_LIHOWAREXCEPTION_HPP
