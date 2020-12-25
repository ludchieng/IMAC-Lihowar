#include <lihowarlib/Texture.hpp>
#include <lihowarlib/exceptions/LihowarException.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

Texture::Texture(TextureName textureName)
    :_textureName(textureName)
{
    string filename;

    // Get texture name from TextureName
    switch (_textureName) {
        case TextureName::SKY:
            filename = "skybox.jpg";
            break;
        case TextureName::BEACON1_DIFF:
            filename = "beacon1_diff.png";
            break;
        case TextureName::BEACON1_LUMIN:
            filename = "beacon1_lumin.png";
            break;
        default:
            break;
    }
    _img = glimac::loadImage(cfg::PATH_ASSETS + "textures/" + filename);

    if (_img == nullptr)
        throw LihowarException("Image loading failed:" + filename, __FILE__, __LINE__);

    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA,
        _img->getWidth(), _img->getHeight(),
        0, GL_RGBA, GL_FLOAT,
        _img->getPixels()
    );
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &_id);
}

}