#ifndef LIHOWAR_LIHOWARIOEXCEPTION_HPP
#define LIHOWAR_LIHOWARIOEXCEPTION_HPP

#include <exception>
#include <cstdlib>
#include <string>
#include <lihowarlib/exceptions/LihowarException.hpp>

namespace lihowar {

class LihowarIOException : public LihowarException {

public:
    // CONSTRUCTORS & DESTRUCTORS
    LihowarIOException(
        const std::string& message,
        const char* file,
        const int line)
       :LihowarException(message, file, line)
    {}

    ~LihowarIOException() = default;

public:
    // INTERFACE
    inline const char* what() const noexcept override
    {
        std::string msg = "LihowarIOException: ["
                + _file + ":" + std::to_string(_line)
                + "]: " + _message;

        std::cerr << msg << std::endl;

        return msg.c_str();
    };

};

}


#endif //LIHOWAR_LIHOWARIOEXCEPTION_HPP
