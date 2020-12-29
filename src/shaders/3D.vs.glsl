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
#version 300 es

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoord;

out vec3 vFragPos;
out vec3 vFragNormal;
out vec2 vFragTexCoords;

uniform mat4 uMatMVP;
uniform mat4 uMatMV;
uniform mat4 uMatNormal;

void main() {
    vec4 vertexPos = vec4(aVertexPosition, 1.);
    vec4 vertexNorm = vec4(aVertexNormal, 0.);

    vFragPos = vec3(uMatMV * vertexPos);
    gl_Position = uMatMVP * vertexPos;
    vFragNormal = vec3(uMatNormal * vertexNorm);
    vFragTexCoords = aVertexTexCoord;
}
