#include "FlailSnail/print_provenance_log.h"
#include "FlailSnail/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef UNIXLIKE
#include <unistd.h>
#endif

void _print_provenance_log(
    int argc,
    char* argv[], 
    struct FSCompilerInfo fs_compiler_info
){
    // get filename
    char* input_filename = fs_basename(argv[0]);
    char* extension = "_provenance.log"; // TODO add unique ID
    char* filename = malloc(strlen(input_filename) + strlen(extension) + 1);
    strcpy(filename, input_filename);
    strcat(filename, extension);

    FILE* file = fopen(filename, "w");

    fprintf(file, "[COMPILER DETAILS]\n");
    fprintf(file, "compiler_name = %s\n", fs_compiler_info.name);
    fprintf(file, "compiler_version = %s\n", fs_compiler_info.version);
    fprintf(file, "compile_date = %s\n", fs_compiler_info.date);

    fprintf(file, "\n[RUNTIME DETAILS]\n");
    fprintf(file, "program_name = %s\n", argv[0]);
    for( int ii=1; ii<argc; ++ii){
        fprintf(file, "command_arg_%d = %s\n", ii, argv[ii]);
    }
    time_t current_time = time(0);
    struct tm* local_time = localtime(&current_time);
    char date_time[32];
    strftime( date_time, 32, "%b %d %Y %H:%M:%S", local_time); 
    fprintf(file, "run_date = %s\n", date_time);
    // Get user details
#ifdef UNIXLIKE
    char hostname[256];
    char username[256];
    gethostname(hostname, 256);
    getlogin_r(username, 256);
    fprintf(file, "hostname = %s\n", hostname);
    fprintf(file, "username = %s\n", username);
#endif

    fclose(file);
    free(filename);
}
