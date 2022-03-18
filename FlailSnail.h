#ifndef __FLAILSNAIL_H
#define __FLAILSNAIL_H

// Define main function macro
// This is a macro rather than a function as compiler details must be obtained from the
// calling program. If it were a regular function defined in a .c file, this would
// simply tell us the C compiler used to compile FlailSnail.

#include "FlailSnail/include/print_provenance_log.h"
#include "FlailSnail/include/compilers.h"

#define print_provenance_log(argc, argv)\
    /* expand compiler details macro, get fs_compiler_info struct */\
    COMPILER_DETAILS\
    _print_provenance_log((argc), (argv), fs_compiler_info);

#endif // __FLAILSNAIL_H
