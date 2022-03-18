# FlailSnail

A library for describing a C/C++/Fortran run in detail, using only a single function call.

## Installation

Installation is handled using cmake:

```
> mkdir build
> cd build
> cmake ..
> make
> sudo make install
```

## Usage

To print details of a code run, try:

```c
// C code
#include <FlailSnail.h>

int main(int argc, char* argv[]){
    print_provenance_log(argc, argv);
    return 0;
}
```

```cpp
// C++ code
#include <FlailSnail.hpp>

int main(int argc, char* argv[]){
    print_provenance_log(argc, argv);
    return 0;
}
```

Fortran support is not yet available, but is a planned feature.

## Testing

```
cd tests
cmake .
make
ctest
# check the files worked -- not yet automated!
cat *.log
# try again with different compilers
cmake . -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++
make
ctest
cat *.log
```
