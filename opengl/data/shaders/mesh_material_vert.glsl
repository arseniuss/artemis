#version 400 core

#include "common"

in vec3 position;

#ifdef USE_VECTOR_COLOR
#ifdef USE_COLOR_ALPHA
in vec4 color;
out vec4 frag_color;
#else
in vec3 color;
out vec3 frag_color;
#endif
#endif

#ifdef USE_VECTOR_UVS
in vec2 uv;
out vec2 frag_uv;
#endif

void main() {
    #ifdef USE_VECTOR_COLOR
    frag_color = color;
    #endif
    
    #ifdef USE_VECTOR_UVS
    frag_uv = uv;
    #endif
    
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1);
}