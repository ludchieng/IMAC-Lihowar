#include <lihowarlib/io/SceneSerializer.hpp>
#include <tao/json.hpp>
#include <lihowarlib/exceptions/LihowarIOException.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

void SceneSerializer::save(const Scene &s)
{
    //tao::json::parse_file(configFilePath)
}

void SceneSerializer::load(Scene &s)
{
    //tao::json::parse_file(configFilePath)
}

string SceneSerializer::serialize(const Object &g)
{
    stringstream res;
    res << "{\n";
    res << "    meshname: " << (int) g._mesh._meshName << "\n";
    res << "    prs: {\n";
    res << "        pos: " << g._prs.pos() << "\n";
    res << "        rot: " << g._prs.rot() << "\n";
    res << "        sca: " << g._prs.sca() << "\n";
    res << "    }\n";
    res << "}\n";
    return res.str();
}

string SceneSerializer::serialize(const Light &l)
{
    stringstream res;
    res << "{\n";
    res << "light\n";
    res << "}\n";
    return res.str();
}

}
