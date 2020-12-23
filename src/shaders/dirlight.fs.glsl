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
