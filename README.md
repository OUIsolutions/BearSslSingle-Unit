# BearSslSingle-Unit
These Project Generate a Single Unit Compilation for [BearrSSL](https://bearssl.org/) allowing you build
projects  with a single **gcc main.c** compilation

## Releases
## [BearSSLSingleUnit.zip]()

Its The final version of the project as a zip file , to use just extract the zip file and compile with

```c
#include "BearSSLSingleUnit/one.c"
```
## [BearSSLone.c]()

Its the same as the zip file , but amalgamated in one single file, you can include with

```c
#include "BearSSLone.c"
```
## [BearSSL.h]() and [BearSSL.c]()
its the "C style" Version, designed if you want to use in more than one compilation
unity
for use, in your C code

```c
#include "release/BearSSL.h"
``
and compile with
```shell
gcc
```


## Building From Scratch
if you want to build the hole project from scracth you must have a gcc  Compiler
and [CTags](https://github.com/universal-ctags/ctags) installed and run in linux
just type:
```shel
 sh pre_build.sh && ./build.outs
```
You can edit the **buld/stage2/lua/constants.lua** files , and pass the
**CTAGS_COMMAD** const  executable location if you want
