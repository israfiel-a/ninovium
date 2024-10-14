/**
 * @file Platform.h
 * @author Israfiel (https://github.com/israfiel-a)
 * @brief Defines some various platform-related macros and strings.
 * @date 2024-10-05
 *
 * @copyright (c) 2024 - Israfiel
 * This source code is under the AGPL v3.0. For information on what that
 * entails, please see the attached @file LICENSE.md file.
 */

#ifndef NINOVIUM__PLATFORM_H
#define NINOVIUM__PLATFORM_H

// Figure out what operating system we're compiling for. If it's not
// supported, we throw a compiler error.
#if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN32__)
    #define NINOVIUM_WINDOWS
    #define NINOVIUM_PLATFORM "windows"
#elif defined(linux) || defined(__linux__)
    #define NINOVIUM_LINUX
    #define NINOVIUM_PLATFORM "linux"
    // Define the display server of the application, as some window
    // creation hints that are required on X11 are not on Wayland.
    #if DISPLAY_SERVER == 0
        #define NINOVIUM_WAYLAND
        #define NINOVIUM_DISPLAY_SERVER "wayland"
    #elif DISPLAY_SERVER == 1
        #define NINOVIUM_X11
        #define NINOVIUM_DISPLAY_SERVER "x11"
    #else
        #error "Unsupported display server."
    #endif
#else
    #error "Unsupported operating system."
#endif

// Make sure we're running on a CPU architecture that we support.
// I'd really rather not run on x32 processors because of registry
// pressure, but if the user wants it, we'll let it happen.
#if defined(__x86_64__) || defined(_M_X64)
    #define NINOVIUM_ARCH "x86_64"
    #define NINOVIUM_X86_64
#elif defined(i386) || defined(__i386__) || defined(__i386) ||            \
    defined(_M_IX86)
    #define NINOVIUM_ARCH "x86_32"
    #define NINOVIUM_X86_32
    #warning "NINOVIUM will probably run strange on 32 bit systems."
#elif defined(__aarch64__) || defined(_M_ARM64) ||                        \
    defined(__AARCH64EL__) || defined(__arm64)
    #define NINOVIUM_ARCH "arm_x64"
    #define NINOVIUM_ARM_X64
#else
    #error "Unsupported CPU architecture."
#endif

// Define any debug state-specific macros.
#if !defined(NINOVIUM_DEBUG)
    #define NINOVIUM_BUILD_STATE "release"
    #if !defined(NDEBUG)
        #define NDEBUG
    #endif
#else
    #define NINOVIUM_BUILD_STATE "debug"
#endif

/**
 * @brief A string representing the full platform string of the currently
 * running NINOVIUM binaries. Note that this does @b not contain Ninovium's
 * display server even if on Linux, that has to be queried via the @ref
 * NINOVIUM_DISPLAY_SERVER macro.
 */
#define NINOVIUM_PLATFORM_STRING                                          \
    NINOVIUM_PLATFORM "-" NINOVIUM_ARCH "-" NINOVIUM_BUILD_STATE

#endif // NINOVIUM__PLATFORM_H
