#version 400 core

#include "common"

#ifdef USE_VECTOR_COLOR
#ifdef USE_COLOR_ALPHA
in vec4 frag_color;
#else
in vec3 frag_color;
#endif
#endif

#ifdef USE_VECTOR_UVS
in vec2 frag_uv;
#endif

#ifdef USE_TEXTURE0
uniform sampler2D texture0;
#endif

void main() {
    #ifdef USE_VECTOR_COLOR
    #ifdef USE_COLOR_ALPHA
    gl_FragColor = frag_color;
    #else
    gl_FragColor = vec4(frag_color, 1.0);
    #endif
    #endif

    #if defined(USE_VECTOR_UVS) && defined(USE_TEXTURE0)
    gl_FragColor = vec4(texture(texture0, frag_uv).rgb, 1.0);
    #endif
}