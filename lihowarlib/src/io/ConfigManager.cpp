#include <lihowarlib/io/ConfigManager.hpp>
#include <tao/json.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

void ConfigManager::load(const string &filename)
{
    const tao::json::value v = tao::json::parse_file( filename + ".json" );
    string key = "Comment est votre blanquette ?";
    cout << "[ConfigManager::load] test: " << key << " -> " << v.at(key).as<string>() << endl;
    key = "On me dit le plus grand bien des harengs pommes à l’huile ?";
    cout << "[ConfigManager::load] test: " << key << " -> " << v.at(key).as<string>() << endl;
}

}