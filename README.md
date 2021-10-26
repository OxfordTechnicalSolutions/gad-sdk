# OxTS Generic Aiding SDK

This project contains the OxTS GAD SDK, written in C++. This SDK is designed to allow users to encode aiding data to GAD packets and send them to an OxTS INS for use in the navigation solution. It also contains NCom decoder functionality, for those who wish to receive data from the unit.

Find the full code documentation for this project at: [https://oxts.gitlab.io/navigation/generic-aiding/gad-sdk/](https://oxts.gitlab.io/navigation/generic-aiding/gad-sdk/)

## Requirements

- CMake 3.1
- Boost 1.71 (requirement can be disabled, though this will remove UDP functionality)
- Generic Aiding Feature Codes.
- Ethernet connection to an OxTS INS, for real-time aiding.

### Installing requirements on Linux

```
sudo apt-get install cmake
sudo apt-get install libboost-all-dev
```

### Installing requirements on Windows 

- Download and install [CMake](https://cmake.org/download/)
- Download [Boost](https://www.boost.org/users/download/)
  - Extract the files to a sensible location such as C:\Libs. Note you do not need to create an extra containing folder. The full path to the boost libraries should resemble C:\Libs\boost_1_77_0.
  - Navigate to the boost directory and run ``` bootstrap.bat ``` 
  - Run ```b2.exe link=shared```
  - Edit your environment variables and add the variable ```BOOST_ROOT``` with value equal to the path to your boost library. In this example the value would be ```C:\Libs\boost_1_77_0```

## Getting Started

Install the pre-built binaries from... (TBC). Will require some form of deployment.

## Building from source

Users can also build the SDK from source, using the following instructions:

1. Clone the repository onto the PC.
2. Navigate to the root directory of the repository
3. (Optional) Edit the CMakeLists.txt file in the root of the repository to 
   configure options, such as enabling building of examples and documentation.
4. Execute the commands:

### Linux
```
mkdir _build && cd _build 
cmake ..
cmake --build . --target install
```
This will build the SDK and install it to your machine. Your machine may report an error from the INSTALL that permission to copy a file has been denied. In this case run the last command again, but add `sudo` to the start. This should provide the correct access rights to install files to the correct location. 

### Windows
```
mkdir _build
cd _build
cmake ..
cmake --build . --target install
```
This will build the SDK and install it on your machine. You may need to run CMD or Powershell as an adminitrator if the SDK fails to install.


Once this is complete, other CMake projects on the machine can link to the libraries using:

```
find_package(oxts-sdk-gal-cpp REQUIRED)
find_package(Boost COMPONENTS system thread regex)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        oxts-sdk-gal-cpp
)
```
in their CMakeLists.txt. 
Header files can then be included in code files using 
`#include "oxts/<oxts-sdk-module>/<filename>.hpp".

### Build options

The CMakeLists.txt file in the root of the repository contains some options for building the SDK.

| Option | Description | Default |
|-------------|---------------|----|
|OXTS_SDK_BUILD_EXAMPLES|Enable examples targets.| ON |
|OXTS_SDK_DISABLE_BOOST|Use Boost library when building. Note that not using boost will limit UDP functionality, which will need to be replaced by the user in order to send GAD to an INS.| OFF |
<!-- |OXTS_SDK_BUILD_DOCS|Build SDK documentation.| OFF | -->

### Building the docs

The documentation for this project is generated using a few tools: Doxygen, Breathe, and Sphinx. 

1. Install requirements (python 3.7 also required):
```
  pip install -U sphinx
  pip3 install sphinx-rtd-theme
  pip3 install sphinx-sitemap
  pip3 install breathe

```
2. Navigate to the `docs_sphinx` directory and run the command:
```
  sphinx-build -b html . public
```


## Python GAD SDK (Windows and Linux)

Note: As of PIP 21.3 pip creates build files locally in a folder called build instead of a temporary folder. If the boost install directory changes or the path isn't set properly then the build folder should be manually deleted before trying to install again. Likewise if modifying the code and installing again then the build folder should be deleted.  

The C++ SDK has been wrapped in Python using PyBind11. The interface for the Python code largely matches that of the C++ code, though class accessors have been replaced with Python properties.

The Python SDK is not yet  documented, though its binding to the C++ can be found in `oxts-sdk-py/gal-py-bindings.cpp`. There is also an example in `examples/python/my-first-gad.py`.

To install the package, use `pip install ./oxts-sdk` from the directory above the repository folder. After that, it can be imported using `import oxts_sdk`.


