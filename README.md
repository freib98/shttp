# shttp - simple http server

This repository contains the source code for a small HTTP/1.0 server with basic functionality. The goal is to implement the [RFC 1945](https://tools.ietf.org/html/rfc1945) as good as possible. Currently shttp works only on linux.

## Getting Started

These instructions will help you to get your environment ready to build, develop and run the project on your local machine.

### Build Prerequisites

You'll need the following tools:

* [Visual Studio Code](https://code.visualstudio.com/)
* [meson](https://mesonbuild.com/)
* [clang](https://clang.llvm.org/)
* [ninja](https://ninja-build.org/)

However, this is just the tool chain used to develop shttp. Other tool chains might work aswell, but these are garantied to work.

In order to debug shttp you need the [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) extension from the Visual Studio Code Marketplace.

### Building the code

This repository provides a bash script to build the binaries.

```
$ ./tools/build.sh
```

To debug shttp the build script accepts 'debug' as argument.

```
$ ./tools/build.sh debug
```

## Usage

Simply execute the shttp binary with a port:

```
$ ./shttp <<port>>
```
