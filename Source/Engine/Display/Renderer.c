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
