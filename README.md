Lexi
====

Lexi, for lexical, is a fast conversion library to and from lexical forms. Internally, Lexi uses code from Milo Yip's [dtoa and itoa](https://github.com/miloyip/rapidjson) implementation for double and integer conversions, respectively, and adds type detection as well as other overloads for fast lexical conversions.

[![Build Status](https://travis-ci.org/Alexhuszagh/lexi.svg?branch=master)](https://travis-ci.org/Alexhuszagh/lexi)
[![Build Status](https://tea-ci.org/api/badges/Alexhuszagh/lexi/status.svg)](https://tea-ci.org/Alexhuszagh/lexi)
[![Build status](https://ci.appveyor.com/api/projects/status/mds5o52wguleb54b?svg=true)](https://ci.appveyor.com/project/Alexhuszagh/lexi)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/12987/badge.svg)](https://scan.coverity.com/projects/alexhuszagh-lexi)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/103c3c4c3b1f4508ae34278366cacdaf)](https://www.codacy.com/app/Alexhuszagh/lexi?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Alexhuszagh/lexi&amp;utm_campaign=Badge_Grade)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/Alexhuszagh/lexi/blob/master/LICENSE.md)

**Table of Contents**

- [Features](#features)
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
cd lexi/build
cmake .. -_DBUILD_TESTS=ON      # "-DBUILD_FUZZ=ON" for fuzzing with Clang
make -j 5                       # "msbuild lexi.sln" for MSVC
```

## Portability

Lexi is continually built with the following compiler and compiler versions:

- Clang 3.8+
- GCC 5.3+
- MinGW 5.3.0 (MXE, MinGW, and MSYS2) 

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
