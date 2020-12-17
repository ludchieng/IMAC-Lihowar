#version 300 es
precision mediump float;

in vec3 vFragPos;
in vec3 vFragNormal;
in vec2 vFragTexCoords;

out vec3 fFragColor;

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

uniform float uKd;
uniform float uKs;
uniform float uKa;
uniform float uShininess;

uniform bool uHasTexture;
uniform sampler2D uTexture;

uniform int uLightsDirCount;
uniform int uLightsPointCount;

uniform LightDir   uLightsDir[MAX_LIGHTSDIR_COUNT];
uniform LightPoint uLightsPoint[MAX_LIGHTSPOINT_COUNT];



vec3 blinnPhong(LightDir);
vec3 blinnPhong(LightPoint);
vec3 blinnPhongMultiLights();



void main() {
    vec3 light = blinnPhongMultiLights();
    if (uHasTexture) {
        vec3 texture = texture(uTexture,vFragTexCoords).xyz;
        fFragColor = clamp(texture * light, uKa, 1.);
    } else {
        fFragColor = clamp(light, uKa, 1.);
    }
}



vec3 blinnPhong(LightDir l) {
    vec3 wi = normalize(l.dir);
    vec3 wo = normalize(-vFragPos);
    vec3 halfV = (wo + wi) * .5;
    vec3 res = l.intensity * (
    uKd * max(0., dot( wi, vFragNormal )) +
    uKs * pow( max(0., dot(halfV, vFragNormal)), uShininess )  );
    return res;
}

vec3 blinnPhong(LightPoint l) {
    float dist = distance(l.pos, vFragPos);
    vec3 wi = normalize(l.pos-vFragPos);
    vec3 wo = normalize(-vFragPos);
    vec3 halfV = (wo + wi)*.5;
    vec3 res = l.intensity * (
    uKd * max(0., dot( wi, vFragNormal )) +
    uKs * pow( max(0., dot(halfV, vFragNormal)), uShininess )  );
    res /= (dist * dist);
    return res;
}

vec3 blinnPhongMultiLights() {
    vec3 res = vec3(0.);

    for (int i = 0; i < uLightsDirCount; ++i)
        res += blinnPhong(uLightsDir[i]);

    for (int i = 0; i < uLightsPointCount; ++i)
        res += blinnPhong(uLightsPoint[i]);

    return clamp(res, uKa, 1.);
}