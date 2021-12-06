#version 400 core

#include "common"

#ifdef USE_COLOR_ALPHA
in vec4 frag_color;
#else
in vec3 frag_color;
#endif

void main() {
    #ifdef USE_COLOR_ALPHA
    gl_FragColor = frag_color;
    #else
    gl_FragColor = vec4(frag_color, 1.0);
    #endif
}