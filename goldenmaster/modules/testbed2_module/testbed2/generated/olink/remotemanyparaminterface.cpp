

#include "testbed2/generated/olink/remotemanyparaminterface.h"
#include "testbed2/generated/core/manyparaminterface.publisher.h"
#include "testbed2/generated/core/testbed2.json.adapter.h"

using namespace Test::Testbed2;
using namespace Test::Testbed2::olink;

RemoteManyParamInterface::RemoteManyParamInterface(ApiGear::ObjectLink::ClientRegistry& registry, ApiGear::PocoImpl::OLinkClient& client)
    : m_registry(registry),
      m_publisher(std::make_unique<ManyParamInterfacePublisher>())
{
    m_registry.addObjectSink(this);
    client.linkObjectSource("testbed2.ManyParamInterface");
}

RemoteManyParamInterface::~RemoteManyParamInterface()
{
    m_registry.removeObjectSink(this);
}

void RemoteManyParamInterface::applyState(const nlohmann::json& fields) 
{
    if(fields.contains("prop1")) {
        setProp1Local(fields["prop1"].get<int>());
    }
    if(fields.contains("prop2")) {
        setProp2Local(fields["prop2"].get<int>());
    }
    if(fields.contains("prop3")) {
        setProp3Local(fields["prop3"].get<int>());
    }
    if(fields.contains("prop4")) {
        setProp4Local(fields["prop4"].get<int>());
    }
}

void RemoteManyParamInterface::setProp1(int prop1)
{
    if(m_node == nullptr) {
        return;
    }
    m_node->setRemoteProperty("testbed2.ManyParamInterface/prop1", prop1);
}

void RemoteManyParamInterface::setProp1Local(int prop1)
{
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

int RemoteManyParamInterface::getProp1() const
{
    return m_data.m_prop1;
}

void RemoteManyParamInterface::setProp2(int prop2)
{
    if(m_node == nullptr) {
        return;
    }
    m_node->setRemoteProperty("testbed2.ManyParamInterface/prop2", prop2);
}

void RemoteManyParamInterface::setProp2Local(int prop2)
{
    if (m_data.m_prop2 != prop2) {
        m_data.m_prop2 = prop2;
        m_publisher->publishProp2Changed(prop2);
    }
}

int RemoteManyParamInterface::getProp2() const
{
    return m_data.m_prop2;
}

void RemoteManyParamInterface::setProp3(int prop3)
{
    if(m_node == nullptr) {
        return;
    }
    m_node->setRemoteProperty("testbed2.ManyParamInterface/prop3", prop3);
}

void RemoteManyParamInterface::setProp3Local(int prop3)
{
    if (m_data.m_prop3 != prop3) {
        m_data.m_prop3 = prop3;
        m_publisher->publishProp3Changed(prop3);
    }
}

int RemoteManyParamInterface::getProp3() const
{
    return m_data.m_prop3;
}

void RemoteManyParamInterface::setProp4(int prop4)
{
    if(m_node == nullptr) {
        return;
    }
    m_node->setRemoteProperty("testbed2.ManyParamInterface/prop4", prop4);
}

void RemoteManyParamInterface::setProp4Local(int prop4)
{
    if (m_data.m_prop4 != prop4) {
        m_data.m_prop4 = prop4;
        m_publisher->publishProp4Changed(prop4);
    }
}

int RemoteManyParamInterface::getProp4() const
{
    return m_data.m_prop4;
}

int RemoteManyParamInterface::func1(int param1)
{
    if(m_node == nullptr) {
        return 0;
    }
    int value(func1Async(param1).get());
    return value;
}

std::future<int> RemoteManyParamInterface::func1Async(int param1)
{
    if(m_node == nullptr) {
        throw std::runtime_error("Node is not initialized");
    }
    return std::async(std::launch::async, [this,
                    param1]()
        {
            std::promise<int> resultPromise;
            m_node->invokeRemote("testbed2.ManyParamInterface/func1",
                nlohmann::json::array({param1}), [&resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
                    const int& value = arg.value.get<int>();
                    resultPromise.set_value(value);
                });
            return resultPromise.get_future().get();
        }
    );
}

int RemoteManyParamInterface::func2(int param1, int param2)
{
    if(m_node == nullptr) {
        return 0;
    }
    int value(func2Async(param1, param2).get());
    return value;
}

std::future<int> RemoteManyParamInterface::func2Async(int param1, int param2)
{
    if(m_node == nullptr) {
        throw std::runtime_error("Node is not initialized");
    }
    return std::async(std::launch::async, [this,
                    param1,
                    param2]()
        {
            std::promise<int> resultPromise;
            m_node->invokeRemote("testbed2.ManyParamInterface/func2",
                nlohmann::json::array({param1,param2}), [&resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
                    const int& value = arg.value.get<int>();
                    resultPromise.set_value(value);
                });
            return resultPromise.get_future().get();
        }
    );
}

int RemoteManyParamInterface::func3(int param1, int param2, int param3)
{
    if(m_node == nullptr) {
        return 0;
    }
    int value(func3Async(param1, param2, param3).get());
    return value;
}

std::future<int> RemoteManyParamInterface::func3Async(int param1, int param2, int param3)
{
    if(m_node == nullptr) {
        throw std::runtime_error("Node is not initialized");
    }
    return std::async(std::launch::async, [this,
                    param1,
                    param2,
                    param3]()
        {
            std::promise<int> resultPromise;
            m_node->invokeRemote("testbed2.ManyParamInterface/func3",
                nlohmann::json::array({param1,param2,param3}), [&resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
                    const int& value = arg.value.get<int>();
                    resultPromise.set_value(value);
                });
            return resultPromise.get_future().get();
        }
    );
}

int RemoteManyParamInterface::func4(int param1, int param2, int param3, int param4)
{
    if(m_node == nullptr) {
        return 0;
    }
    int value(func4Async(param1, param2, param3, param4).get());
    return value;
}

std::future<int> RemoteManyParamInterface::func4Async(int param1, int param2, int param3, int param4)
{
    if(m_node == nullptr) {
        throw std::runtime_error("Node is not initialized");
    }
    return std::async(std::launch::async, [this,
                    param1,
                    param2,
                    param3,
                    param4]()
        {
            std::promise<int> resultPromise;
            m_node->invokeRemote("testbed2.ManyParamInterface/func4",
                nlohmann::json::array({param1,param2,param3,param4}), [&resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
                    const int& value = arg.value.get<int>();
                    resultPromise.set_value(value);
                });
            return resultPromise.get_future().get();
        }
    );
}

std::string RemoteManyParamInterface::olinkObjectName()
{
    return "testbed2.ManyParamInterface";
}

void RemoteManyParamInterface::olinkOnSignal(std::string name, nlohmann::json args)
{
    std::string path = ApiGear::ObjectLink::Name::pathFromName(name);
    if(path == "sig1") {
        m_publisher->publishSig1(args[0].get<int>());   
        return;
    }
    if(path == "sig2") {
        m_publisher->publishSig2(args[0].get<int>(),args[1].get<int>());   
        return;
    }
    if(path == "sig3") {
        m_publisher->publishSig3(args[0].get<int>(),args[1].get<int>(),args[2].get<int>());   
        return;
    }
    if(path == "sig4") {
        m_publisher->publishSig4(args[0].get<int>(),args[1].get<int>(),args[2].get<int>(),args[3].get<int>());   
        return;
    }
}

void RemoteManyParamInterface::olinkOnPropertyChanged(std::string name, nlohmann::json value)
{
    std::string path = ApiGear::ObjectLink::Name::pathFromName(name);
    applyState({ {path, value} });
}
void RemoteManyParamInterface::olinkOnInit(std::string name, nlohmann::json props, ApiGear::ObjectLink::IClientNode *node)
{
    (void) name; //suppress the 'Unreferenced Formal Parameter' warning.
    m_node = node;
    applyState(props);
}

void RemoteManyParamInterface::olinkOnRelease()
{
    m_node = nullptr;
}

bool RemoteManyParamInterface::isReady() const
{
    return m_node != nullptr;
}

IManyParamInterfacePublisher& RemoteManyParamInterface::_getPublisher() const
{
    return *m_publisher;
}
