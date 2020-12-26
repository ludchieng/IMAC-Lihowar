#ifndef LIHOWAR_GAMECONFIG_HPP
#define LIHOWAR_GAMECONFIG_HPP

#include <lihowarlib/io/ConfigSerializer.hpp>
#include <lihowarlib/exceptions/LihowarIOException.hpp>

namespace lihowar {

class GameConfig;

typedef GameConfig cfg;

class GameConfig {

public:
    // MEMBERS
    static bool DEBUG;

    static std::string PATH_ASSETS;
    static std::string PATH_SHADERS;
    static std::string PATH_SCENES;

    static bool FULLSCREEN;
    static unsigned int WINDOW_WIDTH;
    static unsigned int WINDOW_HEIGHT;
    static float ASPECT_RATIO;

    static float MAX_FRAMERATE;

    static float MIN_FOV;
    static float MAX_FOV;

    static float Z_NEAR;
    static float Z_FAR;

    static bool USE_ANTIALIASING;
    static unsigned int MSAA;

public:
    // INTERFACE
    static void load(int argc, char** argv) {
        std::string execPath(argv[0]);
        std::string execDir = execPath.substr(0, execPath.find_last_of("\\/")); // Removes file name
        std::string defaultConfigFilePath = execDir + "/config/default.json";
        std::string configFilePath = (argc > 1) ? std::string(argv[1]) : defaultConfigFilePath;

        try {
            ConfigSerializer::load(configFilePath);
        } catch (LihowarIOException &e) {
            std::cerr << e.what();
            std::cerr << "Falling back on default config..." << std::endl;
            ConfigSerializer::load(defaultConfigFilePath);
        }

        DEBUG                      = ConfigSerializer::get<bool>        ("debug");

        PATH_ASSETS  = execDir+"/" + ConfigSerializer::get<std::string> ("path_assets");
        PATH_SHADERS = execDir+"/" + ConfigSerializer::get<std::string> ("path_shaders");
        PATH_SCENES  = execDir+"/" + ConfigSerializer::get<std::string> ("path_scenes");

        FULLSCREEN                 = ConfigSerializer::get<bool>        ("fullscreen");
        WINDOW_WIDTH               = ConfigSerializer::get<unsigned int>("window_height");
        WINDOW_HEIGHT              = ConfigSerializer::get<unsigned int>("window_width");
        ASPECT_RATIO               = WINDOW_WIDTH / (float) WINDOW_HEIGHT;

        MAX_FRAMERATE              = ConfigSerializer::get<float>       ("max_framerate");

        MIN_FOV                    = ConfigSerializer::get<float>       ("min_fov");
        MAX_FOV                    = ConfigSerializer::get<float>       ("max_fov");

        Z_NEAR                     = ConfigSerializer::get<float>       ("z_near");
        Z_FAR                      = ConfigSerializer::get<float>       ("z_far");

        USE_ANTIALIASING           = ConfigSerializer::get<bool>        ("use_antialiasing");
        MSAA                       = ConfigSerializer::get<unsigned int>("msaa");
    }
};

}


#endif //LIHOWAR_GAMECONFIG_HPP
