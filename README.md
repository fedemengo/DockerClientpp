# A Docker Client SDK for C++

[![Build Status](https://travis-ci.org/tommyleo2/DockerClientpp.svg?branch=master)](https://travis-ci.org/tommyleo2/DockerClientpp)
[![Documentation](https://codedocs.xyz/tommyleo2/DockerClientpp.svg)](https://fedemengo.github.io/DockerClientpp/)

DockerClientpp is a simple docker client sdk written in C++

**This library heavily relies on Linux platform**

## Quick Start

```c++

DockerClient dc  // Instantiate a client with default option: connect to /var/run/docker.sock

DockerClient dc(SOCK_TYPE::SOCK_UNIX, "/path/to/docker/daemon/socket");

DockerClient dc(SOCK_TYPE::SOCK_TCP, "IP:Port");

string container_id = dc.createContainer({
  {"AttachStdout", true},
  {"AttachStderr", true},
  {"Tty", true},
  {"StopSignal", "SIGKILL"},
  {"Image", "busybox:1.26"}
}, "test");

ExecRet result = dc.executeCommand(container_id, {"echo", "hello DockerClientpp"});

std::cout << result.ret_code << std::endl 
          << result.output << std::endl; 
```
Note: 
1. For more usage, see [hello_world.cpp](./doc/example/hello_world.cpp)
2. For complete API reference, see [header file](./include/DockerClient.hpp) or [documentation](https://fedemengo.github.io/DockerClientpp/classDockerClientpp_1_1DockerClient.html)
3. For configuration passed in docker client see [Docker Engine API](https://docs.docker.com/engine/api/v1.37/)

## Build & Install

1. `git clone --recursive https://github.com/fedemengo/DockerClientpp.git`
2. `cd DockerClientpp`
3. `mkdir build`
4. `cd build`
5. `cmake ..`
6. `make install`(with root permission)

The library's name is `libDockerClientpp.a`
Use Headers `#include <dockerclientpp/DockerClientpp.hpp>` in your project

### Install locally

Compile the code inside the library folder

```
#!/bin/bash

currDir=${PWD}
clientDir="DockerClientpp"

# cd inside the library
cd ${clientDir} && \

mkdir -p deps && \

# create build folder
mkdir -p build && cd build && \

# generate make file with specific location
cmake .. -DCMAKE_INSTALL_PREFIX=${PWD}/../deps && \

# install the library in the desired location
make install && \

cd .. && rm -r build && \

echo "Installation succeded!"
```

### Use library

Link static and dynamic libraries from source folder

```
CC = g++

STATIC_LIB_PATH = -LDockerClientpp/deps/lib
STATIC_LIB_NAME = -lDockerClientpp -larchive
SHARED_LIB_PATH = -rpath=$(PWD)/DockerClientpp/deps/lib
INCLUDE_PATH = -IDockerClientpp/deps/include/DockerClientpp

LIB_FALGS = $(STATIC_LIB_PATH) $(STATIC_LIB_NAME) $(INCLUDE_PATH) -Wl,$(SHARED_LIB_PATH) -pthread

all: main.cpp
	$(CC) main.cpp $(LIB_FALGS)

clean:
	rm -f a.out
```

### doxygen support

After cmake configuration, execute `make doc`. The doc files will be put under `/<DockerClient root directory>/doc`

## Use in CMake Project

1. add subdirectory
2. link `DOCKER_CLIENT_PP_LIB` to your targets
