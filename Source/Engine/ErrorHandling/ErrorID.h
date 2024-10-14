/**
 * @file ErrorID.h
 * @author Israfiel (https://github.com/israfiel-a)
 * @brief Provides some getters and setters for the engine's @ref errid --
 * basically the `errno` of engine functions.
 * @date 2024-10-10
 *
 * @copyright (c) 2024 - Israfiel
 * This source code is under the AGPL v3.0. For information on what that
 * means, see the attached LICENSE.md.
 */

#ifndef NINOVIUM__ERRORID_H
#define NINOVIUM__ERRORID_H

#include <Utilities/Output/Log.h>
#include <stdbool.h>
#include <stdio.h>

typedef enum ni_error_state
{
    failed_to_fix,
    unfixed,
    fixed
} ni_error_state_t;

typedef enum ni_error_code
{
    no_error,
    missing_parameter,
    glfw_failure,
    monitor_missing,
    window_failure,
    error_count
} ni_error_code_t;

typedef struct ni_error
{
    const char *name;
    const char *description;
    ni_error_code_t code;
    ni_error_state_t state;
    ni_file_context_t context;
} ni_error_t;

void Ni_SetErrorID(ni_error_code_t code, bool print,
                   ni_file_context_t context);
const ni_error_t *Ni_GetErrorID(void);

bool Ni_AttemptFix(void);

void Ni_LogCurrentError(FILE *s);

#endif // NINOVIUM__ERRORID_H
