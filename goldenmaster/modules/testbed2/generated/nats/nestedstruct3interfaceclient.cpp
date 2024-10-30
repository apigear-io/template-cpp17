#include "testbed2/generated/nats/nestedstruct3interfaceclient.h"
#include "testbed2/generated/core/nestedstruct3interface.publisher.h"
#include "testbed2/generated/core/testbed2.json.adapter.h"

using namespace Test::Testbed2;
using namespace Test::Testbed2::Nats;


NestedStruct3InterfaceClient::NestedStruct3InterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    : m_client(client)
    , m_publisher(std::make_unique<NestedStruct3InterfacePublisher>())
{
}

NestedStruct3InterfaceClient::~NestedStruct3InterfaceClient()
{
}

void NestedStruct3InterfaceClient::setProp1(const NestedStruct1& prop1)
{
    if(m_client == nullptr) {
        return;
    }
    (void) prop1;
    //TODO
}

void NestedStruct3InterfaceClient::setProp1Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const NestedStruct1& prop1 = fields.get<NestedStruct1>();
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

const NestedStruct1& NestedStruct3InterfaceClient::getProp1() const
{
    return m_data.m_prop1;
}

void NestedStruct3InterfaceClient::setProp2(const NestedStruct2& prop2)
{
    if(m_client == nullptr) {
        return;
    }
    (void) prop2;
    //TODO
}

void NestedStruct3InterfaceClient::setProp2Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const NestedStruct2& prop2 = fields.get<NestedStruct2>();
    if (m_data.m_prop2 != prop2) {
        m_data.m_prop2 = prop2;
        m_publisher->publishProp2Changed(prop2);
    }
}

const NestedStruct2& NestedStruct3InterfaceClient::getProp2() const
{
    return m_data.m_prop2;
}

void NestedStruct3InterfaceClient::setProp3(const NestedStruct3& prop3)
{
    if(m_client == nullptr) {
        return;
    }
    (void) prop3;
    //TODO
}

void NestedStruct3InterfaceClient::setProp3Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const NestedStruct3& prop3 = fields.get<NestedStruct3>();
    if (m_data.m_prop3 != prop3) {
        m_data.m_prop3 = prop3;
        m_publisher->publishProp3Changed(prop3);
    }
}

const NestedStruct3& NestedStruct3InterfaceClient::getProp3() const
{
    return m_data.m_prop3;
}

NestedStruct1 NestedStruct3InterfaceClient::func1(const NestedStruct1& param1)
{
    if(m_client == nullptr) {
        return NestedStruct1();
    }
    NestedStruct1 value(func1Async(param1).get());
    return value;
}

std::future<NestedStruct1> NestedStruct3InterfaceClient::func1Async(const NestedStruct1& param1)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    param1]()
        {
            std::promise<NestedStruct1> resultPromise;
            //TODO 
            return resultPromise.get_future().get();
        }
    );
}

NestedStruct1 NestedStruct3InterfaceClient::func2(const NestedStruct1& param1, const NestedStruct2& param2)
{
    if(m_client == nullptr) {
        return NestedStruct1();
    }
    NestedStruct1 value(func2Async(param1, param2).get());
    return value;
}

std::future<NestedStruct1> NestedStruct3InterfaceClient::func2Async(const NestedStruct1& param1, const NestedStruct2& param2)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    param1,
                    param2]()
        {
            std::promise<NestedStruct1> resultPromise;
            //TODO 
            return resultPromise.get_future().get();
        }
    );
}

NestedStruct1 NestedStruct3InterfaceClient::func3(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3)
{
    if(m_client == nullptr) {
        return NestedStruct1();
    }
    NestedStruct1 value(func3Async(param1, param2, param3).get());
    return value;
}

std::future<NestedStruct1> NestedStruct3InterfaceClient::func3Async(const NestedStruct1& param1, const NestedStruct2& param2, const NestedStruct3& param3)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    param1,
                    param2,
                    param3]()
        {
            std::promise<NestedStruct1> resultPromise;
            //TODO 
            return resultPromise.get_future().get();
        }
    );
}
void NestedStruct3InterfaceClient::onSig1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig1(json_args[0].get<NestedStruct1>());
}
void NestedStruct3InterfaceClient::onSig2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig2(json_args[0].get<NestedStruct1>(),json_args[1].get<NestedStruct2>());
}
void NestedStruct3InterfaceClient::onSig3(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig3(json_args[0].get<NestedStruct1>(),json_args[1].get<NestedStruct2>(),json_args[2].get<NestedStruct3>());
}


INestedStruct3InterfacePublisher& NestedStruct3InterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
