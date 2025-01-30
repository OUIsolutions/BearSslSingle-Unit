# BearSslSingle-Unit
These Project Generate a Single Unit Compilation for [BearrSSL](https://bearssl.org/) allowing you build
projects  with a single **gcc main.c** compilation

## Releases

| item          | What Is |
|-------        |-----------|
| [BearSSLSingleUnit.zip](https://github.com/OUIsolutions/BearSslSingle-Unit/releases/download/v0.001/BearSSLSingleUnit.zip)| Full Folder Mode  |
| [BearSSLone.c](https://github.com/OUIsolutions/BearSslSingle-Unit/releases/download/v0.001/BearSSLone.c)Single File Version|
| [BearSSL.h](https://github.com/OUIsolutions/BearSslSingle-Unit/releases/download/v0.001/BearSSL.h)|Declaration |
| [BearSSL.c](https://github.com/OUIsolutions/BearSslSingle-Unit/releases/download/v0.001/BearSSL.h)|Declaration |




### [BearSSLSingleUnit.zip](https://github.com/OUIsolutions/BearSslSingle-Unit/releases/download/v0.001/BearSSLSingleUnit.zip)

Its The final version of the project as a zip file , to use just extract the zip file and compile with

```c
#include "BearSSLSingleUnit/one.c"
```
### [BearSSLone.c](https://github.com/OUIsolutions/BearSslSingle-Unit/releases/download/v0.001/BearSSLone.c)

Its the same as the zip file , but amalgamated in one single file, you can include with

```c
#include "BearSSLone.c"
```
### [BearSSL.h](https://github.com/OUIsolutions/BearSslSingle-Unit/releases/download/v0.001/BearSSL.h) and [BearSSL.c](https://github.com/OUIsolutions/BearSslSingle-Unit/releases/download/v0.001/BearSSL.c)
its the "C style" Version, designed if you want to use in more than one compilation
unity
for use, in your C code

```c
#include "release/BearSSL.h"
``
and compile with
```shell
 gcc -c BearSSL.c -o  BearSSL.o
 gcc main.c BearSSL.o
 ```


## Micro Client Example
just for testing , you have in **micro_client_sample** a micro https client example,
you can compile with:
```shell
gcc micro_client_sample/main.c -o client.o
```
and you can test with
```shell

 ./client.o example.com 443
```
Note that these example was taken from the original  [BearrSSL](https://bearssl.org/)  samples page
and the [BearSSLTrustedAnchors.h](https://github.com/arduino-libraries/ArduinoBearSSL/blob/master/src/BearSSLTrustAnchors.h)
was taken from the oficial arduino Github Organization

## Building From Scratch
if you want to build the hole project from scracth you must have a gcc  Compiler
and [CTags](https://github.com/universal-ctags/ctags) git  and curl installed and run in linux
just type:
```shel
 sh pre_build.sh && ./build.outs
```
You can edit the **config/commands** files , and pass the
**CTAGS_COMMAD**, **GIT_COMMAND** **CURL_COMMAND**  const  executable location if you want
