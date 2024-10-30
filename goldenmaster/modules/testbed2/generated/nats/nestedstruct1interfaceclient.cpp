#include "testbed2/generated/nats/nestedstruct1interfaceclient.h"
#include "testbed2/generated/core/nestedstruct1interface.publisher.h"
#include "testbed2/generated/core/testbed2.json.adapter.h"

using namespace Test::Testbed2;
using namespace Test::Testbed2::Nats;


NestedStruct1InterfaceClient::NestedStruct1InterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    : m_client(client)
    , m_publisher(std::make_unique<NestedStruct1InterfacePublisher>())
{
}

NestedStruct1InterfaceClient::~NestedStruct1InterfaceClient()
{
}

void NestedStruct1InterfaceClient::setProp1(const NestedStruct1& prop1)
{
    if(m_client == nullptr) {
        return;
    }
    (void) prop1;
    //TODO
}

void NestedStruct1InterfaceClient::setProp1Local(const std::string& args)
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

const NestedStruct1& NestedStruct1InterfaceClient::getProp1() const
{
    return m_data.m_prop1;
}

NestedStruct1 NestedStruct1InterfaceClient::func1(const NestedStruct1& param1)
{
    if(m_client == nullptr) {
        return NestedStruct1();
    }
    NestedStruct1 value(func1Async(param1).get());
    return value;
}

std::future<NestedStruct1> NestedStruct1InterfaceClient::func1Async(const NestedStruct1& param1)
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
void NestedStruct1InterfaceClient::onSig1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig1(json_args[0].get<NestedStruct1>());
}


INestedStruct1InterfacePublisher& NestedStruct1InterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
