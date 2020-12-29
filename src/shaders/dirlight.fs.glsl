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
precision mediump float;

in vec3 vFragPos;
in vec3 vFragNormal;
in vec2 vFragTexCoords;

uniform vec3 uLightIntensity;
uniform vec3 uLightDir;
uniform float uKd;
uniform float uKs;
uniform float uKa;
uniform float uShininess;

uniform bool uHasTexture;
uniform sampler2D uTexture;

out vec3 fFragColor;

vec3 blinnPhong() {
    vec3 cameraDir = normalize(-vFragPos);
    vec3 halfVector = (cameraDir + normalize(uLightDir)) * .5;
    vec3 res = uLightIntensity * (
        uKd * dot( normalize(uLightDir), normalize(vFragNormal) ) +
        uKs * pow( dot(halfVector, normalize(vFragNormal)), uShininess )  );
    return clamp(res, uKa, 1.);
}

void main() {
    vec3 light = blinnPhong();
    if (uHasTexture) {
        vec3 texture = texture(uTexture,vFragTexCoords).xyz;
        fFragColor = clamp(texture * light, uKa, 1.);
    } else {
        fFragColor = clamp(light, uKa, 1.);
    }
}
