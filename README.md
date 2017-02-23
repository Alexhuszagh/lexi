Lexi
====

Lexi, for lexical, is a fast conversion library to and from lexical forms. Internally, Lexi uses code from Milo Yip's [dtoa and itoa](https://github.com/miloyip/rapidjson) implementation for double and integer conversions, respectively, and adds type detection as well as other overloads for fast lexical conversions.

**Table of Contents**

- [Features](#features)
- [Testing](#testing)
- [Portability](#portability)
- [Acknowledgments](#acknowledgements)
- [Contributor Guidelines](#contributor-guidelines)
- [License](#license)

## Features

- Fast integer formatting
- Fast double formatting based off the Grisu2 algorithm
- Overloads for enumerated types

## Building

Simply clone, configure with CMake, and build.

```bash
git clone https://github.com/Alexhuszagh/lexi.git
git submodule update --init
cd json/build
cmake .. -_DBUILD_TESTS=ON      # "-DBUILD_FUZZ=ON" for fuzzing with Clang
make -j 5                       # "msbuild Lexi.sln" for MSVC
```

## Testing

// TODO: need to fuzz

## Portability

Json++ has been tested with the following compilers and operating systems:

- 64-bit Linux with Clang 3.8.2
- 64-bit Linux with GCC 5.4.0
- 32/64-bit Windows with MinGW 5.3.0 (MXE, MinGW, and MSYS2) 
//- 32/64-bit Windows with Visual Studio 14 2015

## Acknowledgments

Milo Yip. for his fast-formatting and extraction algorithms.

## Contributor Guidelines

All useful pull requests will be merged, provided that they do not add external dependencies and follow these guidelines.

1. Preprocessor macros should be used sparingly.
2. Code syntax should not depend on the preprocessor.
3. Your code must be readable.
4. Keep minimal definitions in the headers for compilation time.

## License

MIT, see [license](LICENSE.md).
