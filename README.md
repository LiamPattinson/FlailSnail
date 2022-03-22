# FlailSnail

A library for describing a C/C++/Fortran run in detail, using only a single function call.

## Installation

Installation is handled using cmake:

```
> cmake . -B build
> cmake --build build
> sudo cmake --build build --target install
```

## Usage

To print details of a code run, try:

```cpp
// C/C++ code
#include <FlailSnail.h>

int main(int argc, char* argv[]){
    print_provenance_log(argc, argv);
    return 0;
}
```

Fortran support is not yet available, but is a planned feature.

## Testing

```
> cmake --build build --target run-tests
# check the files worked -- not yet automated!
> cat build/tests/*.log

# try again with different compilers
> cmake . -B build_clang -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++
> cmake --build build_clang --target run-tests
> cat build_clang/tests/*.log
```
