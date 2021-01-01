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
#pragma once
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
    static std::string EXEC_PATH;
    static std::string EXEC_DIR;

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

    static std::string SCENE;

public:
    // INTERFACE
    static void load(int argc, char** argv)
    {
        EXEC_PATH = argv[0];
        EXEC_DIR = EXEC_PATH.substr(0, EXEC_PATH.find_last_of("\\/")); // Removes file name
        std::string defaultConfigFilePath = EXEC_DIR + "/config/default.json";
        std::string configFilePath = (argc > 1) ? argv[1] : defaultConfigFilePath;

        try {
            // First try with user input config file
            ConfigSerializer::load(configFilePath);
            loadValues();
        } catch (LihowarIOException &e) {
            std::cerr << e.what() << std::endl;
            std::cerr << "Falling back on default config..." << std::endl;

            try {
                // Second try with default input config file
                ConfigSerializer::load(defaultConfigFilePath);
                loadValues();
            } catch (LihowarIOException &e) {
                // Resigning on hardcoded config
                std::cerr << e.what() << std::endl;
                std::cerr << "Falling back on hardcoded config..." << std::endl;
            }

        }
    }

private:

    static void loadValues()
    {
        DEBUG                       = ConfigSerializer::get<bool>        ("debug");

        PATH_ASSETS  = EXEC_DIR+"/" + ConfigSerializer::get<std::string> ("path_assets");
        PATH_SHADERS = EXEC_DIR+"/" + ConfigSerializer::get<std::string> ("path_shaders");
        PATH_SCENES  = EXEC_DIR+"/" + ConfigSerializer::get<std::string> ("path_scenes");

        FULLSCREEN                  = ConfigSerializer::get<bool>        ("fullscreen");
        WINDOW_WIDTH                = ConfigSerializer::get<unsigned int>("window_width");
        WINDOW_HEIGHT               = ConfigSerializer::get<unsigned int>("window_height");
        ASPECT_RATIO                = WINDOW_WIDTH / (float) WINDOW_HEIGHT;

        MAX_FRAMERATE               = ConfigSerializer::get<float>       ("max_framerate");

        MIN_FOV                     = ConfigSerializer::get<float>       ("min_fov");
        MAX_FOV                     = ConfigSerializer::get<float>       ("max_fov");

        Z_NEAR                      = ConfigSerializer::get<float>       ("z_near");
        Z_FAR                       = ConfigSerializer::get<float>       ("z_far");

        USE_ANTIALIASING            = ConfigSerializer::get<bool>        ("use_antialiasing");
        MSAA                        = ConfigSerializer::get<unsigned int>("msaa");

        SCENE                       = ConfigSerializer::get<std::string> ("scene");
    }
};

}


#endif //LIHOWAR_GAMECONFIG_HPP
