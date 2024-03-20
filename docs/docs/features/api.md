---
sidebar_position: 1
---

import CodeBlock from '@theme/CodeBlock';
import helloWorldModuleComponent from '!!raw-loader!./data/helloworld.module.yaml';

# API Feature

The feature `api` is the bare minimum for code generation. The feature will generate:

- core behavioral API for the defined _interfaces_
- interfaces for [publisher](api#publisher) and [subscriber](api#subscriber) tailored for each interface
- Enumerations for the defined _enums_
- Data structured with a core implementation for the defined _structs_

:::note
Check out the [stubs](stubs.md) feature which provides fully functional implementation for the publisher.
:::

### Files overview per module

Using the example API definition

<details>
  <summary>Hello World API (click to expand)</summary>
  <CodeBlock language="yaml" showLineNumbers>{helloWorldModuleComponent}</CodeBlock>
</details>

the following file structure will be generated inside the target folder. The purpose and content of each file is explained below.

```bash
📂hello-world
 ┣ 📂apigear
 ┣ 📂cpp_hello_world
 ┃ ┣ 📂apigear
 ┃ ┣ 📂examples
 ┃ ┣ 📂modules
 ┃ ┃ ┗ 📂io_world
 ┃ ┃ ┃ ┣ 📂generated
 ┃ ┃ ┃ ┃ ┣ 📂api
 ┃ ┃ ┃ ┃ ┃ ┣ 📜CMakeLists.txt
 ┃ ┃ ┃ ┃ ┃ ┣ 📜common.h
 ┃ ┃ ┃ ┃ ┃ ┣ 📜datastructs.api.cpp
 ┃ ┃ ┃ ┃ ┃ ┣ 📜datastructs.api.h
 ┃ ┃ ┃ ┃ ┃ ┣ 📜hello.api.h
 ┃ ┃ ┃ ┃ ┃ ┗ 📜io_world.h
 .. .
```

### Enums and Structures

Files `datastructs.api.h` and `datastructs.api.cpp` contain core data structures and enumerations used in your module.

#### Enums

Inside the `datastructs.api.h` you will find all the enums defined in your API. For each enum there is a `enum class` generated with all the values defined.

For convenience of use each enum has a `toEnum` function, which converts given `uint8_t` to enum value.

#### Structs

All structs defined in your API are generated in `datastructs.api.h` and `datastructs.api.cpp` files. They are used to communicate data between your API and its users.

For convenience of use each structure has:

- equality comparison operators
- empty constructor and a constructor with parameters for all its fields.

### Interfaces

For each interface inside an AP module there is separate file generated, like the `📜hello.api.h`.

The interface class contains pure virtual functions as well as pure virtual subscriber and publisher classes.

The interface has:

- pure virtual `getters` and a `setters` for each property

  ```cpp
  virtual void setLast(const Message& last) = 0;
  virtual const Message& getLast() const = 0;
  ```

- pure virtual functions for each operation

  ```cpp
  virtual int say(const Message& msg, When::WhenEnum when) = 0;
  ```

- and their asynchronous versions

  ```cpp
  virtual std::future<int> sayAsync(const Message& msg, WhenEnum when) = 0;
  ```

- an access to a publisher

  The interface does not contain signals defined in your interface, the signals feature is achieved with a subscriber/publisher mechanism.

A class interested in notification on signal emission (and property changes) needs to use the publisher to subscribe for those events.
The important thing is that your implementation of the interface should notify the `IHelloPublisher` about emitted signals or state changed.

:::note
Notice the convention for the getter - we use an underscore `_` - this function is added by the generator to your interface. The underscore is used to prevent name collision with your implementation of the interface.

```cpp
virtual IHelloPublisher& _getPublisher() const = 0;
```

:::

#### Publisher

The `IHelloPublisher` provides the interface for subscribing and unsubscribing from a signal emission
or a property change. Use of such a class is mandatory for implementation and allows users of your API to react on changes.

The publisher is responsible for keeping its clients informed about requested changes. But it is the interface (here `IHello`) implementation responsibility
to call the publish functions from its API when signal or property change occurs e.g:

```cpp IHello implementation
void Hello::setLast(const Message& last)
{
    ...
    // call the publish function
    m_publisher->publishLastChanged(last);

}
```

There are two ways of subscribing for changes.

Either provide an implementation for `ISubscriber` interface class and use is with those publisher's functions

```cpp
void subscribeToAllChanges(IHelloSubscriber& subscriber);
void unsubscribeFromAllChanges(IHelloSubscriber& subscriber);
```

The subscribe ISubscriber assures your subscriber will be informed about all emitted signals and all property changes.

The other option is to use the _parallel_ system of notification which doesn't require the `ISubscriber` and informs your Interface user about change of specific property or signal emission. E.g for `LastChanged` property we have:

```cpp
long subscribeToLastChanged(HelloLastPropertyCb callback); // returns handleId that needs to be used to unsubscribe
void unsubscribeFromLastChanged(long handleId);
```

The publisher will execute the provided callback function each time and only when this property is changed.

:::caution
For both methods of subscribing make sure to remove subscription for a ISubscriber/callback before it becomes invalid.
Also make sure that the subscribed function is not blocking and returns immediately!
:::

The publish functions need to be called by the implementation of the `IHello` on each property change or signal emission to notify all the subscribers about this change.

:::note
Subscriptions systems are parallel - if you use both of them for single interface user i.e subscribe your class as an `ISubscriber` and for a single change
your subscriber will be informed twice about that change, one for each subscription mechanism.

This means that the unsubscribe functions for both mechanisms work only for that mechanism, i.e. the unsubscribe with `ISubscriber` will not remove any subscriptions for the specific property/signal and they stay intact.
:::

#### Subscriber

For each interface we generate the `ISubscriber`, for example here the `IHelloSubscriber` which contains a set of functions for all the properties and signals for the notification mechanism.

The implementation for `IHello` contains a publisher which can be used to subscribe for those changes called `IHelloSubscriber`. Each time publisher will receive publish request it will notify all subscribed `IHelloSubscriber` object about change.
You can use `IHelloSubscriber` class to implement your local clients of the `IHello` or a network service adapter - see [Olink Server](olink.md#olink-server-adapter).

Below is a small code snippet which shows an example implementation for `IHelloSubscriber`, a class which main functionality is reacting on changes in `Hello`.

```cpp
class HelloUser : public IHelloSubscriber
{
public:
    HelloUser(IHello& Hello)
    : m_Hello(Hello)
    {
        m_Hello._getPublisher().subscribeToAllChanges(*this);
    }
     ~HelloUser()
     {
          m_Hello._getPublisher().unsubscribeFromAllChanges(*this);
     }

    void onJustSaid(const Message& /*msg*/) override
    {
        // do something with msg.
    }

    void onLastChanged(const Message& /*last*/) override
    {
        // do something with last;
    }
    // Some other functionality.
private:
    IHello& m_Hello
}

```

### Other

`📜 CMakeLists.txt` for building this module, describing it's dependencies, and exposing built package for other features that will use it. <br />
`📜 common.h` prepares dll import/export statements.
