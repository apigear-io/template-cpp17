---
sidebar_position: 2
---

# Quick-Start

The Quick-Start guide explains how in a few steps you get from an API definition to a functional c++ example.

Steps one and two are universal for other technologies. In the step two you will choose a concrete _cpp14_ template.
For more general information about first steps with ApiGear [First Steps](/docs/start/first_steps)

The quick start enables only basic features: the [api](features/api.md) generation and simple [stub](features/stubs.md) implementation.
For all available features check the [overview](features/features.md).

## 1. Install the code generator

Get the [ApiGear Studio](https://github.com/apigear-io/studio-releases/releases) or [ApiGear CLI](https://github.com/apigear-io/cli/releases). For more information check the [ApiGear documentation](/docs/start/install).

## 2. Get the template

There are several options to get the template. Installation via the _Studio_ or the _CLI_. Alternatively it is possible to clone or download from github.

### Installation via CLI

When using the _CLI_ only the highlighted line is imported. You can always check whether the installation was successful via the `template list` command.

```bash
$ apigear template list
list of templates from registry and cache
name                       | installed | registry | url
apigear-io/template-cpp14 | false     | true     | https://github.com/apigear-io/template-cpp14.git
...
# highlight-next-line
$ apigear template install apigear-io/template-cpp14
$ apigear template list
list of templates from registry and cache
name                       | installed | registry | url
apigear-io/template-cpp14 | true      | true     | https://github.com/apigear-io/template-cpp14.git
...
```

### Installation via Studio

From within the studio the installation is really simple.

1. Open an existing project or create an new one
2. Go to the `Templates` tab
3. Click `Install` on the `apigear-io/template-cpp14` entry

### Clone from github

In case you want to check or modify the source code of the template, it is easier to clone or download the repository. The repository does not need to be part of the project, but can be stored anywhere on the computer.

```bash
$ git clone https://github.com/apigear-io/template-cpp14.git
```

You can then point the solution file to use your template from its directory by providing relative path from the solution file.

## 3. Set up project

For a project we usually need two files. The solution which specifies what `APIs` and which template to use for it. And at least one `API` module file.
Both should ideally be in a folder called `apigear` next to each other.

Alternatively, you can also use the _Studio_ to create a new project and modify the two example files.

### Solution file

Create a [solution](/docs/start/first_steps#create-a-solution) file.
The example below specifies

- module files in _line 8_, here the `helloworld.module.yaml` module with `Hello` API
- the output directory for generated files in _line 9_
- a template used to generate the code in _line 10_, here the `apigear-ui/template-cpp14` template. This can also be a path to a local copy of the template.
- the enabled features of the template in _line 13_, here the `stubs` feature, a simple implementation of interfaces. For all available features check the [overview](features/features.md).

```yaml title="helloworld.solution.yaml" showLineNumbers
schema: "apigear.solution/1.0"
name: hello_world_example
version: "0.1.0"

targets:
  - name: cpp_hello_world
    inputs:
      - helloworld.module.yaml
    output: ../cpp_hello_world
    template: apigear-io/template-cpp14
    force: true
    features:
      - stubs
```

:::tip Targets
You can extend this solution file with other targets, each for the different technology with different template. The `module.yaml` is technology independent and may be used for any template.
:::

:::note
Set the force parameter to true if you want to always override all the generated files. With option set to false some files, like implementation (stub feature) won't be updated. All the API files are always updated.
:::

### API module file

Use your favorite text editor to create the `helloworld.module.yaml` with the example content:

```yaml title="helloworld.module.yaml" showLineNumbers
schema: apigear.module/1.0
name: io.world
version: "1.0.0"

interfaces:
  - name: Hello
    properties:
      - { name: last, type: Message }
    operations:
      - name: say
        params:
          - { name: msg, type: Message }
          - { name: when, type: When }
        return:
          type: int
    signals:
      - name: justSaid
        params:
          - { name: msg, type: Message }
enums:
  - name: When
    members:
      - { name: Now, value: 0 }
      - { name: Soon, value: 1 }
      - { name: Never, value: 2 }
structs:
  - name: Message
    fields:
      - { name: content, type: string }
```

## 4. Generate code

With the output directory set as in example, both _ApiGear_ files reside in an `apigear` subfolder next to the _cpp_ generated files.
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

### Generate via CLI

The following snippet shows how the CLI can be run.

```bash
$ apigear generate solution apigear/helloworld.solution.yaml
10:52:20 INF generated 21 files in 30ms. (20 write, 0 skip, 1 copy) topic=gen
```

- `generate` tells the CLI that it should generate code
- `solution` specifies that we want to run a solution file

### Generate via Studio

1. Open the project
2. Go to the `Solutions` tab
3. Click `Run` on the `helloworld.solution.yaml` entry

## 5. Use the generated cpp project.

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
