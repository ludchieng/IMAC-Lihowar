#ifndef LIHOWAR_LIHOWAREXCEPTION_HPP
#define LIHOWAR_LIHOWAREXCEPTION_HPP

#include <exception>
#include <cstdlib>
#include <string>

namespace lihowar {

class LihowarException : public std::exception {

protected:
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
    inline const char* what() const noexcept override
    {
        std::cerr << "LihowarException: ";
        std::cerr << "[" << _file << ":" << std::to_string(_line) << "]" << std::endl;
        return _message.c_str();
    };

};

}


#endif //LIHOWAR_LIHOWAREXCEPTION_HPP
