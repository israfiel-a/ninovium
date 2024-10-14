#include "Engine.h"
#include <Display/Renderer.h>
#include <Display/Window.h>
#include <ErrorHandling/ErrorID.h>

static ni_window_t window = {NULL, 0, 0, NULL};
static ni_renderer_t renderer = {GLM_MAT4_IDENTITY_INIT, {0, NULL}};

bool init(void *ptr)
{
    (void)ptr;
    return false;
}
void run(void *ptr)
{
    (void)ptr;
    return;
}
void kill(void *ptr)
{
    (void)ptr;
    return;
}

bool Ni_StartEngine(const char *title, const char **args)
{
    if (title == NULL)
    {
        Ni_SetErrorID(missing_parameter, true, NINOVIUM_DEFAULT_FC);
        return false;
    }

    Ni_CreateWindow(&window, title);
    Ni_CreateRenderer(&renderer, NULL);

    //! make this a part of args[]
    Ni_SetDisplayInitRoutine(&renderer, init);
    Ni_SetDisplayRunRoutine(&renderer, run);
    Ni_SetDisplayKillRoutine(&renderer, kill);

    return true;
}

void Ni_TerminateEngine(void) { Ni_DestroyWindow(&window); }

bool Ni_RunEngine(void)
{
    Ni_RunDisplayInitRoutine(&renderer);
    while (Ni_WindowStillOpen(&window))
    {
        Ni_RunDisplayRoutine(&renderer);
        Ni_UpdateWindow(&window);
    }

    Ni_RunDisplayKillRoutine(&renderer);
    return true;
}
