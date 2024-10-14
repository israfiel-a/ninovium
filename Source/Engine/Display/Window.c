/**
 * @file Window.c
 * @author Israfiel (https://github.com/israfiel-a)
 * @brief Implements the layer of abstraction Ninovium puts between the
 * game and GLFW. This includes creation, deletion, and some limited
 * setters.
 * @implements Window.h
 * @date 2024-10-07
 *
 * @copyright (c) 2024 - Israfiel
 * This source code is under the AGPL v3.0. For information on what that
 * entails, please see the attached @file LICENSE.md file.
 */

#include "Window.h"                // Public interface parent
#include <ErrorHandling/ErrorID.h> // Error logging
#include <Platform.h>              // Platform macros

#include <stdlib.h> // Standard memory allocation
#include <string.h> // Standard string utilities

bool Ni_CreateWindow(ni_window_t *window, const char *title)
{
    if (window == NULL)
    {
        Ni_SetErrorID(missing_parameter, true, NINOVIUM_DEFAULT_FC);
        return false;
    }

#if defined(NINOVIUM_WAYLAND)
    glfwInitHint(GLFW_WAYLAND_LIBDECOR, GLFW_WAYLAND_DISABLE_LIBDECOR);
#endif

    int glfw_initialized = glfwInit();
    if (!glfw_initialized)
    {
        Ni_SetErrorID(glfw_failure, true, NINOVIUM_DEFAULT_FC);
        return false;
    }

    // Get the GLFW representation of the user's "primary" monitor (really
    // just the first one GLFW finds).
    GLFWmonitor *primary_monitor = glfwGetPrimaryMonitor();
    if (primary_monitor == NULL)
    {
        Ni_SetErrorID(monitor_missing, true, NINOVIUM_DEFAULT_FC);
        return false;
    }
    const GLFWvidmode *resolution = glfwGetVideoMode(primary_monitor);

    // The window shall be neither resizable nor decorated in any way.
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

// Figure out some details for Linux windows.
#if defined(NINOVIUM_WAYLAND)
    glfwWindowHintString(GLFW_WAYLAND_APP_ID, title);
#elif defined(NINOVIUM_X11)
    glfwWindowHintString(GLFW_X11_CLASS_NAME, title);
    glfwWindowHintString(GLFW_X11_INSTANCE_NAME, title);
#endif

    window->_ = glfwCreateWindow(resolution->width, resolution->height,
                                 "unset", primary_monitor, NULL);
    if (window->_ == NULL)
        Ni_SetErrorID(window_failure, true, NINOVIUM_DEFAULT_FC);
    // Make our graphics context current on this thread.
    glfwMakeContextCurrent(window->_);

    window->width = resolution->width;
    window->height = resolution->height;
    window->title = NULL;
    if (title != NULL) Ni_ChangeWindowTitle(window, title);

    // Hide and disable movement of the cursor. This ensures our cursor
    // doesn't move off-screen or hit a border and break gameplay.
    glfwSetInputMode(window->_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return true;
}

void Ni_DestroyWindow(ni_window_t *window)
{
    if (window == NULL || window->_ == NULL)
    {
        Ni_SetErrorID(missing_parameter, true, NINOVIUM_DEFAULT_FC);
        return;
    }
    glfwDestroyWindow(window->_);

    window->title = NULL;
    window->width = 0;
    window->height = 0;

    glfwTerminate();
}

void Ni_ChangeWindowTitle(ni_window_t *window, const char *title)
{
    if (window == NULL || window->_ == NULL || title == NULL)
    {
        Ni_SetErrorID(missing_parameter, true, NINOVIUM_DEFAULT_FC);
        return;
    }

    window->title = title;
    glfwSetWindowTitle(window->_, window->title);
}

bool Ni_WindowStillOpen(const ni_window_t *window)
{
    if (window == NULL || window->_ == NULL)
    {
        Ni_SetErrorID(missing_parameter, true, NINOVIUM_DEFAULT_FC);
        return false;
    }

    return !glfwWindowShouldClose(window->_);
}

void Ni_UpdateWindow(const ni_window_t *window)
{
    if (window == NULL || window->_ == NULL)
    {
        Ni_SetErrorID(missing_parameter, true, NINOVIUM_DEFAULT_FC);
        return;
    }

    glfwPollEvents();
    glfwSwapBuffers(window->_);
}
