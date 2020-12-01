#version 300 es
precision mediump float;

in vec3 vViewCoordPos;
in vec3 vViewCoordNormal;
in vec2 vTexCoord;

out vec3 fFragColor;

uniform sampler2D uDiffuse1;
uniform sampler2D uDiffuse2;

void main() {
    fFragColor = texture(uDiffuse1, vTexCoord).xyz;
    fFragColor += texture(uDiffuse2, vTexCoord).xyz;
}
