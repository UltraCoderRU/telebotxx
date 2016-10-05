# telebotxx
[![Build Status](https://travis-ci.org/UltraCoderRU/telebotxx.svg?branch=master)](https://travis-ci.org/UltraCoderRU/telebotxx)

Telegram Bot API 2.0 for C++14. It uses [Curl for People](https://github.com/whoshuu/cpr) library to perform HTTP requests and [RapidJSON](https://github.com/miloyip/rapidjson) to work with JSON data.
In development, so you are welcome to contribute.

## Requirements
* C++14-compatible compiler
* CMake 2.8 or newer
* Boost Unit Test Framework (only for tests)

## Building
*You can set available options in CMakeLists.txt before running configure script.*
```bash
git submodule update --init --recursive
./configure
make
```
