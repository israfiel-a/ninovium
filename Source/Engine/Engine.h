/**
 * @file Engine.h
 * @author Israfiel (https://github.com/israfiel-a)
 * @brief The base file of the Ninovium engine. This should be the only
 * file your project includes, beyond utilities and such.
 * @date 2024-10-10
 *
 * @copyright (c) 2024 - Israfiel
 * This source code is under the AGPL v3.0. For information on what that
 * means, see the attached LICENSE.md.
 */

#ifndef NINOVIUM__ENGINE_H
#define NINOVIUM__ENGINE_H

#include <Display/Renderer.h>
#include <Utilities/Input/InitArgs.h>
#include <stdbool.h>
#include <stddef.h>

bool Ni_StartEngine(const char *title, ni_init_args_t args);
void Ni_TerminateEngine(void);

bool Ni_RunEngine(void);

void Ni_ChangeDisplayInitRoutine(ni_display_init_t func);
void Ni_ChangeDisplayRoutine(ni_display_run_t func);
void Ni_ChangeDisplayKillsRoutine(ni_display_kill_t func);

#endif // NINOVIUM__ENGINE_H
