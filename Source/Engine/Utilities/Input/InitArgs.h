#ifndef NINOVIUM__INITARGS_H
#define NINOVIUM__INITARGS_H

#include <stdbool.h>

typedef struct ni_init_args
{
    bool unimplemented;
} ni_init_args_t;

void Ni_ParseInitArgs(ni_init_args_t args);

#endif // NINOVIUM__INITARGS_H
