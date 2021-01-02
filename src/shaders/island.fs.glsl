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
in vec3 vVertexPosition;
in vec3 vVertexNormal;

/*layout (location = 0)*/ out vec3 fFragColor;
//layout (location = 1) out vec3 fBrightColor;

const int MAX_LIGHTSDIR_COUNT = 4;    // must be the same in the program class
const int MAX_LIGHTSPOINT_COUNT = 12; // must be the same in the program class

struct LightDir {
    vec3 intensity;
    vec3 dir;
};

struct LightPoint {
    vec3 intensity;
    vec3 pos;
};

uniform float uKd;
uniform float uKs;
uniform float uShininess;

uniform vec3 uLightAmbient;

uniform int uLightsDirCount;
uniform int uLightsPointCount;

uniform LightDir   uLightsDir[MAX_LIGHTSDIR_COUNT];
uniform LightPoint uLightsPoint[MAX_LIGHTSPOINT_COUNT];



float brightness(vec3);       // get brightness of a color
vec3 blinnPhong(LightDir, vec3 fragNormal);
vec3 blinnPhong(LightPoint, vec3 fragNormal);
vec3 blinnPhongMultiLights(vec3 fragNormal);

float noise(vec3);



void main() {
    vec3 wi = normalize(-uLightsDir[0].dir);
    vec3 wo = normalize(-vFragPos);
    vec3 halfV = (wo + wi) * .5;
    vec3 fragNormal = normalize(vFragNormal);
    fFragColor =        vVertexNormal.y *  .1 * vec3(1.,  1. , 1. ) + .1;
    fFragColor +=       vVertexNormal.x *  .1 * vec3( .5, 0. ,  .5) + .1;
    fFragColor +=       vVertexNormal.z *  .1 * vec3( .6,  .5, 0. ) + .1;
    fFragColor += clamp(vVertexNormal.y *  .5 * vec3(1. , 1. ,  .5), 0., 1.);
    fFragColor *= vec3(1.05, 0.9, 1.0);

    vec3 sand = dot(fragNormal, -wo) *  .2 * vec3(.8, .8, .8) + .2;
    sand *= noise(vec3(1., 25., 1.) * vVertexPosition) * vec3(1.9);
    sand *= noise(vec3(11.,10.,12.) * vVertexPosition) * vec3(1.2) + .5;
    sand *= vec3(.92, .85, .8) * 2.5;
    sand *= dot(halfV, fragNormal);

    fFragColor += clamp(sand, 0., 1.);
    fFragColor *= (uLightAmbient + blinnPhongMultiLights(fragNormal));
    fFragColor = clamp(fFragColor, 0., 1.);
/*
    if(brightness(fFragColor) > 1.0)
        fBrightColor = vec3(fFragColor);
    else
        fBrightColor = vec3(0.0, 0.0, 0.0);*/
}




float brightness(vec3 color) {
    return dot(fFragColor, vec3(0.2126, 0.7152, 0.0722));
}




vec3 blinnPhong(LightDir l, vec3 fragNormal) {
    vec3 wi = normalize(-l.dir);
    vec3 wo = normalize(-vFragPos);
    vec3 halfV = (wo + wi) * .5;
    vec3 diffuse = vec3(  uKd * max(0., dot( wi, fragNormal ))  );
    vec3 specular = vec3(  uKs * pow( max(0., dot(halfV, fragNormal)), uShininess )  );
    return l.intensity * (diffuse + specular);
}


vec3 blinnPhong(LightPoint l, vec3 fragNormal) {
    float dist = distance(l.pos, vFragPos);
    float distSq = dist * dist;

    if (length(l.intensity) / distSq < .05)
        return vec3(0.);

    vec3 wi = normalize(l.pos-vFragPos);
    vec3 wo = normalize(-vFragPos);
    vec3 halfV = (wo + wi)*.5;
    vec3 diffuse = vec3(  uKd * max(0., dot( wi, fragNormal ))  );
    vec3 specular = vec3(  uKs * pow( max(0., dot(halfV, fragNormal)), uShininess )  );
    return l.intensity * (diffuse + specular) / distSq;
}


vec3 blinnPhongMultiLights(vec3 fragNormal) {
    vec3 res = vec3(0.);

    for (int i = 0; i < uLightsDirCount; ++i)
        res += blinnPhong(uLightsDir[i], fragNormal);

    for (int i = 0; i < uLightsPointCount; ++i)
        res += blinnPhong(uLightsPoint[i], fragNormal);

    return res;
}




float mod289(float x){return x - floor(x * (1.0 / 289.0)) * 289.0;}
vec4 mod289(vec4 x){return x - floor(x * (1.0 / 289.0)) * 289.0;}
vec4 perm(vec4 x){return mod289(((x * 34.0) + 1.0) * x);}

float noise(vec3 p){
    vec3 a = floor(p);
    vec3 d = p - a;
    d = d * d * (3.0 - 2.0 * d);

    vec4 b = a.xxyy + vec4(0.0, 1.0, 0.0, 1.0);
    vec4 k1 = perm(b.xyxy);
    vec4 k2 = perm(k1.xyxy + b.zzww);

    vec4 c = k2 + a.zzzz;
    vec4 k3 = perm(c);
    vec4 k4 = perm(c + 1.0);

    vec4 o1 = fract(k3 * (1.0 / 41.0));
    vec4 o2 = fract(k4 * (1.0 / 41.0));

    vec4 o3 = o2 * d.z + o1 * (1.0 - d.z);
    vec2 o4 = o3.yw * d.x + o3.xz * (1.0 - d.x);

    return o4.y * d.y + o4.x * (1.0 - d.y);
}