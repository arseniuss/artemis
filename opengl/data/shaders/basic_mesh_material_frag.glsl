#version 400 core

#include "common"

#if defined(USE_COLOR_ALPHA)
uniform vec4 color;
#else
uniform vec3 color;
#endif

void main() {
    #if defined(USE_COLOR_ALPHA)
    gl_FragColor = color;
    #else
    gl_FragColor = vec4(color, 1.0);
    #endif
}