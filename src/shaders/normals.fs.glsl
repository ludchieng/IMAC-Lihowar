#version 300 es
precision mediump float;

in vec3 vViewCoordPos;
in vec3 vViewCoordNormal;
in vec2 vTexCoord;

out vec3 fFragColor;

void main() {
    fFragColor = normalize(vViewCoordNormal);
}