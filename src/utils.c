#include "utils.h"

char* fs_basename(char* path){
    // split into tokens based on '/' (unix) or '\' (win)
#ifdef UNIXLIKE
    char delim[] = "/";
#elif defined(_WIN32)
    char delim[] = "\\";
#else
#error "FlailSnail: Could not determine operating system"
#endif
    char* token = strtok(path, delim);
    while(token!=NULL){
        path = token;
        token = strtok(NULL,delim);
    }
    return path;
}
