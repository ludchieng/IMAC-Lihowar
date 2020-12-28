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
    {
        _what = "LihowarIOException: ["
                + std::string(file) + ":" + std::to_string(line)
                + "]: " + message;
    }

    ~LihowarIOException() = default;

};

}


#endif //LIHOWAR_LIHOWARIOEXCEPTION_HPP
