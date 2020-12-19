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

uniform float uKd;
uniform float uKs;
uniform float uShininess;

uniform bool uHasTexture;
uniform sampler2D uTexture;

uniform vec3 uLightAmbient;

uniform int uLightsDirCount;
uniform int uLightsPointCount;

uniform LightDir   uLightsDir[MAX_LIGHTSDIR_COUNT];
uniform LightPoint uLightsPoint[MAX_LIGHTSPOINT_COUNT];



vec3 blinnPhong(LightDir);
vec3 blinnPhong(LightPoint);
vec3 blinnPhongMultiLights();



void main() {
    vec3 light = uLightAmbient + blinnPhongMultiLights();
    if (uHasTexture) {
        vec3 texture = texture(uTexture,vFragTexCoords).xyz;
        fFragColor = clamp(texture * light, 0., 1.);
    } else {
        fFragColor = clamp(light, 0., 1.);
    }
/*
    float brightness = dot(fFragColor, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        fBrightColor = vec3(fFragColor);
    else
        fBrightColor = vec3(0.0, 0.0, 0.0);*/
}



vec3 blinnPhong(LightDir l) {
    vec3 wi = normalize(-l.dir);
    vec3 wo = normalize(-vFragPos);
    vec3 halfV = (wo + wi) * .5;
    vec3 res = l.intensity * (
    uKd * max(0., dot( wi, vFragNormal )) +
    uKs * pow( max(0., dot(halfV, vFragNormal)), uShininess )  );
    return res;
}

vec3 blinnPhong(LightPoint l) {
    float dist = distance(l.pos, vFragPos);
    float distSq = dist * dist;

    if (length(l.intensity) / distSq < .05)
        return vec3(0.);

    vec3 wi = normalize(l.pos-vFragPos);
    vec3 wo = normalize(-vFragPos);
    vec3 halfV = (wo + wi)*.5;
    vec3 res = l.intensity * (
    uKd * max(0., dot( wi, vFragNormal )) +
    uKs * pow( max(0., dot(halfV, vFragNormal)), uShininess )  );
    res /= distSq;
    return res;
}

vec3 blinnPhongMultiLights() {
    vec3 res = vec3(0.);

    for (int i = 0; i < uLightsDirCount; ++i)
        res += blinnPhong(uLightsDir[i]);

    for (int i = 0; i < uLightsPointCount; ++i)
        res += blinnPhong(uLightsPoint[i]);

    return clamp(res, 0., 1.);
}