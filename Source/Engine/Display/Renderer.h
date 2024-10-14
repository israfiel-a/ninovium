#ifndef NINOVIUM__RENDERER_H
#define NINOVIUM__RENDERER_H

#include <CGLM/mat4.h>

typedef struct ni_renderer
{
    mat4 projection_matrix;
    struct ni_shader_list
    {
        unsigned int _;
        struct ni_shader_list *next;
    } shader_list;
} ni_renderer_t;

bool Ni_CreateRenderer(ni_renderer_t *renderer, const char **shaders);

#endif // NINOVIUM__RENDERER_H
