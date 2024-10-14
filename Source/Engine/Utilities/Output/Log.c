#include "Log.h"
#include <stdarg.h>

void Ni_PrintMessage(ni_file_context_t context, const char *format, ...)
{
    printf("\033[34m---\nMessage from %s() in %s on line %d:\n",
           context.function_name, context.file_name, context.line);

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    printf("\n---\033[0m\n");
}

void Ni_PrintError(ni_file_context_t context, const char *format, ...)
{
    fprintf(stderr, "\033[31m---\nError from %s() in %s on line %d:\n",
            context.function_name, context.file_name, context.line);

    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    fprintf(stderr, "\n---\033[0m\n");
}

void Ni_PrintToFile(FILE *s, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(s, format, args);
    va_end(args);
}
