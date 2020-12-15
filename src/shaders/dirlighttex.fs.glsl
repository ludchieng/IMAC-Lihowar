#version 300 es
precision mediump float;

in vec3 vFragPos;
in vec3 vFragNormal;
in vec2 vFragTexCoords;

uniform vec3 uLightIntensity;
uniform vec3 uLightDir;
uniform vec3 uKd;
uniform vec3 uKs;
uniform vec3 uKa;
uniform float uShininess;

uniform sampler2D uTexture;

out vec3 fFragColor;

vec3 blinnPhong() {
    return uLightIntensity * (
        uKd * dot(uLightDir, vFragNormal)
        + uKs * pow(
                    (dot(
                        (normalize(-vFragPos.xyz) + uLightDir)/2.,
                        vFragNormal
                        )),
                    uShininess));
}

vec3 blinnPhongHardCoded() {
    vec3 cameraDir = normalize(-vFragPos);
    vec3 halfVector = (cameraDir + normalize(uLightDir)) * .5;
    return vec3(1.) * (
        .35 * dot( normalize(uLightDir), vFragNormal ) +
        .85 * pow( dot(halfVector, vFragNormal), 2. )  );
}

void main() {
    vec3 texture = texture(uTexture,vFragTexCoords).xyz;
    vec3 light = clamp(blinnPhongHardCoded(), .05f, 1.);
    fFragColor = texture + light;
}
