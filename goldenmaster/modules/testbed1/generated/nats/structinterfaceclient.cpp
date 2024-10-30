#include "testbed1/generated/nats/structinterfaceclient.h"
#include "testbed1/generated/core/structinterface.publisher.h"
#include "testbed1/generated/core/testbed1.json.adapter.h"

using namespace Test::Testbed1;
using namespace Test::Testbed1::Nats;


StructInterfaceClient::StructInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client)
    : m_client(client)
    , m_publisher(std::make_unique<StructInterfacePublisher>())
{
}

StructInterfaceClient::~StructInterfaceClient()
{
}

void StructInterfaceClient::setPropBool(const StructBool& propBool)
{
    if(m_client == nullptr) {
        return;
    }
    (void) propBool;
    //TODO
}

void StructInterfaceClient::setPropBoolLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const StructBool& propBool = fields.get<StructBool>();
    if (m_data.m_propBool != propBool) {
        m_data.m_propBool = propBool;
        m_publisher->publishPropBoolChanged(propBool);
    }
}

const StructBool& StructInterfaceClient::getPropBool() const
{
    return m_data.m_propBool;
}

void StructInterfaceClient::setPropInt(const StructInt& propInt)
{
    if(m_client == nullptr) {
        return;
    }
    (void) propInt;
    //TODO
}

void StructInterfaceClient::setPropIntLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const StructInt& propInt = fields.get<StructInt>();
    if (m_data.m_propInt != propInt) {
        m_data.m_propInt = propInt;
        m_publisher->publishPropIntChanged(propInt);
    }
}

const StructInt& StructInterfaceClient::getPropInt() const
{
    return m_data.m_propInt;
}

void StructInterfaceClient::setPropFloat(const StructFloat& propFloat)
{
    if(m_client == nullptr) {
        return;
    }
    (void) propFloat;
    //TODO
}

void StructInterfaceClient::setPropFloatLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const StructFloat& propFloat = fields.get<StructFloat>();
    if (m_data.m_propFloat != propFloat) {
        m_data.m_propFloat = propFloat;
        m_publisher->publishPropFloatChanged(propFloat);
    }
}

const StructFloat& StructInterfaceClient::getPropFloat() const
{
    return m_data.m_propFloat;
}

void StructInterfaceClient::setPropString(const StructString& propString)
{
    if(m_client == nullptr) {
        return;
    }
    (void) propString;
    //TODO
}

void StructInterfaceClient::setPropStringLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    const StructString& propString = fields.get<StructString>();
    if (m_data.m_propString != propString) {
        m_data.m_propString = propString;
        m_publisher->publishPropStringChanged(propString);
    }
}

const StructString& StructInterfaceClient::getPropString() const
{
    return m_data.m_propString;
}

StructBool StructInterfaceClient::funcBool(const StructBool& paramBool)
{
    if(m_client == nullptr) {
        return StructBool();
    }
    StructBool value(funcBoolAsync(paramBool).get());
    return value;
}

std::future<StructBool> StructInterfaceClient::funcBoolAsync(const StructBool& paramBool)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    paramBool]()
        {
            std::promise<StructBool> resultPromise;
            //TODO 
            return resultPromise.get_future().get();
        }
    );
}

StructBool StructInterfaceClient::funcInt(const StructInt& paramInt)
{
    if(m_client == nullptr) {
        return StructBool();
    }
    StructBool value(funcIntAsync(paramInt).get());
    return value;
}

std::future<StructBool> StructInterfaceClient::funcIntAsync(const StructInt& paramInt)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    paramInt]()
        {
            std::promise<StructBool> resultPromise;
            //TODO 
            return resultPromise.get_future().get();
        }
    );
}

StructFloat StructInterfaceClient::funcFloat(const StructFloat& paramFloat)
{
    if(m_client == nullptr) {
        return StructFloat();
    }
    StructFloat value(funcFloatAsync(paramFloat).get());
    return value;
}

std::future<StructFloat> StructInterfaceClient::funcFloatAsync(const StructFloat& paramFloat)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    paramFloat]()
        {
            std::promise<StructFloat> resultPromise;
            //TODO 
            return resultPromise.get_future().get();
        }
    );
}

StructString StructInterfaceClient::funcString(const StructString& paramString)
{
    if(m_client == nullptr) {
        return StructString();
    }
    StructString value(funcStringAsync(paramString).get());
    return value;
}

std::future<StructString> StructInterfaceClient::funcStringAsync(const StructString& paramString)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    paramString]()
        {
            std::promise<StructString> resultPromise;
            //TODO 
            return resultPromise.get_future().get();
        }
    );
}
void StructInterfaceClient::onSigBool(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigBool(json_args[0].get<StructBool>());
}
void StructInterfaceClient::onSigInt(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigInt(json_args[0].get<StructInt>());
}
void StructInterfaceClient::onSigFloat(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigFloat(json_args[0].get<StructFloat>());
}
void StructInterfaceClient::onSigString(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSigString(json_args[0].get<StructString>());
}


IStructInterfacePublisher& StructInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
