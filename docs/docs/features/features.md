import CodeBlock from '@theme/CodeBlock';
import helloWorldModuleComponent from '!!raw-loader!./data/helloworld.module.yaml';
import Figure from '../figure'

# Features

This guide explains how to use the generated code, what are the available features and their benefits.

:::info
A feature is a part of the template that generates a specific aspect of the code. For example, the `api` feature generates the core API interfaces and the `stubs` feature generates a stub implementation for the API.
:::

## Get started

This template generates code for pure c++ projects. In order to successfully compile and use the code, you need to have a working c++ compiler toolchain installed.

:::note
Basic c++ knowledge is necessary.
:::

### Code generation

Follow the documentation for the [code generation](/docs/guide/intro) in general and [CLI](/docs/tools/cli/generate) or the [Studio](/docs/tools/studio/intro) tools.
Or try first the [quick start guide](../quickstart/index.md) which shows how to prepare api and generate code out of it.

:::tip
For questions regarding the template please go to our [discussions page](https://github.com/orgs/apigear-io/discussions). For feature requests or bug reports please use our [issue tracker](https://github.com/apigear-io/template-cpp14/issues).
:::

### Example API

The following code snippet contains the _API_ definition which is used throughout this guide to demonstrate the generated code and its usage.

<details>
    <summary>Hello World API (click to expand)</summary>
    <CodeBlock language="yaml" showLineNumbers>{helloWorldModuleComponent}</CodeBlock>
</details>

## Features

### Core Features

Features generate a view model for the _API_ definition. This can be used to implement a working _C++_ service and directly use it in your project.

- [api](api.md) - generates compilable base pure interfaces for your _API_, as also a basic implementation for data types and subscriber/publisher as abstract classes that describe the notification system for users of your interfaces.
- [stubs](stubs.md) - adds a basic stub implementation for the _API_, you'll get classes that can actually be instantiated with a ready to use publishers, this is a good starting point for your implementation.
- [conan](conan.md) - build and packaging support for your project.

### Extended Features

Features can be used in combination with _API_ and add more functionality on top, like simulation support (see [olink](olink.md#simulation))

- [olink](olink.md) - provides a client and server adapters for each interface, that can be connected to any of the other technology templates with support for [ObjectLink](/docs/advanced/protocols/objectlink/intro). Use this feature to connect with ApiGear simulation tools.
- examples_olink - examples of generated code for the olink feature. Contains:
	- `olinkserver` shows use of your interfaces as an olink services.
	- `olinkclient` shows use of your interfaces as an olink clients.
- [monitor](monitor.md) - generates a middle-ware layer which logs all API events to the [CLI](/docs/tools/cli/intro) or the [Studio](/docs/tools/studio/intro)
- [MQTT](mqtt.md) _experimental_ - provides minimal working adapters for MQTT client and service side for each interfaces. Check also MQTT in other technology templates that supports it.
- examples_mqtt - examples of generated code for the olink feature. Contains:
	- `mqttserver` shows use of your interfaces with mqtt adapted for your services.
	- `mqttclient` shows use of your interfaces as a mqtt adapted for your services users.
- examples of generated code for basic features:
  - `app` simple example with stubs.
  - `appthreadsafe` simple example with stubs wrapped with thread safe decorator. See [thread safe decorator from core features](stubs.md#core)

<Figure caption="Overview of features for user application, including receiving data from network: Bottom floor shows possible inputs for your API, you can either obtain data from the network with OLink or MQTT or use local (thread safe if necessary) implementation." src="/img/features/featuresApp.png" />

:::note
Theoretically you can use the Thread Safe Decorator with other features that implements API: OLinkClient and MQTT Client, but they, already provide thread safety on at least the same level as the Thread Safe Decorator.
:::

<Figure caption="Overview of features for user application, including publishing data through network: Topmost floor shows your options for using your local implementation (bottom floor): you can use it in your local app and/or use method of sharing the data with clients in the network. Consider then using thread safe version of your implementation." src="/img/features/featuresServer.png" />

There are also an _internal_ features:

- `apigear`, which is generated for the _extended_ features and is explained with them.
- `core`, which is generated for the stubs and the _extended_ features. For the explanation see [core documentation](stubs.md#core)

Each feature can be selected using the solution file or via command line tool.

:::note
_Features are case sensitive, make sure to always **use lower-case.** _
:::

:::tip
The _meta_ feature `all` enables all specified features of the template. If you want to see the full extent of the generated code `all` is easiest solution.
Please note, `all` is part of the code generator and not explicitly used within templates.
:::

## Folder structure

This graph shows the full folder structure which is generated for `all` features enabled, but skips the [conan](conan.md) files. Generated features are encapsulated in separate folders for each module or for the common features like `examples` and the internal helper feature `apigear`, a level above, in the `generation target` level, here `cpp_hello_world`. For more details visit the documentation for each feature.

```bash
📂hello-world
 ┣ 📂apigear
 ┃ ┣ 📜helloworld.solution.yaml
 ┃ ┗ 📜helloworld.module.yaml
 ┣ 📂cpp_hello_world
 ┃ ┣ 📂apigear
 ┃ ┣ 📂examples
 ┃ ┣ 📂modules
 ┃ ┃ ┗ 📂io_world
 ┃ ┃ ┃ ┣ 📂conan
 ┃ ┃ ┃ ┣ 📂generated
 ┃ ┃ ┃ ┃ ┣ 📂api
 ┃ ┃ ┃ ┃ ┣ 📂core
 ┃ ┃ ┃ ┃ ┣ 📂monitor
 ┃ ┃ ┃ ┃ ┣ 📂mqtt
 ┃ ┃ ┃ ┃ ┗ 📂olink
 ┃ ┃ ┃ ┣ 📂implementation
 ┃ ┃ ┃ ┣ 📜CMakeLists.txt
 ┃ ┃ ┃ ┗ 📜Io_worldConfig.cmake.in
 ┃ ┗ 📜CMakeLists.txt
```
