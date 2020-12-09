#ifndef LIHOWAR_LIHOWAREXCEPTION_HPP
#define LIHOWAR_LIHOWAREXCEPTION_HPP

#include <exception>
#include <iostream>
#include <cstdlib>
#include <string>
#include <lihowarlib/common.hpp>

namespace lihowar {

class LihowarException : public std::exception {

private:
    // MEMBERS
    std::string _message;
    std::string _file;
    int _line;

public:
    // CONSTRUCTORS & DESTRUCTORS
    LihowarException(
            const std::string& message,
            const char* file,
            const int line)
       :_message(message),
        _file(file),
        _line(line) {}

    ~LihowarException() = default;

public:
    // INTERFACE
    inline const char* what() const noexcept
    {
        std::string msg = "LihowarException: ["
                + _file + ":" + std::to_string(_line)
                + "]: " + _message;

        std::cerr << msg << std::endl;

        return msg.c_str();
    };

};

}


#endif //LIHOWAR_LIHOWAREXCEPTION_HPP
