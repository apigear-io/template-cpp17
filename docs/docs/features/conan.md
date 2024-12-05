﻿---
sidebar_position: 5
---
import CodeBlock from '@theme/CodeBlock';
import helloWorldModuleComponent from '!!raw-loader!./data/helloworld.module.yaml';

# Conan package manager

With this feature you we generate a conan support for your project. It helps with packaging and to managing dependencies for different platforms, OSs, compilers, architecture, cross-builds. Read more about conan and its all benefits [here](https://conan.io/).

:::tip
Please make sure your C++ standard is set to 17 in your conan profile i.e.:<br />
`compiler.cppstd=17`
:::

### File overview for module

With an example API

<details>
    <summary>Hello World API (click to expand)</summary>
    <CodeBlock language="yaml" showLineNumbers>{helloWorldModuleComponent}</CodeBlock>
</details>

The files for conan will be generated for project:

```bash {9}
📂hello-world
 ┣ 📂apigear
 ┣ 📂cpp_hello_world
 ┃ ┣ 📂apigear
 ┃ ┃ ...
 ┃ ┃ ┗ 📜conanfile.py
 ┃ ┣ 📂examples
 ┃ ┃ ┣ 📂 app
 ┃ ┃ ┃ ...
 ┃ ┃ ┃ ┗ 📜conanfile.txt
 ┃ ┃ ... 
 ┃ ┣ 📂modules
 ┃ ┃ ┗ 📂io_world
 ┃ ┃ ┃ ┣ 📂conan
 ┃ ┃ ┃ ┃ ┣ 📂test_package
 ┃ ┃ ┃ ┃ ┃ ┣ 📜CMakeLists.txt
 ┃ ┃ ┃ ┃ ┃ ┣ 📜conanfile.py
 ┃ ┃ ┃ ┃ ┃ ┗ 📜main.cpp
 ┃ ┃ ┃ ┃ ┗ 📜conanfile.py
 ┣ 📂scripts
 ┃ ┣ 📜test_conan.bat
 ┃ ┣ 📜test_conan.sh
 ```
### Run scripts
The top level files you'll find in '📂hello-world/cpp_hello_world' `📜test_conan.bat` (for windows) and `📜test_conan.sh` (for linux based systems) contain set of command line commands to build whole project.
The scripts build the project twice: 
- Firstly, using a package development commands. This way is recommended for local development, testing and modifications/customization of the build process in the user space without recompiling the entire package. Used command is `conan build ..` (preceded by `source` command that copies necessary sources and `install` command which installs the requirements and generates the info files).
You can read more about build [here](https://docs.conan.io/1/reference/commands/development/build.html).
- Secondly, with one of  conan creator commands `conan create ...`. It is primarily used to generate, package, and upload packages to a repository. It calls the local conanfile.py ‘package()’ method. The `conanfile.py` is located in the `📂modules` and created for each module separately. Creator Commands are more geared toward recipe creation, versioning, and repository interactions. You can read more about package [here](https://docs.conan.io/1/reference/commands/development/package.html).

We use CMake build system with conan.

:::tip
Modify the script to suit your needs. You can choose one of the building methods depending on current stage of your package development lifecycle.
:::


Some of the above files, the `📂cpp_hello_world/apigear/conanfile.py` or `conanfiles.txt` generated for each example were present even without conan feature - for simplicity of generation rules. <br />
The `📂cpp_hello_world/apigear/conanfile.py` contains recipe for building additional library - network layer for cpp-template,  independent from your API, and necessary for [ObjectLink core](https://github.com/apigear-io/objectlink-core-cpp), for aligning to MQTT protocol or for tracing. <br />
The  `📂cpp_hello_world📂modules/io_world/conan/conanfile.py` is the main recipe for your API module, which contains all the info necessary for packaging.
Dependencies for the examples are stored in conanfile.txt files in each of the examples ( conanfile.txt is a simplification of conanfile.py, that can be used exclusively to consume dependencies, but not to create packages).

The test package
Files inside the `📂cpp_hello_world/modules/io_world/conan/test_package contain a test package`. It instantiates `Hello` implementation from a `stub` feature. It is a check that package for `io_world` was created in proper way, can be found and used.
 