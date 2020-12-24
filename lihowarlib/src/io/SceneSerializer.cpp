#include <lihowarlib/io/SceneSerializer.hpp>
#include <fstream>
#include <sstream>
#include <tao/json.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

void SceneSerializer::save(const Scene &s)
{
    string filename("scene1");
    ofstream f;
    f.open(PATH_SCENES + filename, ofstream::out | ofstream::trunc);

    if (!f.is_open())
        throw LihowarIOException("Scene saving failed at: " + PATH_SCENES + filename, __FILE__, __LINE__);

    f << "LIHOWAR\n";
    f << "Scene:\n\n";

    f << "GameObjects:\n";
    auto itgo = s.objects().begin();
    while (itgo != s.objects().end()) {
        f << serialize(**itgo);
        f << "\n";
        ++itgo;
    }

    f << "Lights:\n";
    auto itl = s.lights().begin();
    while (itl != s.lights().end()) {
        f << serialize(**itl);
        ++itl;
    }

    f.close();
}

void SceneSerializer::load(Scene &s)
{
    fstream f;
    f.open("tpoint.txt",ios::in);
    if (f.is_open()){
        string tp;
        while(getline(f, tp)){
            cout << tp << "\n";
        }
        f.close();
    }
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