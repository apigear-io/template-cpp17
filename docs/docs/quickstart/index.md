---
sidebar_position: 2
---
import QuickStartCommon from "@site/docs/_quickstart_common.md"

# Quick-Start

The Quick-Start guide explains how in a few steps you get from an API definition to a functional c++ example.

Steps one and two are universal for other technologies. In the step two you will choose a concrete _cpp14_ template.
For more general information about first steps with ApiGear [First Steps](/docs/guide/intro)

The quick start enables only basic features: the [api](features/api.md) generation and simple [stub](features/stubs.md) implementation.
For all available features check the [overview](features/features.md).

<QuickStartCommon />

## 5. Use the generated cpp project

### Project folder structure

With the output directory set as in the example, both _ApiGear_ files reside in an `apigear` subfolder next to the _cpp_ generated files.
In this case the folder structure should look similar to this

```bash
📂hello-world
 ┣ 📂apigear
 ┃ ┣ 📜helloworld.solution.yaml
 ┃ ┗ 📜helloworld.module.yaml
 ┣ 📂cpp_hello_world
 # highlight-next-line
 ┃ ┣ 📂modules
 ┃ ┃ ┗ 📂io_world
 ┃ ┃ ┃ ┣ 📂generated
 ┃ ┃ ┃ ┣ 📂implementation
 ┃ ┃ ┃ ┃ ┣ 📜CMakeLists.txt
 ┃ ┃ ┃ ┃ ┣ 📜hello.cpp
 ┃ ┃ ┃ ┃ ┣ 📜hello.h
 ┃ ┃ ┃ ┃ ┗ 📜hello.test.cpp
 ┃ ┗ 📜CMakeLists.txt
```

Using the solution file from the previous paragraph the code will be generated in the `cpp_hello_world` folder.
With subfolder for each module, here `io_world` as the name of module (defined in line 2 of `helloworld.module.yaml`).
It contains both features generated: a basic api and a stub implementation.

The generated code provides cpp _C++_ implementations. The following paragraphs show how you can use it.
You can start your project loading the top level CMakeLists.txt in `cpp_hello_world` folder.

The 'io_world/io_world/generated/api/' folder contains all definitions of the enums and structs for your module, as well as the interface classes for your Interfaces.
From now on you can simply include the header files for the api interface or the stub implementation and use it.
For more details on generated features please check [api](features/api.md), [stubs](features/stubs.md).

:::tip
Check our "examples" with all features enabled to get more working examples.
:::

:::note
For the simulation check [the olink feature](features/olink.md) which provides middle layer on your code side and the [simulation](/docs/advanced/simulation/intro) explained.
:::

### Create and run an example

Prepare an `examples` folder in the `hello-world/cpp_hello_world` directory with a `main.cpp` like this:

```cpp
#include "io_world/implementation/hello.h"
#include <iostream>

int main(){
    HelloWorldExample::IoWorld::Hello myHelloInstance;

    // Try out properties: subscribe for changes
    myHelloInstance._getPublisher().subscribeToLastChanged(
        [](const HelloWorldExample::IoWorld::Message& last) { std::cout << "last property changed "; });
    // and ask for change.
    HelloWorldExample::IoWorld::Message messageForProperty;
    messageForProperty.m_content "New message";
    myHelloInstance.setLast(messageForProperty);

    // Check the signals with subscribing for its change
    myHelloInstance._getPublisher().subscribeToJustSaid(
        [](const HelloWorldExample::IoWorld::Message& msg) { qDebug() << "justSaid signal emitted "; });
    // and emit one.
    HelloWorldExample::IoWorld::Message messageForSignal;
    messageForSignal.m_content "Message from signal";
    emit myHelloInstance.justSaid(messageForSignal);

    // Play around executing operations, maybe they emit signals? or change the properties?
    auto method_result = myHelloInstance.say(HelloWorldExample::IoWorld::Message(), HelloWorldExample::IoWorld::When::Now);

    return 0;
}
```

add a `CMakeLists.txt` to the `examples` folder:

```bash
cmake_minimum_required(VERSION 3.1)
project(MyExample)

# append local binary directory for conan packages to be found
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MyExample main.cpp)

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(app PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(app PRIVATE /W4 /WX /wd4251)
endif()

find_package(io_world QUIET COMPONENTS io_world-core io_world-implementation )
target_link_libraries(app
    io_world::io_world-core
    io_world::io_world-implementation

)

install(TARGETS app
        RUNTIME DESTINATION bin COMPONENT Runtime)
```

Add the `examples` subdirectory to the `hello-world/cpp_hello_world/CMakeLists.txt`. Now you can build the application and the libraries with it and run your example.

:::tip
If generating all features, you'll need Poco library (websockets library used by OLink feature) or Paho (Mqtt library used by mqtt feature)'.
You then may want to use [conan](features/conan.md) feature, which will get all necessary dependencies.

Otherwise you might want to add
`set(CMAKE_MODULE_PATH "path/to/your/poco_or_paho_build")` to your `CMakeLists` or use option `-DCMAKE_PREFIX_PATH=$GITHUB_WORKSPACE/path/to/poco_or_paho_build` .
You might want also use conan for first time - to get you all those dependencies and then use paths provided by conan.
:::
