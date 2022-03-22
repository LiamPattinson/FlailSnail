#ifndef __FLAILSNAILCOMPILERS_H
#define __FLAILSNAILCOMPILERS_H
// collection of macros for determining compiler info

#include <string.h>
#include "utils.h"

// Define struct containing info about compilers and compile time
struct FSCompilerInfo {
    char name[64];
    char version[64];
    char date[64];
};

// get compiler name and version
#if defined(__clang__)
    #define FS_COMPILER_CLANG
    #ifdef __GNUG__
        #define FS_COMPILER_NAME "clang++"
    #else
        #define FS_COMPILER_NAME "clang"
    #endif
    #define FS_COMP_MAJOR FS_STRINGIFY(__clang_major__)
    #define FS_COMP_MINOR FS_STRINGIFY(__clang_minor__)
    #define FS_COMP_PATCH FS_STRINGIFY(__clang_patchlevel__)
    #define FS_COMPILER_GNU
#elif defined(__GNUC__) // note: clang also defines __GNUC__, so this must be an elif
    #ifdef __GNUG__
        #define FS_COMPILER_NAME "g++"
    #else
        #define FS_COMPILER_NAME "gcc"
    #endif
    #define FS_COMP_MAJOR FS_STRINGIFY(__GNUC__)
    #define FS_COMP_MINOR FS_STRINGIFY(__GNUC_MINOR__)
    #define FS_COMP_PATCH FS_STRINGIFY(__GNUC_PATCHLEVEL__)
#else
    #error "FlailSnail: Unable to determine compiler type"
#endif

#define COMPILER_DETAILS                                        \
    struct FSCompilerInfo fs_compiler_info;                     \
    strcpy(fs_compiler_info.name, FS_COMPILER_NAME);            \
    strcpy(                                                     \
        fs_compiler_info.version,                               \
        FS_COMP_MAJOR "." FS_COMP_MINOR "." FS_COMP_PATCH       \
    );                                                          \
    strcpy(fs_compiler_info.date, __DATE__ " " __TIME__);


#endif // __FLAILSNAILCOMPILERS_H
