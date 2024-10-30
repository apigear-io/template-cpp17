#include "testbed1/generated/nats/structarrayinterfaceclient.h"
#include "testbed1/generated/core/structarrayinterface.publisher.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"

using namespace Test::Testbed1;
using namespace Test::Testbed1::Nats;


StructArrayInterfaceClient::StructArrayInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    : m_client(client)
    , m_publisher(std::make_unique<StructArrayInterfacePublisher>())
{
}

StructArrayInterfaceClient::~StructArrayInterfaceClient()
{
}

void StructArrayInterfaceClient::setPropBool(const std::list<StructBool>& propBool)
{
    if(m_client == nullptr) {
        return;
    }
    (void) propBool;
    //TODO
}

void StructArrayInterfaceClient::setPropBoolLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::list<StructBool>& propBool = fields.get<std::list<StructBool>>();
    if (m_data.m_propBool != propBool) {
        m_data.m_propBool = propBool;
        m_publisher->publishPropBoolChanged(propBool);
    }
}

const std::list<StructBool>& StructArrayInterfaceClient::getPropBool() const
{
    return m_data.m_propBool;
}

void StructArrayInterfaceClient::setPropInt(const std::list<StructInt>& propInt)
{
    if(m_client == nullptr) {
        return;
    }
    (void) propInt;
    //TODO
}

void StructArrayInterfaceClient::setPropIntLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::list<StructInt>& propInt = fields.get<std::list<StructInt>>();
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

const std::list<StructInt>& StructArrayInterfaceClient::getPropInt() const
{
    return m_data.m_propInt;
}

void StructArrayInterfaceClient::setPropFloat(const std::list<StructFloat>& propFloat)
{
    if(m_client == nullptr) {
        return;
    }
    (void) propFloat;
    //TODO
}

void StructArrayInterfaceClient::setPropFloatLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::list<StructFloat>& propFloat = fields.get<std::list<StructFloat>>();
    if (m_data.m_propFloat != propFloat) {
        m_data.m_propFloat = propFloat;
        m_publisher->publishPropFloatChanged(propFloat);
    }
}

const std::list<StructFloat>& StructArrayInterfaceClient::getPropFloat() const
{
    return m_data.m_propFloat;
}

void StructArrayInterfaceClient::setPropString(const std::list<StructString>& propString)
{
    if(m_client == nullptr) {
        return;
    }
    (void) propString;
    //TODO
}

void StructArrayInterfaceClient::setPropStringLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const std::list<StructString>& propString = fields.get<std::list<StructString>>();
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const std::list<StructString>& StructArrayInterfaceClient::getPropString() const
{
    return m_data.m_propString;
}

std::list<StructBool> StructArrayInterfaceClient::funcBool(const std::list<StructBool>& paramBool)
{
    if(m_client == nullptr) {
        return std::list<StructBool>();
    }
    std::list<StructBool> value(funcBoolAsync(paramBool).get());
    return value;
}

std::future<std::list<StructBool>> StructArrayInterfaceClient::funcBoolAsync(const std::list<StructBool>& paramBool)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    paramBool]()
        {
            std::promise<std::list<StructBool>> resultPromise;
            //TODO 
            return resultPromise.get_future().get();
        }
    );
}

std::list<StructInt> StructArrayInterfaceClient::funcInt(const std::list<StructInt>& paramInt)
{
    if(m_client == nullptr) {
        return std::list<StructInt>();
    }
    std::list<StructInt> value(funcIntAsync(paramInt).get());
    return value;
}

std::future<std::list<StructInt>> StructArrayInterfaceClient::funcIntAsync(const std::list<StructInt>& paramInt)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    paramInt]()
        {
            std::promise<std::list<StructInt>> resultPromise;
            //TODO 
            return resultPromise.get_future().get();
        }
    );
}

std::list<StructFloat> StructArrayInterfaceClient::funcFloat(const std::list<StructFloat>& paramFloat)
{
    if(m_client == nullptr) {
        return std::list<StructFloat>();
    }
    std::list<StructFloat> value(funcFloatAsync(paramFloat).get());
    return value;
}

std::future<std::list<StructFloat>> StructArrayInterfaceClient::funcFloatAsync(const std::list<StructFloat>& paramFloat)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    paramFloat]()
        {
            std::promise<std::list<StructFloat>> resultPromise;
            //TODO 
            return resultPromise.get_future().get();
        }
    );
}

std::list<StructString> StructArrayInterfaceClient::funcString(const std::list<StructString>& paramString)
{
    if(m_client == nullptr) {
        return std::list<StructString>();
    }
    std::list<StructString> value(funcStringAsync(paramString).get());
    return value;
}

std::future<std::list<StructString>> StructArrayInterfaceClient::funcStringAsync(const std::list<StructString>& paramString)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    paramString]()
        {
            std::promise<std::list<StructString>> resultPromise;
            //TODO 
            return resultPromise.get_future().get();
        }
    );
}
void StructArrayInterfaceClient::onSigBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigBool(json_args[0].get<std::list<StructBool>>());
}
void StructArrayInterfaceClient::onSigInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigInt(json_args[0].get<std::list<StructInt>>());
}
void StructArrayInterfaceClient::onSigFloat(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigFloat(json_args[0].get<std::list<StructFloat>>());
}
void StructArrayInterfaceClient::onSigString(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigString(json_args[0].get<std::list<StructString>>());
}


IStructArrayInterfacePublisher& StructArrayInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
