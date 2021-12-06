#version 400 core

#include "common"

in vec3 position;

#ifdef USE_COLOR_ALPHA
in vec4 color;
out vec4 frag_color;
#else
in vec3 color;
out vec3 frag_color;
#endif

void main() {
    frag_color = color;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1);
}