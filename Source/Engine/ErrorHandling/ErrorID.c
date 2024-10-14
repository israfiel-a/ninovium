#include "ErrorID.h"

static const char *error_names[error_count] = {
    "no_error", "missing_parameter", "glfw_failure", "monitor_missing",
    "window_failure"};
static const char *error_descriptions[error_count] = {
    "no error available", "missing required parameter",
    "failed to initialize GLFW", "unable to find monitor",
    "failed to create window"};

static ni_error_t errid = {"no_error", "no error available", no_error,
                           fixed};

void Ni_SetErrorID(ni_error_code_t code, bool print,
                   ni_file_context_t context)
{
    if (code == error_count) return;
    errid = (ni_error_t){error_names[code], error_descriptions[code], code,
                         unfixed, context};

    if (print)
        Ni_PrintError(context, "%d/%s: %s\n", errid.code, errid.name,
                      errid.description);
}

const ni_error_t *Ni_GetErrorID(void) { return &errid; }

bool Ni_AttemptFix(void) { return false; }

void Ni_LogCurrentError(FILE *s)
{
    Ni_PrintToFile(s, "%s() in %s on line %d: %d/%s: %s\n",
                   errid.context.function_name, errid.context.file_name,
                   errid.context.line, errid.code, errid.name,
                   errid.description);
}
