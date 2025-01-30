# BearSslSingle-Unit
These Project Generate a Single Unit Compilation for [BearrSSL](https://bearssl.org/) allowing you build
projects  with a single **gcc main.c** compilation

## Releases

| item          | What Is |
|-------        |-----------|
| [BearSSLSingleUnit.zip](https://github.com/OUIsolutions/BearSslSingle-Unit/releases/download/0.0.2/BearSSLSingleUnit.zip)| Full Folder Mode  |
| [BearSSLSingleUnitOne.c](https://github.com/OUIsolutions/BearSslSingle-Unit/releases/download/0.0.2/BearSSLSingleUnitOne.c)| Single File Version|
| [BearSSLSingleUnit.h](https://github.com/OUIsolutions/BearSslSingle-Unit/releases/download/0.0.2/BearSSLSingleUnit.h)|Declaration |
| [BearSSLSingleUnit.c](https://github.com/OUIsolutions/BearSslSingle-Unit/releases/download/0.0.2/BearSSLSingleUnit.c)|Declaration |




### [BearSSLSingleUnit.zip](https://github.com/OUIsolutions/BearSslSingle-Unit/releases/download/0.0.2/BearSSLSingleUnit.zip)

Its The final version of the project as a zip file , to use just extract the zip file and compile with

```c
#include "BearSSLSingleUnit/one.c"
```
###  [BearSSLSingleUnitOne.c](https://github.com/OUIsolutions/BearSslSingle-Unit/releases/download/0.0.2/BearSSLSingleUnitOne.c)

Its the same as the zip file , but amalgamated in one single file, you can include with

```c
#include "BearSSLone.c"
```
###  [BearSSLSingleUnit.h](https://github.com/OUIsolutions/BearSslSingle-Unit/releases/download/0.0.2/BearSSLSingleUnit.h) and [BearSSLSingleUnit.c](https://github.com/OUIsolutions/BearSslSingle-Unit/releases/download/0.0.2/BearSSLSingleUnit.c)
its the "C style" Version, designed if you want to use in more than one compilation
unity
for use, in your C code

```c
#include "release/BearSSL.h"
``
and compile with
```shell
 gcc -c BearSSLSingleUnit.c -o  BearSSL.o
 gcc main.c BearSSL.o
 ```


## Micro Client Example
just for testing , you have in **micro_client_sample** a micro https client example, put the 
**BearSSLSingleUnitOne.c** in the same folder and
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
if you want to build the hole project from scracth you must have 
**diff**,**patch** and [Darwin](https://github.com/OUIsolutions/Darwin/tree/0.016) on version **0.016**
clone the repon and type:
```shel
 darwin run_blueprint --mode folder  src/ update_bear  create_patch  build generate_release 
 ```
