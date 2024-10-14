#include "Engine.h"
#include <Display/Window.h>
#include <ErrorHandling/ErrorID.h>
#include <Utilities/Input/InitArgs.h>

static ni_window_t window = {NULL, 0, 0, NULL};
static ni_renderer_t renderer = {GLM_MAT4_IDENTITY_INIT, {0, NULL}};

static bool default_init(void *ptr);
static void default_run(void *ptr);
static void default_kill(void *ptr);

bool Ni_StartEngine(const char *title, ni_init_args_t args)
{
    if (title == NULL)
    {
        Ni_SetErrorID(missing_parameter, true, NINOVIUM_DEFAULT_FC);
        return false;
    }

    Ni_ParseInitArgs(args);

    Ni_CreateWindow(&window, title);
    Ni_CreateRenderer(&renderer, NULL);

    Ni_SetDisplayInitRoutine(&renderer, default_init);
    Ni_SetDisplayRunRoutine(&renderer, default_run);
    Ni_SetDisplayKillRoutine(&renderer, default_kill);

    return true;
}

void Ni_TerminateEngine(void) { Ni_DestroyWindow(&window); }

bool Ni_RunEngine(void)
{
    if (!Ni_RunDisplayInitRoutine(&renderer)) return false;
    while (Ni_WindowStillOpen(&window))
    {
        Ni_RunDisplayRoutine(&renderer);
        Ni_UpdateWindow(&window);
    }

    Ni_RunDisplayKillRoutine(&renderer);
    return true;
}

void Ni_ChangeDisplayInitRoutine(ni_display_init_t func)
{
    Ni_SetDisplayInitRoutine(&renderer, func);
}

void Ni_ChangeDisplayRoutine(ni_display_run_t func)
{
    Ni_SetDisplayRunRoutine(&renderer, func);
}

void Ni_ChangeDisplayKillsRoutine(ni_display_kill_t func)
{
    Ni_SetDisplayKillRoutine(&renderer, func);
}

static bool default_init(void *ptr)
{
    Ni_PrintMessage(
        NINOVIUM_DEFAULT_FC,
        "Custom display init routine not configured. Pointer assigned: %p",
        ptr);
    return true;
}

static void default_run(void *ptr)
{
    (void)ptr;
    return;
}

static void default_kill(void *ptr)
{
    Ni_PrintMessage(
        NINOVIUM_DEFAULT_FC,
        "Custom display kill routine not configured. Pointer assigned: %p",
        ptr);
    return;
}
