#include "Log.h"
#include <stdarg.h>

void Ni_PrintMessage(const char *format, ...) {}

void Ni_PrintToFile(FILE *s, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(s, format, args);
    va_end(args);
}

void Ni_PrintError(ni_file_context_t context, const char *format, ...)
{
    fprintf(stderr, "\033[31mError from %s() in %s on line %d.\nDetails: ",
            context.function_name, context.file_name, context.line);

    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    fprintf(stderr, "\033[0m\n");
}
