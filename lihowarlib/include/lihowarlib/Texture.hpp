#ifndef LIHOWAR_TEXTURE_HPP
#define LIHOWAR_TEXTURE_HPP

#include <GL/glew.h>
#include <glimac/Image.hpp>
#include <lihowarlib/common.hpp>
#include <lihowarlib/exceptions/LihowarException.hpp>

namespace lihowar {

enum TextureName {
    Earth, Moon,
    TEXTURENAME_FIRST = Earth, TEXTURENAME_LAST = Moon
};

class Texture {

private:
    // MEMBERS
    TextureName _textureName;
    GLuint _id;
    std::unique_ptr<glimac::Image> _img;

public:
    // CONSTRUCTORS & DESTRUCTORS
    explicit Texture(TextureName textureId);
    ~Texture();
    
public:
    // INTERFACE
    GLuint &id() { return _id; }

};

}


#endif //LIHOWAR_TEXTURE_HPP
