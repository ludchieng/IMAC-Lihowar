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
#include <lihowarlib/io/SceneSerializer.hpp>
#include <tao/json.hpp>
#include <lihowarlib/exceptions/LihowarIOException.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

unique_ptr<Scene> SceneSerializer::load(const string &sceneFilePath)
{
    if (cfg::DEBUG) cout << "[SceneSerializer::load] START" << endl;
    auto res = unique_ptr<Scene>(new Scene());
    tao::json::value data = tao::json::parse_file(sceneFilePath);

    if (nullptr != data.find("objects"))
        deserializeArrayIntoList<Object>(data.at("objects"), res->objects());

    if (nullptr != data.find("islands"))
        deserializeArrayIntoVector<Island>(data.at("islands"), res->islands());

    if (cfg::DEBUG) cout << "[SceneSerializer::load] END" << endl;
    return res;
}


template<typename T>
void SceneSerializer::deserializeArrayIntoList(
        const tao::json::value &data,
        std::list<std::unique_ptr<T>> &destList)
{
    vector<tao::json::value> objects = data.get_array();

    auto it = objects.begin();
    while (it != objects.end()) {
        try {

            destList.push_back(
                    static_cast<unique_ptr<T>>(
                            dynamic_cast<T*>(&deserializeObject(*it)) ));

        } catch (exception &e) {
            cerr << e.what() << endl;
            cerr << "This object will be ignored" << endl << endl;
        }
        ++it;
    }
}


template<typename T>
void SceneSerializer::deserializeArrayIntoVector(
        const tao::json::value &data,
        std::vector<std::unique_ptr<T>> &destVector)
{
    vector<tao::json::value> objects = data.get_array();

    auto it = objects.begin();
    while (it != objects.end()) {
        try {

            destVector.push_back(
                    static_cast<unique_ptr<T>>(
                            dynamic_cast<T*>(&deserializeObject(*it)) ));

        } catch (exception &e) {
            cerr << e.what() << endl;
            cerr << "This object will be ignored" << endl << endl;
        }
        ++it;
    }
}


Object &SceneSerializer::deserializeObject(const tao::json::value &data)
{
    Object *res;
    string dType = format(data.at("type").get_string());

    // TODO might find a way to refactor this, thought, hurts my eyes
    if     (dType == "island") res = static_cast<Object*>( &deserializeIsland(data) );
    else if (dType == "beacon") res = static_cast<Object*>( &deserializeBeacon(data) );
    else if (dType == "pentaball") res = static_cast<Object*>( &deserializePentaball(data) );
    else if (dType == "plateform") res = static_cast<Object*>( &deserializePlateform(data) );
    else    throw LihowarIOException("Invalid object type: " + dType, __FILE__, __LINE__);

    if (nullptr != data.find("subobjects")) {
        deserializeArrayIntoList(data.at("subobjects"), res->subobjects());
    }

    return *res;
}


glm::vec3 SceneSerializer::deserializeVec3(const tao::json::value &data)
{
    return glm::vec3(
            data.at(0).as<float>(),
            data.at(1).as<float>(),
            data.at(2).as<float>()  );
}


Object::PRS &SceneSerializer::deserializePRS(const tao::json::value &data)
{
    glm::vec3 pos = (nullptr != data.find("pos")) ? deserializeVec3(data.at("pos")) : glm::vec3(0.);
    glm::vec3 rot = (nullptr != data.find("rot")) ? deserializeVec3(data.at("rot")) : glm::vec3(0.);
    glm::vec3 sca = (nullptr != data.find("sca")) ? deserializeVec3(data.at("sca")) : glm::vec3(1.);
    return *new Object::PRS(pos, rot, sca);
}


Material &SceneSerializer::deserializeMaterial(const tao::json::value &data)
{
    GLuint diff =   getTexId(data, "diff"  );
    GLuint spec =   getTexId(data, "spec"  );
    GLuint lumin =  getTexId(data, "lumin" );
    GLuint ao =     getTexId(data, "ao"    );
    GLuint normal = getTexId(data, "normal");
    return *new Material(diff, spec, lumin, ao, normal);
}


Island &SceneSerializer::deserializeIsland(const tao::json::value &data)
{
    MeshName meshName;
    string dMeshName = format(data.at("meshName").get_string());

    if      (dMeshName == "island1") meshName = MeshName::ISLAND1;
    else if (dMeshName == "island2") meshName = MeshName::ISLAND2;
    else    throw LihowarIOException("Invalid island meshname type: " + dMeshName, __FILE__, __LINE__);

    return *new Island(
            meshName,
            deserializePRS(data.at("prs"))  );
}


Beacon &SceneSerializer::deserializeBeacon(const tao::json::value &data)
{
    MeshName meshName;
    string dMeshName = format(data.at("meshName").get_string());

    if      (dMeshName == "beacon1") meshName = MeshName::BEACON1;
    else    throw LihowarIOException("Invalid island meshname type: " + dMeshName, __FILE__, __LINE__);

    return *new Beacon(
            meshName,
            deserializeMaterial(data.at("material")),
            deserializePRS(data.at("prs"))  );
}


Pentaball &SceneSerializer::deserializePentaball(const tao::json::value &data)
{
    return *new Pentaball(deserializePRS(data.at("prs")));
}


Plateform &SceneSerializer::deserializePlateform(const tao::json::value &data)
{
    return *new Plateform(deserializePRS(data.at("prs")));
}


GLuint SceneSerializer::getTexId(const tao::json::value &data, const string &key)
{
    string dTex;
    try {
        dTex = format( data.at(key).get_string() );
        if (dTex == "sky"                   ) return AssetManager::texId(TextureName::SKY                    ) ;
        if (dTex == "beacon1_diff"          ) return AssetManager::texId(TextureName::BEACON1_DIFF           ) ;
        if (dTex == "beacon1_lumin"         ) return AssetManager::texId(TextureName::BEACON1_LUMIN          ) ;
        if (dTex == "beacon2_diff"          ) return AssetManager::texId(TextureName::BEACON2_DIFF           ) ;
        if (dTex == "beacon2_lumin"         ) return AssetManager::texId(TextureName::BEACON2_LUMIN          ) ;
        if (dTex == "airship_balloon_diff"  ) return AssetManager::texId(TextureName::AIRSHIP_BALLOON_DIFF   ) ;
        if (dTex == "airship_balloon_ao"    ) return AssetManager::texId(TextureName::AIRSHIP_BALLOON_AO     ) ;
        if (dTex == "airship_balloon_normal") return AssetManager::texId(TextureName::AIRSHIP_BALLOON_NORMAL ) ;
        if (dTex == "airship_nacelle_diff"  ) return AssetManager::texId(TextureName::AIRSHIP_NACELLE_DIFF   ) ;
        if (dTex == "airship_nacelle_ao"    ) return AssetManager::texId(TextureName::AIRSHIP_NACELLE_AO     ) ;
        if (dTex == "airship_nacelle_normal") return AssetManager::texId(TextureName::AIRSHIP_NACELLE_NORMAL ) ;
        if (dTex == "airship_woodfloor_diff") return AssetManager::texId(TextureName::AIRSHIP_WOODFLOOR_DIFF ) ;
        if (dTex == "airship_woodfloor_ao"  ) return AssetManager::texId(TextureName::AIRSHIP_WOODFLOOR_AO   ) ;
        if (dTex == "pentaball_diff"        ) return AssetManager::texId(TextureName::PENTABALL_DIFF         ) ;
        if (dTex == "pentaball_ao"          ) return AssetManager::texId(TextureName::PENTABALL_AO           ) ;
        if (dTex == "pentaball_normal"      ) return AssetManager::texId(TextureName::PENTABALL_NORMAL       ) ;
        if (dTex == "pentaball_lumin"       ) return AssetManager::texId(TextureName::PENTABALL_LUMIN        ) ;
        if (dTex == "pentaball_spec"        ) return AssetManager::texId(TextureName::PENTABALL_SPEC         ) ;
        if (dTex == "plateform_diff"        ) return AssetManager::texId(TextureName::PLATEFORM_DIFF         ) ;
        if (dTex == "plateform_ao"          ) return AssetManager::texId(TextureName::PLATEFORM_AO           ) ;
        if (dTex == "plateform_normal"      ) return AssetManager::texId(TextureName::PLATEFORM_NORMAL       ) ;
        throw LihowarIOException("Invalid shader map name: " + dTex, __FILE__, __LINE__);
    } catch (LihowarIOException &e) {
        cerr << e.what() << endl;
        cerr << "No texture will be applied" << endl;
        return AssetManager::NO_TEXTURE;
    } catch (out_of_range &e) {
        return AssetManager::NO_TEXTURE;
    }
}

}
