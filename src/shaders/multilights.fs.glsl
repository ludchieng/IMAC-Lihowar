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

/*layout (location = 0)*/ out vec3 fFragColor;
//layout (location = 1) out vec3 fBrightColor;

const int MAX_LIGHTSDIR_COUNT = 4;
const int MAX_LIGHTSPOINT_COUNT = 12;

struct LightDir {
    vec3 intensity;
    vec3 dir;
};

struct LightPoint {
    vec3 intensity;
    vec3 pos;
};

uniform highp mat4 uMatNormal;

uniform float uKd;
uniform float uKs;
uniform float uKl;
uniform float uKao;
uniform float uKn;
uniform float uShininess;

uniform bool uHasDiffuseMap;
uniform sampler2D uDiffuseMap;

uniform bool uHasSpecularMap;
uniform sampler2D uSpecularMap;

uniform bool uHasLuminMap;
uniform sampler2D uLuminMap;

uniform bool uHasAOMap;
uniform sampler2D uAOMap;

uniform bool uHasNormalMap;
uniform sampler2D uNormalMap;

uniform vec3 uLightAmbient;

uniform int uLightsDirCount;
uniform int uLightsPointCount;

uniform LightDir   uLightsDir[MAX_LIGHTSDIR_COUNT];
uniform LightPoint uLightsPoint[MAX_LIGHTSPOINT_COUNT];



vec4 centerNormal(vec4);      // convert values from [0,1] to [-1,1]
vec3 fragNormal();            // get normal vector from either vertex data interpolation or normal map
float brightness(vec3);       // get brightness of a color
vec3 blinnPhong(LightDir);
vec3 blinnPhong(LightPoint);
vec3 blinnPhongMultiLights();



void main() {
    fFragColor = uLightAmbient + blinnPhongMultiLights();
    if (uHasLuminMap)
        fFragColor = max(fFragColor, uKl * texture(uLuminMap,vFragTexCoords).xyz);

    if (uHasAOMap)
        fFragColor = fFragColor * texture(uAOMap,vFragTexCoords).xyz;

    fFragColor = clamp(fFragColor, 0., 1.);
/*
    if(brightness(fFragColor) > 1.0)
        fBrightColor = vec3(fFragColor);
    else
        fBrightColor = vec3(0.0, 0.0, 0.0);*/
}



vec4 centerNormal(vec4 normal) {
    return normal * vec4(2.,2.,2.,1.) - vec4(1.,1.,1.,0.);
}


vec3 fragNormal() {
    if (uHasNormalMap)
        return vec3(uMatNormal * centerNormal(texture(uNormalMap, vFragTexCoords)));
    else
        return vFragNormal;
}


float brightness(vec3 color) {
    return dot(fFragColor, vec3(0.2126, 0.7152, 0.0722));
}


vec3 blinnPhong(LightDir l) {

    vec3 wi = normalize(-l.dir);
    vec3 wo = normalize(-vFragPos);
    vec3 halfV = (wo + wi) * .5;
    vec3 diffuse = vec3(  uKd * max(0., dot( wi, normalize(fragNormal()) ))  );
    if (uHasDiffuseMap)
        diffuse *= texture(uDiffuseMap,vFragTexCoords).xyz;

    vec3 specular = vec3(  uKs * pow( max(0., dot(halfV, normalize(fragNormal()))), uShininess )  );
    if (uHasSpecularMap)
        specular *= texture(uSpecularMap,vFragTexCoords).xyz;

    return l.intensity * (diffuse + specular);
}


vec3 blinnPhong(LightPoint l) {
    float dist = distance(l.pos, vFragPos);
    float distSq = dist * dist;

    if (length(l.intensity) / distSq < .05)
        return vec3(0.);

    vec3 wi = normalize(l.pos-vFragPos);
    vec3 wo = normalize(-vFragPos);
    vec3 halfV = (wo + wi)*.5;
    vec3 diffuse = vec3(  uKd * max(0., dot( wi, normalize(fragNormal()) ))  );
    if (uHasDiffuseMap)
    diffuse *= texture(uDiffuseMap,vFragTexCoords).xyz;

    vec3 specular = vec3(  uKs * pow( max(0., dot(halfV, normalize(fragNormal()))), uShininess )  );
    if (uHasSpecularMap)
    specular *= texture(uSpecularMap,vFragTexCoords).xyz;

    return l.intensity * (diffuse + specular) / distSq;
}


vec3 blinnPhongMultiLights() {
    vec3 res = vec3(0.);

    for (int i = 0; i < uLightsDirCount; ++i)
        res += blinnPhong(uLightsDir[i]);

    for (int i = 0; i < uLightsPointCount; ++i)
        res += blinnPhong(uLightsPoint[i]);

    return res;
}
