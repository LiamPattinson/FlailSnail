#ifndef __FLAILSNAILUTILS_H
#define __FLAILSNAILUTILS_H

#include <string.h>

// get filename from path
char* fs_basename(char* path);

// Convert ARG to a string
#define _FS_STRINGIFY(ARG) #ARG
#define FS_STRINGIFY(ARG) _FS_STRINGIFY(ARG)

// tries multiple ways to see if we're on a unix-like system
#if defined(unix) || defined(__unix__) || defined(__unix) || defined(__APPLE__)
#define UNIXLIKE
#endif

#endif // __FLAILSNAILUTILS_H
