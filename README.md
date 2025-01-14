This utility is supported by OxTS. If you require assistance, please contact 
OxTS support at [https://support.oxts.com/hc/en-us/requests/new]

# OxTS Generic Aiding SDK

For more information on OxTS Generic Aiding Solutions, see 
[here](https://www.oxts.com/what-is-generic-aiding/)

This project contains the OxTS GAD SDK, written in C, C++, and Python. The SDK 
is designed to allow users to take measurements from their sensors, encode them 
to the GAD format, then send to an OxTS INS to be used in the navigation 
solution.

The OxTS GAD SDK is compliant with the Motor Industry Software Reliability 
Association (MISRA) coding standards.

Find the full code documentation for this project at: 
[https://oxfordtechnicalsolutions.github.io/index.html](https://oxfordtechnicalsolutions.github.io/index.html)

![Ubuntu 20.04](https://github.com/OxfordTechnicalSolutions/gad-sdk/actions/workflows/cmake.yml/badge.svg?branch=main)
![Windows 10](https://github.com/OxfordTechnicalSolutions/gad-sdk/actions/workflows/msbuild.yml/badge.svg?branch=main)
![Python3.11](https://github.com/OxfordTechnicalSolutions/gad-sdk/actions/workflows/python.yml/badge.svg?branch=main)
![Docs](https://github.com/OxfordTechnicalSolutions/gad-sdk/actions/workflows/Build_docs.yml/badge.svg?branch=main)

## Requirements

- Navsuite 3.13 or newer.
- OxTS INS with firmware version 240917 or newer.
- CMake >3.10
- Generic Aiding Feature Codes.
- Ethernet connection to an OxTS INS, for real-time aiding.
- C/C++ Compiler (Easiest option is to install Visual Studio 2019 
on Windows, or GCC on Linux)
- Python > 3.7 (Optional, for Python SDK and building documentation.)

### Installing requirements on Linux

To Install cmake on Linux operating systems, use the following:

```bash
sudo apt-get install cmake
```

### Installing requirements on Windows 

- Download and install [CMake](https://cmake.org/download/)

## Building from source

With the dependencies installed, steps for building the SDK are common between 
Linux and Windows systems.

1. Clone the repository onto the PC. Note: Clone this repository with the 
--recursive option to clone with pybind11 submodule. 

```console
git clone https://github.com/OxfordTechnicalSolutions/gad-sdk.git --recursive
```

2. Navigate to the root directory of the repository.

3. Execute the following commands:

```console
mkdir _build
cd _build 
cmake ..
cmake --build . --target install
```

Your machine may report an error from the INSTALL that permission to copy a 
file has been denied. The default install location required root/administrator 
level permissions, so either change the install location or rerun the install 
command either as sudo on Linux, or in a terminal with Admin privileges on 
Windows.

## Linking the C++ GAD SDK as a dependency

Once the build and install step is complete, other CMake projects on the 
machine can link to the libraries using:

```
find_package(oxts-sdk-gal-cpp REQUIRED)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        oxts-sdk-gal-cpp
)
```

in their CMakeLists.txt.
 
The SDK can then  be included your C++ source code using:

```c++
#include "oxts/gal-cpp/gad.hpp"
#include "oxts/gal-cpp/gad_handler.hpp"
```

 For an example of this usage, see [here](https://oxfordtechnicalsolutions.github.io/source/longform/my_first_gad.html)


**Note:** If this error message is shown when building a project which depends 
on the GAD SDK:

```
    Could not find a package configuration file provided by "oxts-sdk-gal-cpp"
  with any of the following names:

    oxts-sdk-gal-cppConfig.cmake
    oxts-sdk-gal-cpp-config.cmake
```

Place the following in a project's CMakeLists file:

```
set("oxts-sdk-gal-cpp_DIR" "<install_dir>/lib/cmake/oxts-sdk-gal-cpp")
```

Where, <install_dir> is the directory that the GAD-SDK is installed to. 
E.g. C:/Program Files (x86)/oxts-sdk 


## Python API

The C++ API has been wrapped in Python using PyBind11. As such, the same CMake 
dependency is required to build the Python SDK from source.

Clone and install as follows:

```console
git clone https://github.com/OxfordTechnicalSolutions/gad-sdk.git --recursive
python -m pip install ./gad-sdk 
```

Should you have already cloned the repo without `--recursive`, you will find 
that the PyBind folder is empty and the Python package fails to install. In 
this case, submodules can be updated using:

```console
git submodule update --init --recursive
```

Once the install is completed, the library can then be imported using 
`import oxts_sdk`.

Information on Python SDK can be found within the main SDK documentation. In 
addition, a list of bindings to the C++ can be found in the documentation or 
here `oxts-sdk-py/gal-py-bindings.cpp`. Also, there are examples here 
`examples/python/my-first-gad.py`.

## Unit Tests

Unit tests are not generally required for users of the GAD SDK, only 
developers. 

### C++

Unit tests for the C++ API have an additional dependency to the rest of the SDK,
in the form of Boost 1.82. 

#### Windows

- Download [Boost](https://www.boost.org/users/download/)
  - Extract the files to a sensible location such as C:\Libs. The full path to 
  the Boost libraries should resemble C:\Libs\boost_1_82_0.
  - In a terminal window, navigate to the Boost directory and run `bootstrap.bat` 
  - Then run `b2.exe link=shared` to install Boost.
  - Edit your environment variables and add the variable `BOOST_ROOT` with 
  value equal to the path to your Boost library. In this example the value 
  would be `C:\Libs\boost_1_82_0`

To build the unit tests, set the appropriate flag when configuring CMake, like 
so:

```console
mkdir build && cd build
cmake .. -DOXTS_SDK_BUILD_TESTS=ON
cmake --build .
```

The tests can then be run from the build folder using:

```console
./tests/Debug/unit_tests.exe
```

#### Linux (Ubuntu)

Install Boost 1.82:

```console
curl -L https://boostorg.jfrog.io/artifactory/main/release/1.83.0/source/boost_1_82_0.tar.gz | tar xz
cd boost_1_82_0
./bootstrap.sh --prefix=/usr/local
sudo ./b2 install
```

To build the unit tests, set the appropriate flag when configuring CMake, like 
so:

```console
mkdir build && cd build
cmake .. -DOXTS_SDK_BUILD_TESTS=ON
cmake --build .
```

The tests can then be run from the build folder using:

```console
./tests/unit_tests
```


### Python

The unit tests for the Python API are created using pytest. This can be 
installed using pip, or your chosen Python package manager.

With the oxts_sdk already installed following instructions above, run the 
following:

```console
python -m pytest ./tests/pybind_test.py 
```


## Building the docs

The documentation for this project can be found 
[here](https://oxfordtechnicalsolutions.github.io/index.html).

It is not necessary for users to build the documentation, though it can be 
useful in some cases.

1. Install Doxygen. Installation instructions can be found 
[here](https://www.doxygen.nl/manual/install.html).

2. Install Sphinx and Breathe using pip install (python 3.7 also required):

```console
  pip install -U sphinx
  pip install sphinx-tabs
  pip3 install sphinx-rtd-theme
  pip3 install breathe
  pip3 install sphinx-sitemap
  pip3 install sphinx-toolbox
```

3. Navigate to the `docs_sphinx\source` directory and run the command:

```console
  sphinx-build -b html . public
```
