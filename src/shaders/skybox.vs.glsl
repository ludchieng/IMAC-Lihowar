#version 300 es

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoord;

out vec3 vFragPos;
out vec3 vFragNormal;
out vec2 vFragTexCoords;

uniform mat4 uMatMVP;
uniform mat4 uMatMV;
uniform mat4 uMatNormal;

void main() {
    vec4 vertexPos = vec4(aVertexPosition, 1.);
    vec4 vertexNorm = vec4(aVertexNormal, 0.);

    vFragPos = vec3(uMatMV * vertexPos);
    gl_Position = uMatMVP * (vertexPos - vertexNorm * .005); // minus vertexNorm to prevent holes between faces
    vFragNormal = vec3(uMatNormal * vertexNorm);
    vFragTexCoords = aVertexTexCoord;
}
