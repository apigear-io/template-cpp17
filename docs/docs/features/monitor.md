---
sidebar_position: 4
---

import CodeBlock from '@theme/CodeBlock';
import helloWorldModuleComponent from '!!raw-loader!./data/helloworld.module.yaml';

# Monitor

Use the monitor feature to examine the interface calls, state and signals during runtime. With this feature you obtain a monitor client and a monitored version of your interfaces. The monitoring server is embedded into the [ApiGear Studio](/docs/studio/intro) and [CLI version](/docs/cli/intro).
More details on [monitoring](/docs/monitor/intro)

## File overview for module

With our example API definition

<details>
    <summary>Hello World API (click to expand)</summary>
    <CodeBlock language="yaml" showLineNumbers>{helloWorldModuleComponent}</CodeBlock>
</details>

the following file structure will be generated. The purpose and content of each file is explained below.

```bash {7,18}
📂hello-world
 ┣ 📂apigear
 ┃ ...
 ┣ 📂cpp_hello_world
 ┃ ┣ 📂apigear
 ┃ ┃ ...
 ┃ ┃ ┣ 📂tracer
 ┃ ┃ ┃ ┣ 📜CMakeLists.txt
 ┃ ┃ ┃ ┣ 📜tracer.cpp
 ┃ ┃ ┃ ┣ 📜tracer.h
 ┃ ┃ ┃ ┗ 📜tracer.test.cpp
 ┃ ┣ 📂examples
 ┃ ┣ 📂modules
 ┃ ┃ ┗ 📂io_world
 ┃ ┃ ┃ ┣ 📂generated
 ┃ ┃ ┃ ┃ ┣ 📂monitor
 ┃ ┃ ┃ ┃ ┃ ┣ 📜CMakeLists.txt
 ┃ ┃ ┃ ┃ ┃ ┣ 📜hello.tracedecorator.cpp
 ┃ ┃ ┃ ┃ ┃ ┣ 📜hello.tracedecorator.h
 ┃ ┃ ┃ ┃ ┃ ┣ 📜hello.tracer.cpp
 ┃ ┃ ┃ ┃ ┃ ┗ 📜hello.tracer.h
 ...
```

### Interface Independent Trace Client

When generating the monitor feature (or olink feature) you'll get an additional folder in the top most directory:`📂hello-world/apigear`. The `📂tracer` subfolder contains a client for logging, with a network layer (based on the [POCO](https://docs.pocoproject.org/current/Poco.Net.html) library).
The class connects to the `Apigear Trace Server` and takes care of formatting and sending the traces.

### Monitor

Files `📜hello.tracedecorator.h` and `📜hello.tracedecorator.cpp` contain the trace wrapper for the `Hello` interface. The wrapper will be generated for each interface inside the API definition.

```cpp
class HELLO_WORLD_EXAMPLE_IO_WORLD_EXPORT HelloTraceDecorator : public IHello, public IHelloSubscriber
{
    explicit HelloTraceDecorator(IHello& impl, ApiGear::PocoImpl::Tracer& tracer)

...
};
```

The tracer uses the implementation of `IHello` - wraps each interface operation call and the notifications of property changed and signal emitted with a lgo to a monitor tool.
The other calls are just forwarded to your implementation - so you can use the `HelloTraceDecorator` as a `Hello` object.

:::note
The wrapped object `IHello& impl` is just the object that fulfills the `IHello` interface, so the implementation can be e.g. the [`OlinkClient`](olink.md) version of `Hello`.
:::

The `📜hello.tracer.h` and `📜hello.tracer.cpp` files contain helper to prepare interface specific trace data for the general tracing [TraceClient](monitor#tracing-example)

### Tracing example

Prepare an application (generate for both examples and monitor features) that uses the tracer:

```cpp

int main(){
    ApiGear::PocoImpl::Tracer tracer;
    tracer.connect("http://localhost:8182", "testExampleApp");
    std::unique_ptr<IoWorld::IHello> helloImplementation = std::make_unique<IoWorld::Hello>();
    std::unique_ptr<IoWorld::IHello> tracedHello = IoWorld::HelloTraceDecorator::connect(*helloImplementation, tracer);

    // use your tracedHello as it was Hello implementation, all property changes, and signals and method execution and function calls will be traced.
    auto lastMessage = tracedHello->getLast();
    tracedHello->say(lastMessage, IoWorld::WhenEnum::Soon);
    IoWorld::Message someMessage("the new content");
    tracedHello->setLast(someMessage);
    tracedHello->_getPublisher().publishJustSaid(someMessage);
    return 0;
}
```

Make sure that you are using the same port for sending and receiving traces.
For sending: check yor setting for `ApiGear::PocoImpl::Tracer`.
For receiver: go to the ApiGear Studio settings and set correct port number.
By default the address is set to `ws://localhost:8182/ws`.
