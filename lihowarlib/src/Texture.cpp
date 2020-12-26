#include <lihowarlib/Texture.hpp>
#include <lihowarlib/exceptions/LihowarException.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

const map<TextureName, string> Texture::PATHS = {
        { TextureName::SKY,           "skybox.jpg" },
        { TextureName::BEACON1_DIFF,  "beacon1_diff.png" },
        { TextureName::BEACON1_LUMIN, "beacon1_lumin.png" },
};


Texture::Texture(TextureName texName)
    :_textureName(texName)
{
    glimac::FilePath imgPath = cfg::PATH_ASSETS + "textures/" + getPath(texName);

    _img = glimac::loadImage(imgPath);

    if (nullptr == _img)
        throw LihowarException("Image loading failed:" + imgPath.str(), __FILE__, __LINE__);

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

    if (cfg::DEBUG) cout << "[Texture::Texture] successfully loaded texture at: " << getPath(texName) << endl;
}


Texture::~Texture()
{
    glDeleteTextures(1, &_id);
}


string &Texture::getPath(TextureName texName)
{
    try {
        return const_cast<string &>(PATHS.at(texName));
    } catch (out_of_range &e) {
        throw LihowarException("Unknown path for specified TextureName: index: " + to_string((int) texName), __FILE__, __LINE__);
    }
}

}