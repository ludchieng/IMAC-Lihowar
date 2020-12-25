#include <lihowarlib/GameConfig.hpp>

using namespace lihowar;

namespace lihowar {

bool         GameConfig::DEBUG            = true;

std::string  GameConfig::PATH_ASSETS      ("assets/");
std::string  GameConfig::PATH_SHADERS     ("shaders/");
std::string  GameConfig::PATH_SCENES      ("scenes/");

bool         GameConfig::FULLSCREEN       = false;
unsigned int GameConfig::WINDOW_WIDTH     = (cfg::FULLSCREEN) ? 1920 : 1280;
unsigned int GameConfig::WINDOW_HEIGHT    = (cfg::FULLSCREEN) ? 1080 : 720;
float        GameConfig::ASPECT_RATIO     = cfg::WINDOW_WIDTH / (float) cfg::WINDOW_HEIGHT;

float        GameConfig::MAX_FRAMERATE    = 60.f;

float        GameConfig::MIN_FOV          = 70.0f;
float        GameConfig::MAX_FOV          = 95.0f;

float        GameConfig::Z_NEAR           = .1f;
float        GameConfig::Z_FAR            = 5000.f;

bool         GameConfig::USE_ANTIALIASING = false;
unsigned int GameConfig::MSAA             = 1*2;

}