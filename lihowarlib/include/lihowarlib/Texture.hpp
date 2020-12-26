#ifndef LIHOWAR_TEXTURE_HPP
#define LIHOWAR_TEXTURE_HPP

#include <map>
#include <GL/glew.h>
#include <glimac/Image.hpp>
#include <lihowarlib/GameConfig.hpp>

namespace lihowar {

enum class TextureName {
    SKY, BEACON1_DIFF, BEACON1_LUMIN,
    first = SKY, last = BEACON1_LUMIN
};

class Texture {

public:
    // CONSTANTS
    static const unsigned int TEX_UNIT_DIFFUSE = 0;
    static const unsigned int TEX_UNIT_SPECULAR = 1;
    static const unsigned int TEX_UNIT_LUMIN = 2;

private:
    // CONSTANTS
    const static std::map<TextureName, std::string> PATHS;

private:
    // MEMBERS
    TextureName _textureName;
    GLuint _id;
    std::unique_ptr<glimac::Image> _img;

public:
    // CONSTRUCTORS & DESTRUCTORS
    explicit Texture(TextureName texName);
    ~Texture();
    
public:
    // INTERFACE
    GLuint &id() { return _id; }

private:
    std::string &getPath(TextureName texName);

};

}


#endif //LIHOWAR_TEXTURE_HPP
