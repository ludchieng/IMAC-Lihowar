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
#include <iostream>
#include <glimac/Image.hpp>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <GL/glew.h>

using namespace std;
using namespace glm;


void transformImg(const string &execPath, const string &imgPath);


int main(int argc, char** argv)
{
    if (argc < 2) {
        cout << "No argument provided, exit program" << endl;
        return EXIT_SUCCESS;
    }
    for (int i = 1; i < argc; ++i) {
        cout << "------------------- "<< endl << "no. " << i << endl;
        transformImg(string(argv[0]), string(argv[i]));
        cout << endl;
    }

    return EXIT_SUCCESS;
}


string getFileName(const string& s)
{
    char sep = '/';
#ifdef _WIN32
    sep = '\\';
#endif
    size_t i = s.rfind(sep, s.length());
    if (i != string::npos)
        return(s.substr(i+1, s.length() - i));

    return s;
}


string getDirectory(const string &s)
{
    return s.substr(0, s.find_last_of("\\/"));
}


void transformImg(const string &execPath, const string &imgPath)
{
    // Path name parsing
    string execDir = getDirectory(execPath); // Removes file name
    string imgName = getFileName(imgPath);

    cout << "imgPath: " << execPath + imgPath << endl;
    cout << "imgName: " << imgName << endl;

    // Load image
    std::unique_ptr<glimac::Image> img = loadImage(glimac::FilePath(imgPath));

    cout << "size: " << img->getWidth() << "x" << img->getHeight() << endl;

    unsigned int size = img->getWidth() * img->getHeight();
    auto *result = new uint8_t[size * 4]; // resulting image

    // Normal rotation matrix
    mat4 transform = mat4(1.);
    transform = rotate( mat4(1.), M_PI_2f32, vec3(1.f, 0.f, 0.f) ) * transform;
    transform = rotate( mat4(1.), M_PIf32, vec3(0.f, 1.f, 0.f) ) * transform;

    // Apply transformation on each pixel
    unsigned int j = 0;
    for (unsigned int i = 0; i < size; i++) {
        glm::vec4 px = img->getPixels()[i];
        // Center values around between -1 and 1
        px = px * vec4(2., 2., 2., 1.);
        px = px - vec4(1., 1., 1., 0.);
        // Apply transformation
        px = transform * px;
        // Back to previous format
        px = px + vec4(1., 1., 1., 0.);
        px = px * vec4(.5, .5, .5, 1.);
        // Converting from float to uint
        result[j++] = (uint8_t) (px.r * 255.99f);
        result[j++] = (uint8_t) (px.g * 255.99f);
        result[j++] = (uint8_t) (px.b * 255.99f);
        result[j++] = (uint8_t) (px.a * 255.99f);
    }

    // Write image
    stbi_write_png(
            imgName.c_str(),
            (uint) img->getWidth(),
            (uint) img->getHeight(),
            4,
            result,
            (uint) (img->getWidth() * 4));
}
