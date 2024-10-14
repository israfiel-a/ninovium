/**
 * @file Log.h
 * @author Israfiel (https://github.com/israfiel-a)
 * @brief Provides basic functionality for formatted and colored output
 * logs of various purposes. These logs can be sent to an in-game console
 * as well via the @ref BindConsole interface.
 * @date 2024-10-10
 *
 * @copyright (c) 2024 - Israfiel
 * This source code is under the AGPL v3.0. For information on what that
 * means, see the attached LICENSE.md.
 */

#ifndef NINOVIUM__LOG_H
#define NINOVIUM__LOG_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef struct ni_file_context
{
    const char *file_name;
    const char *function_name;
    uint32_t line;
} ni_file_context_t;

#define NINOVIUM_DEFAULT_FC                                               \
    (ni_file_context_t) { FILENAME, __func__, __LINE__ }

void Ni_PrintMessage(const char *format, ...);
void Ni_PrintToFile(FILE *s, const char *format, ...);

void Ni_PrintError(ni_file_context_t context, const char *format, ...);

#endif // NINOVIUM__LOG_H
