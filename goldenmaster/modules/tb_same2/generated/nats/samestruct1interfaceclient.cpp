#include "tb_same2/generated/nats/samestruct1interfaceclient.h"
#include "tb_same2/generated/core/samestruct1interface.publisher.h"
#include "tb_same2/generated/core/tb_same2.json.adapter.h"

using namespace Test::TbSame2;
using namespace Test::TbSame2::Nats;


SameStruct1InterfaceClient::SameStruct1InterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    : m_client(client)
    , m_publisher(std::make_unique<SameStruct1InterfacePublisher>())
{
}

SameStruct1InterfaceClient::~SameStruct1InterfaceClient()
{
}

void SameStruct1InterfaceClient::setProp1(const Struct1& prop1)
{
    if(m_client == nullptr) {
        return;
    }
    (void) prop1;
    //TODO
}

void SameStruct1InterfaceClient::setProp1Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const Struct1& prop1 = fields.get<Struct1>();
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

const Struct1& SameStruct1InterfaceClient::getProp1() const
{
    return m_data.m_prop1;
}

Struct1 SameStruct1InterfaceClient::func1(const Struct1& param1)
{
    if(m_client == nullptr) {
        return Struct1();
    }
    Struct1 value(func1Async(param1).get());
    return value;
}

std::future<Struct1> SameStruct1InterfaceClient::func1Async(const Struct1& param1)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    param1]()
        {
            std::promise<Struct1> resultPromise;
            //TODO 
            return resultPromise.get_future().get();
        }
    );
}
void SameStruct1InterfaceClient::onSig1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig1(json_args[0].get<Struct1>());
}


ISameStruct1InterfacePublisher& SameStruct1InterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
