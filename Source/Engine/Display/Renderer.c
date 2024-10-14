#include "Renderer.h"
#include <ErrorHandling/ErrorID.h>
#include <Utilities/Macros.h>

bool Ni_CreateRenderer(ni_renderer_t *renderer, const char **shaders)
{
    if (renderer == NULL)
    {
        Ni_SetErrorID(missing_parameter, true, NINOVIUM_DEFAULT_FC);
        return false;
    }

    if (shaders == NULL) return true;
    const char *current_shader = shaders[0];
    for (size_t i = 0; i < NINOVIUM_LOOP_CAP && current_shader != NULL;
         i++)
    {
        //! process/load shader
        current_shader = shaders[i];
    }

    return true;
}

void Ni_SetDisplayInitRoutine(ni_renderer_t *renderer,
                              ni_display_init_t func)
{
    if (renderer == NULL)
    {
        Ni_SetErrorID(missing_parameter, true, NINOVIUM_DEFAULT_FC);
        return;
    }
    renderer->display_routines.init = func;
}

void Ni_SetDisplayRunRoutine(ni_renderer_t *renderer,
                             ni_display_run_t func)
{
    if (renderer == NULL)
    {
        Ni_SetErrorID(missing_parameter, true, NINOVIUM_DEFAULT_FC);
        return;
    }
    renderer->display_routines.run = func;
}

void Ni_SetDisplayKillRoutine(ni_renderer_t *renderer,
                              ni_display_kill_t func)
{
    if (renderer == NULL)
    {
        Ni_SetErrorID(missing_parameter, true, NINOVIUM_DEFAULT_FC);
        return;
    }
    renderer->display_routines.kill = func;
}

void Ni_SetDisplayPointer(ni_renderer_t *renderer, void *ptr)
{
    if (renderer == NULL)
    {
        Ni_SetErrorID(missing_parameter, true, NINOVIUM_DEFAULT_FC);
        return;
    }
    renderer->display_routines.ptr = ptr;
}

bool Ni_RunDisplayInitRoutine(const ni_renderer_t *renderer)
{
    if (renderer == NULL || renderer->display_routines.init == NULL)
    {
        Ni_SetErrorID(missing_parameter, true, NINOVIUM_DEFAULT_FC);
        return false;
    }
    return renderer->display_routines.init(renderer->display_routines.ptr);
}

void Ni_RunDisplayRoutine(const ni_renderer_t *renderer)
{
    if (renderer == NULL || renderer->display_routines.run == NULL)
    {
        Ni_SetErrorID(missing_parameter, true, NINOVIUM_DEFAULT_FC);
        return;
    }
    renderer->display_routines.run(renderer->display_routines.ptr);
}

void Ni_RunDisplayKillRoutine(const ni_renderer_t *renderer)
{
    if (renderer == NULL || renderer->display_routines.kill == NULL)
    {
        Ni_SetErrorID(missing_parameter, true, NINOVIUM_DEFAULT_FC);
        return;
    }
    renderer->display_routines.kill(renderer->display_routines.ptr);
}
