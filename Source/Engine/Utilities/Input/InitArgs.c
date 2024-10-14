#include "InitArgs.h"
#include <Utilities/Macros.h>
#include <stdio.h>

void Ni_ParseInitArgs(const char **args)
{
    if (args == NULL) return;

    const char *current_arg = NULL;
    for (size_t i = 1; i < NINOVIUM_LOOP_CAP && current_arg != NULL; i++)
    {
        printf("%s\n", current_arg);
        current_arg = args[i];
    }
}
