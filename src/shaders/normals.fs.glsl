#version 300 es
precision mediump float;

in vec3 vFragPos;
in vec3 vFragNormal;
in vec2 vTexCoord;

out vec3 fFragColor;

void main() {
    fFragColor = normalize(vFragNormal);
}
