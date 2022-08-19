

#include "tb_same1/generated/olink/remotesameenum2interface.h"
#include "tb_same1/generated/core/sameenum2interface.publisher.h"
#include "tb_same1/generated/core/tb_same1.json.adapter.h"

using namespace Test::TbSame1;
using namespace Test::TbSame1::olink;

RemoteSameEnum2Interface::RemoteSameEnum2Interface(ApiGear::ObjectLink::ClientRegistry& registry, ApiGear::PocoImpl::OLinkClient& client)
    : m_registry(registry),
      m_publisher(std::make_unique<SameEnum2InterfacePublisher>())
{
    m_registry.addObjectSink(this);
    client.linkObjectSource("tb.same1.SameEnum2Interface");
}

RemoteSameEnum2Interface::~RemoteSameEnum2Interface()
{
    m_registry.removeObjectSink(this);
}

void RemoteSameEnum2Interface::applyState(const nlohmann::json& fields) 
{
    if(fields.contains("prop1")) {
        setProp1Local(fields["prop1"].get<Enum1Enum>());
    }
    if(fields.contains("prop2")) {
        setProp2Local(fields["prop2"].get<Enum2Enum>());
    }
}

void RemoteSameEnum2Interface::setProp1(const Enum1Enum& prop1)
{
    if(m_node == nullptr) {
        return;
    }
    m_node->setRemoteProperty("tb.same1.SameEnum2Interface/prop1", prop1);
}

void RemoteSameEnum2Interface::setProp1Local(const Enum1Enum& prop1)
{
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

const Enum1Enum& RemoteSameEnum2Interface::getProp1() const
{
    return m_data.m_prop1;
}

void RemoteSameEnum2Interface::setProp2(const Enum2Enum& prop2)
{
    if(m_node == nullptr) {
        return;
    }
    m_node->setRemoteProperty("tb.same1.SameEnum2Interface/prop2", prop2);
}

void RemoteSameEnum2Interface::setProp2Local(const Enum2Enum& prop2)
{
    if (m_data.m_prop2 != prop2) {
        m_data.m_prop2 = prop2;
        m_publisher->publishProp2Changed(prop2);
    }
}

const Enum2Enum& RemoteSameEnum2Interface::getProp2() const
{
    return m_data.m_prop2;
}

Enum1Enum RemoteSameEnum2Interface::func1(const Enum1Enum& param1)
{
    if(m_node == nullptr) {
        return Enum1Enum::value1;
    }
    Enum1Enum value(func1Async(param1).get());
    return value;
}

std::future<Enum1Enum> RemoteSameEnum2Interface::func1Async(const Enum1Enum& param1)
{
    if(m_node == nullptr) {
        throw std::runtime_error("Node is not initialized");
    }
    return std::async(std::launch::async, [this,
                    param1]()
        {
            std::promise<Enum1Enum> resultPromise;
            m_node->invokeRemote("tb.same1.SameEnum2Interface/func1",
                nlohmann::json::array({param1}), [&resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
                    const Enum1Enum& value = arg.value.get<Enum1Enum>();
                    resultPromise.set_value(value);
                });
            return resultPromise.get_future().get();
        }
    );
}

Enum1Enum RemoteSameEnum2Interface::func2(const Enum1Enum& param1, const Enum2Enum& param2)
{
    if(m_node == nullptr) {
        return Enum1Enum::value1;
    }
    Enum1Enum value(func2Async(param1, param2).get());
    return value;
}

std::future<Enum1Enum> RemoteSameEnum2Interface::func2Async(const Enum1Enum& param1, const Enum2Enum& param2)
{
    if(m_node == nullptr) {
        throw std::runtime_error("Node is not initialized");
    }
    return std::async(std::launch::async, [this,
                    param1,
                    param2]()
        {
            std::promise<Enum1Enum> resultPromise;
            m_node->invokeRemote("tb.same1.SameEnum2Interface/func2",
                nlohmann::json::array({param1,param2}), [&resultPromise](ApiGear::ObjectLink::InvokeReplyArg arg) {
                    const Enum1Enum& value = arg.value.get<Enum1Enum>();
                    resultPromise.set_value(value);
                });
            return resultPromise.get_future().get();
        }
    );
}

std::string RemoteSameEnum2Interface::olinkObjectName()
{
    return "tb.same1.SameEnum2Interface";
}

void RemoteSameEnum2Interface::olinkOnSignal(std::string name, nlohmann::json args)
{
    std::string path = ApiGear::ObjectLink::Name::pathFromName(name);
    if(path == "sig1") {
        m_publisher->publishSig1(args[0].get<Enum1Enum>());   
        return;
    }
    if(path == "sig2") {
        m_publisher->publishSig2(args[0].get<Enum1Enum>(),args[1].get<Enum2Enum>());   
        return;
    }
}

void RemoteSameEnum2Interface::olinkOnPropertyChanged(std::string name, nlohmann::json value)
{
    std::string path = ApiGear::ObjectLink::Name::pathFromName(name);
    applyState({ {path, value} });
}
void RemoteSameEnum2Interface::olinkOnInit(std::string name, nlohmann::json props, ApiGear::ObjectLink::IClientNode *node)
{
    (void) name; //suppress the 'Unreferenced Formal Parameter' warning.
    m_node = node;
    applyState(props);
}

void RemoteSameEnum2Interface::olinkOnRelease()
{
    m_node = nullptr;
}

bool RemoteSameEnum2Interface::isReady() const
{
    return m_node != nullptr;
}

ISameEnum2InterfacePublisher& RemoteSameEnum2Interface::_getPublisher() const
{
    return *m_publisher;
}
