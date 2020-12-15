#include <lihowarlib/GameObjectTextured.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

void GameObjectTextured::render()
{
    glBindTexture(GL_TEXTURE_2D, _texId);
    GameObject::render();
    glBindTexture(GL_TEXTURE_2D, 0);
}

}