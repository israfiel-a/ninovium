#ifndef NINOVIUM__RENDERER_H
#define NINOVIUM__RENDERER_H

#include <CGLM/mat4.h>

typedef bool (*ni_display_init_t)(void *ptr);
typedef void (*ni_display_run_t)(void *ptr);
typedef void (*ni_display_kill_t)(void *ptr);

typedef struct ni_renderer
{
    mat4 projection_matrix;
    struct ni_shader_list
    {
        unsigned int _;
        struct ni_shader_list *next;
    } shader_list;
    struct ni_display_routines
    {
        ni_display_init_t init;
        ni_display_run_t run;
        ni_display_kill_t kill;
        void *ptr;
    } display_routines;
} ni_renderer_t;

bool Ni_CreateRenderer(ni_renderer_t *renderer, const char **shaders);

void Ni_SetDisplayInitRoutine(ni_renderer_t *renderer,
                              ni_display_init_t func);
void Ni_SetDisplayRunRoutine(ni_renderer_t *renderer,
                             ni_display_run_t func);
void Ni_SetDisplayKillRoutine(ni_renderer_t *renderer,
                              ni_display_kill_t func);

void Ni_SetDisplayPointer(ni_renderer_t *renderer, void *ptr);

bool Ni_RunDisplayInitRoutine(const ni_renderer_t *renderer);
void Ni_RunDisplayRoutine(const ni_renderer_t *renderer);
void Ni_RunDisplayKillRoutine(const ni_renderer_t *renderer);

#endif // NINOVIUM__RENDERER_H
