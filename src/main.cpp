#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/glm.hpp>
#include <GL/glew.h>
#include <iostream>
#include <cstddef>
#include <vector>

using namespace glimac;

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 800;

const unsigned int LUNES_COUNT = 32;


void loadImg(GLuint &idTex, const char* path);


struct EarthProg {
    Program m_prog;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uDiffuse1;
    GLint uDiffuse2;

    EarthProg(const FilePath& appPath):
            m_prog(loadProgram(appPath.dirPath() + "shaders/3D.vs.glsl",
                               appPath.dirPath() + "shaders/multiTex3D.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_prog.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_prog.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_prog.getGLId(), "uNormalMatrix");
        uDiffuse1 = glGetUniformLocation(m_prog.getGLId(), "uDiffuse1");
        uDiffuse2 = glGetUniformLocation(m_prog.getGLId(), "uDiffuse2");
    }
};

struct MoonProg {
    Program m_prog;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uDiffuse;

    MoonProg(const FilePath& appPath):
            m_prog(loadProgram(appPath.dirPath() + "shaders/3D.vs.glsl",
                               appPath.dirPath() + "shaders/multiTex3D.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_prog.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_prog.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_prog.getGLId(), "uNormalMatrix");
        uDiffuse = glGetUniformLocation(m_prog.getGLId(), "uDiffuse");
    }
};


int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(WIDTH, HEIGHT, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*
     * glimac
     */
    //textures
    GLuint idTexMoon, idTexEarth, idTexClouds;
    loadImg(idTexEarth, "../../assets/textures/earth.jpg");
    loadImg(idTexMoon, "../../assets/textures/moon.jpg");
    loadImg(idTexClouds, "../../assets/textures/clouds.jpg");

    // shaders
    FilePath applicationPath(argv[0]);
    EarthProg earthProg(applicationPath);
    MoonProg moonProg(applicationPath);


    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    earthProg.m_prog.use();
    glUniform1i(earthProg.uDiffuse1, 0);
    glUniform1i(earthProg.uDiffuse2, 1);

    FreeflyCamera cam(glm::vec3(0., 0., 5.), glm::pi<float>(), 0.);
    glm::mat4 projMatrix = glm::perspective(glm::radians(70.f), (float) WIDTH / (float) HEIGHT, .1f, 100.f);

    // Vertices
    Sphere s = Sphere(1, 32, 32);
    std::vector<glm::vec3> lunesAxis(LUNES_COUNT);
    std::vector<glm::vec3> lunesAltitude(LUNES_COUNT);
    std::vector<glm::vec3> lunesRadius(LUNES_COUNT);

    for (size_t i = 0; i < LUNES_COUNT; ++i) {
        lunesAxis[i] = (glm::sphericalRand(1.f));
        lunesAltitude[i] = (glm::sphericalRand(2.f));
    }

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, s.getVertexCount()*sizeof(ShapeVertex),
                 s.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_UV = 2;
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_UV);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE,
                          sizeof(ShapeVertex), (GLvoid*)(offsetof(ShapeVertex, position)));

    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE,
                          sizeof(ShapeVertex), (GLvoid*)(offsetof(ShapeVertex, normal)));

    glVertexAttribPointer(VERTEX_ATTR_UV, 2, GL_FLOAT, GL_FALSE,
                          sizeof(ShapeVertex), (GLvoid*)(offsetof(ShapeVertex, texCoords)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);

    // Application loop:
    int mouseX, mouseY, lastMouseX = -1, lastMouseY = -1;
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if (e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        cam.rotateLeft(1);
                        break;
                    case SDLK_RIGHT:
                        cam.rotateLeft(-1);
                        break;
                    case SDLK_UP:
                        cam.moveFront(1);
                        break;
                    case SDLK_DOWN:
                        cam.moveFront(-1);
                        break;
                }
            }
        }

        if (SDL_GetMouseState(&mouseX, &mouseY) == 4) { // mouse button right is pressed
            if (lastMouseX != -1)
                cam.rotateLeft(.1 * (lastMouseX - mouseX));
            if (lastMouseY != -1)
                cam.rotateUp(.1 * (lastMouseY - mouseY));
        }
        lastMouseX = mouseX;
        lastMouseY = mouseY;

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 globalMVMatrix = cam.getViewMatrix();
        glm::mat4 earthMVMatrix = glm::rotate(globalMVMatrix, windowManager.getTime(), glm::vec3(0, 1, 0)); // rotates around its axis

        earthProg.m_prog.use();
        glUniformMatrix4fv(earthProg.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * earthMVMatrix));
        glUniformMatrix4fv(earthProg.uMVMatrix, 1, GL_FALSE, glm::value_ptr(earthMVMatrix));
        glUniformMatrix4fv(earthProg.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(earthMVMatrix))));

        glBindVertexArray(vao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, idTexEarth);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, idTexClouds);
        glDrawArrays(GL_TRIANGLES, 0, s.getVertexCount());
        glBindTexture(GL_TEXTURE_2D, 0);

        // Draw lunes
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, idTexMoon);
        moonProg.m_prog.use();
        glm::mat4 moonMVMatrix;
        for (unsigned int i = 0; i < LUNES_COUNT; i++) {
            moonMVMatrix = globalMVMatrix;
            moonMVMatrix = glm::rotate(moonMVMatrix, windowManager.getTime(), lunesAxis[i]); // rotation around parent
            moonMVMatrix = glm::translate(moonMVMatrix, lunesAltitude[i]); // altitude from parent
            moonMVMatrix = glm::scale(moonMVMatrix, glm::vec3(0.2, 0.2, 0.2)); // downscaling
            glUniformMatrix4fv(moonProg.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * moonMVMatrix));
            glUniformMatrix4fv(moonProg.uMVMatrix, 1, GL_FALSE, glm::value_ptr(moonMVMatrix));
            //glUniformMatrix4fv(moonProg.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(moonMVMatrix))));
            glDrawArrays(GL_TRIANGLES, 0, s.getVertexCount());
        }

        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteTextures(1, &idTexEarth);
    glDeleteTextures(1, &idTexMoon);
    glDeleteTextures(1, &idTexClouds);

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}




void loadImg(GLuint &idTex, const char* path) {
    std::unique_ptr<Image> img = loadImage(path);
    if (img == NULL) {
        std::cerr << "Failed to load texture" << std::endl;
        exit(-1);
    }
    glGenTextures(1, &idTex);
    glBindTexture(GL_TEXTURE_2D, idTex);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->getWidth(),img->getHeight(),
                 0, GL_RGBA, GL_FLOAT, img->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}