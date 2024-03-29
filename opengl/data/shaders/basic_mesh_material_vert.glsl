#version 400 core

#include "common"

in vec3 position;

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1);
}