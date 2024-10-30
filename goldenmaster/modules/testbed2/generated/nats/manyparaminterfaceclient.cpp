#include "testbed2/generated/nats/manyparaminterfaceclient.h"
#include "testbed2/generated/core/manyparaminterface.publisher.h"
#include "testbed2/generated/core/testbed2.json.adapter.h"

using namespace Test::Testbed2;
using namespace Test::Testbed2::Nats;


ManyParamInterfaceClient::ManyParamInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    : m_client(client)
    , m_publisher(std::make_unique<ManyParamInterfacePublisher>())
{
}

ManyParamInterfaceClient::~ManyParamInterfaceClient()
{
}

void ManyParamInterfaceClient::setProp1(int prop1)
{
    if(m_client == nullptr) {
        return;
    }
    (void) prop1;
    //TODO
}

void ManyParamInterfaceClient::setProp1Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    int prop1 = fields.get<int>();
    if (m_data.m_prop1 != prop1) {
        m_data.m_prop1 = prop1;
        m_publisher->publishProp1Changed(prop1);
    }
}

int ManyParamInterfaceClient::getProp1() const
{
    return m_data.m_prop1;
}

void ManyParamInterfaceClient::setProp2(int prop2)
{
    if(m_client == nullptr) {
        return;
    }
    (void) prop2;
    //TODO
}

void ManyParamInterfaceClient::setProp2Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    int prop2 = fields.get<int>();
    if (m_data.m_prop2 != prop2) {
        m_data.m_prop2 = prop2;
        m_publisher->publishProp2Changed(prop2);
    }
}

int ManyParamInterfaceClient::getProp2() const
{
    return m_data.m_prop2;
}

void ManyParamInterfaceClient::setProp3(int prop3)
{
    if(m_client == nullptr) {
        return;
    }
    (void) prop3;
    //TODO
}

void ManyParamInterfaceClient::setProp3Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    int prop3 = fields.get<int>();
    if (m_data.m_prop3 != prop3) {
        m_data.m_prop3 = prop3;
        m_publisher->publishProp3Changed(prop3);
    }
}

int ManyParamInterfaceClient::getProp3() const
{
    return m_data.m_prop3;
}

void ManyParamInterfaceClient::setProp4(int prop4)
{
    if(m_client == nullptr) {
        return;
    }
    (void) prop4;
    //TODO
}

void ManyParamInterfaceClient::setProp4Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    int prop4 = fields.get<int>();
    if (m_data.m_prop4 != prop4) {
        m_data.m_prop4 = prop4;
        m_publisher->publishProp4Changed(prop4);
    }
}

int ManyParamInterfaceClient::getProp4() const
{
    return m_data.m_prop4;
}

int ManyParamInterfaceClient::func1(int param1)
{
    if(m_client == nullptr) {
        return 0;
    }
    int value(func1Async(param1).get());
    return value;
}

std::future<int> ManyParamInterfaceClient::func1Async(int param1)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    param1]()
        {
            std::promise<int> resultPromise;
            //TODO 
            return resultPromise.get_future().get();
        }
    );
}

int ManyParamInterfaceClient::func2(int param1, int param2)
{
    if(m_client == nullptr) {
        return 0;
    }
    int value(func2Async(param1, param2).get());
    return value;
}

std::future<int> ManyParamInterfaceClient::func2Async(int param1, int param2)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    param1,
                    param2]()
        {
            std::promise<int> resultPromise;
            //TODO 
            return resultPromise.get_future().get();
        }
    );
}

int ManyParamInterfaceClient::func3(int param1, int param2, int param3)
{
    if(m_client == nullptr) {
        return 0;
    }
    int value(func3Async(param1, param2, param3).get());
    return value;
}

std::future<int> ManyParamInterfaceClient::func3Async(int param1, int param2, int param3)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    param1,
                    param2,
                    param3]()
        {
            std::promise<int> resultPromise;
            //TODO 
            return resultPromise.get_future().get();
        }
    );
}

int ManyParamInterfaceClient::func4(int param1, int param2, int param3, int param4)
{
    if(m_client == nullptr) {
        return 0;
    }
    int value(func4Async(param1, param2, param3, param4).get());
    return value;
}

std::future<int> ManyParamInterfaceClient::func4Async(int param1, int param2, int param3, int param4)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    param1,
                    param2,
                    param3,
                    param4]()
        {
            std::promise<int> resultPromise;
            //TODO 
            return resultPromise.get_future().get();
        }
    );
}
void ManyParamInterfaceClient::onSig1(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig1(json_args[0].get<int>());
}
void ManyParamInterfaceClient::onSig2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig2(json_args[0].get<int>(),json_args[1].get<int>());
}
void ManyParamInterfaceClient::onSig3(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig3(json_args[0].get<int>(),json_args[1].get<int>(),json_args[2].get<int>());
}
void ManyParamInterfaceClient::onSig4(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSig4(json_args[0].get<int>(),json_args[1].get<int>(),json_args[2].get<int>(),json_args[3].get<int>());
}


IManyParamInterfacePublisher& ManyParamInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
