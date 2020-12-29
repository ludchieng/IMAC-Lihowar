/*
 *  Copyright (c) 2020-2021 Lihowar
 *
 *  This software is licensed under OSEF License.
 *
 *  The "Software" is defined as the pieces of code, the documentation files, the config
 *  files, the textures assets, the Wavefront OBJ assets, the screenshot image, the sound
 *  effects and music associated with.
 *
 *  This Software is licensed under OSEF License which means IN ACCORDANCE WITH THE LICENSE
 *  OF THE DEPENDENCIES OF THE SOFTWARE, you can use it as you want for any purpose, but
 *  it comes with no guarantee of any kind, provided that you respects the license of the
 *  software dependencies of the piece of code you want to reuse. The dependencies are
 *  listed at the end of the README given in the directory root of the Lihowar repository.
 */
#include <lihowarlib/Texture.hpp>
#include <lihowarlib/exceptions/LihowarException.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

const map<TextureName, string> Texture::PATHS = {
        { TextureName::SKY                     , "skybox.jpg"                     },
        { TextureName::BEACON1_DIFF            , "beacons/beacon1_diff.png"       },
        { TextureName::BEACON1_LUMIN           , "beacons/beacon1_lumin.png"      },
        { TextureName::BEACON2_DIFF            , "beacons/beacon2_diff.png"       },
        { TextureName::BEACON2_LUMIN           , "beacons/beacon2_lumin.png"      },
        { TextureName::AIRSHIP_BALLOON_DIFF    , "airship/1k/balloon_diff.png"    },
        { TextureName::AIRSHIP_BALLOON_AO      , "airship/1k/balloon_ao.png"      },
        { TextureName::AIRSHIP_BALLOON_NORMAL  , "airship/1k/balloon_normal.png"  },
        { TextureName::AIRSHIP_NACELLE_DIFF    , "airship/1k/nacelle_diff.png"    },
        { TextureName::AIRSHIP_NACELLE_AO      , "airship/1k/nacelle_ao.png"      },
        { TextureName::AIRSHIP_NACELLE_NORMAL  , "airship/1k/nacelle_normal.png"  },
        { TextureName::AIRSHIP_WOODFLOOR_DIFF  , "airship/1k/woodfloor_diff.png"  },
        { TextureName::AIRSHIP_WOODFLOOR_AO    , "airship/1k/woodfloor_ao.png"    },
        { TextureName::PENTABALL_DIFF          , "pentaball/1k/pentaball_diff.png"   },
        { TextureName::PENTABALL_AO            , "pentaball/1k/pentaball_ao.png"     },
        { TextureName::PENTABALL_NORMAL        , "pentaball/1k/pentaball_normal.png" },
        { TextureName::PENTABALL_LUMIN         , "pentaball/1k/pentaball_lumin.png"  },
        { TextureName::PENTABALL_SPEC          , "pentaball/1k/pentaball_spec.png"   },
        { TextureName::PLATEFORM_DIFF          , "plateform/1k/plateform_diff.png"   },
        { TextureName::PLATEFORM_AO            , "plateform/1k/plateform_ao.png"     },
        { TextureName::PLATEFORM_NORMAL        , "plateform/1k/plateform_normal.png" },
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

    if (cfg::DEBUG) cout <<"[Texture::"<<__func__<<"] successfully loaded texture at: " << getPath(texName) << endl;
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
