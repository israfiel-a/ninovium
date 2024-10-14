#include "Engine.h"
#include <Display/Window.h>
#include <ErrorHandling/ErrorID.h>

static ni_window_t window = {NULL, 0, 0, NULL};

bool Ni_StartEngine(const char *title, const char *args)
{
    if (title == NULL)
    {
        Ni_SetErrorID(missing_parameter, true, NINOVIUM_DEFAULT_FC);
        return false;
    }

    Ni_CreateWindow(&window, title);

    return true;
}

void Ni_TerminateEngine(void) { Ni_DestroyWindow(&window); }
