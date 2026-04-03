#include "tb_struct_array/generated/mqtt/structarrayfieldinterfaceclient.h"
#include "tb_struct_array/generated/core/structarrayfieldinterface.publisher.h"
#include "tb_struct_array/generated/core/tb_struct_array.json.adapter.h"
#include "apigear/utilities/logger.h"
#include <random>

using namespace Test::TbStructArray;
using namespace Test::TbStructArray::MQTT;

namespace {
    std::mt19937 randomNumberGenerator (std::random_device{}());
}

StructArrayFieldInterfaceClient::StructArrayFieldInterfaceClient(std::shared_ptr<ApiGear::MQTT::Client> client)
    : MqttBaseAdapter(client, createTopicMap(client->getClientId()))
    , m_client(client)
    , m_publisher(std::make_unique<StructArrayFieldInterfacePublisher>())
{
}

std::shared_ptr<StructArrayFieldInterfaceClient> StructArrayFieldInterfaceClient::create(std::shared_ptr<ApiGear::MQTT::Client> client)
{
    return std::make_shared<StructArrayFieldInterfaceClient>(client);
}

StructArrayFieldInterfaceClient::~StructArrayFieldInterfaceClient()
{
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> StructArrayFieldInterfaceClient::createTopicMap(const std::string& clientId)
{
    return {
        { std::string("tb.struct.array/StructArrayFieldInterface/prop/propStructArray"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropStructArrayLocal(args); } },
        { std::string("tb.struct.array/StructArrayFieldInterface/prop/propEnumArray"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropEnumArrayLocal(args); } },
        { std::string("tb.struct.array/StructArrayFieldInterface/prop/propIntArray"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropIntArrayLocal(args); } },
        { std::string("tb.struct.array/StructArrayFieldInterface/prop/propMixed"), [this](const std::string& args, const std::string&, const std::string&){ this->setPropMixedLocal(args); } },
        { std::string("tb.struct.array/StructArrayFieldInterface/sig/sigMixed"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigMixed(args); } },
        { std::string("tb.struct.array/StructArrayFieldInterface/sig/sigStructArray"), [this](const std::string& args, const std::string&, const std::string&){ this->onSigStructArray(args); } },
        { std::string("tb.struct.array/StructArrayFieldInterface/rpc/funcMixed/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
        { std::string("tb.struct.array/StructArrayFieldInterface/rpc/funcStructArray/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
    };
};

void StructArrayFieldInterfaceClient::setPropStructArray(const StructWithArrayOfStructs& propStructArray)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("tb.struct.array/StructArrayFieldInterface/set/propStructArray");
    m_client->setRemoteProperty(topic, nlohmann::json(propStructArray).dump());
}

void StructArrayFieldInterfaceClient::setPropStructArrayLocal(const std::string& args)
{
    try {
        nlohmann::json fields = nlohmann::json::parse(args);
        if (fields.empty())
        {
            return;
        }

        const StructWithArrayOfStructs& propStructArray = fields.get<StructWithArrayOfStructs>();
        if (m_data.m_propStructArray != propStructArray) {
            m_data.m_propStructArray = propStructArray;
            m_publisher->publishPropStructArrayChanged(propStructArray);
        }
    } catch (const std::exception& e) {
        AG_LOG_ERROR("StructArrayFieldInterfaceClient JSON error: " + std::string(e.what()));
    }
}

const StructWithArrayOfStructs& StructArrayFieldInterfaceClient::getPropStructArray() const
{
    return m_data.m_propStructArray;
}

void StructArrayFieldInterfaceClient::setPropEnumArray(const StructWithArrayOfEnums& propEnumArray)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("tb.struct.array/StructArrayFieldInterface/set/propEnumArray");
    m_client->setRemoteProperty(topic, nlohmann::json(propEnumArray).dump());
}

void StructArrayFieldInterfaceClient::setPropEnumArrayLocal(const std::string& args)
{
    try {
        nlohmann::json fields = nlohmann::json::parse(args);
        if (fields.empty())
        {
            return;
        }

        const StructWithArrayOfEnums& propEnumArray = fields.get<StructWithArrayOfEnums>();
        if (m_data.m_propEnumArray != propEnumArray) {
            m_data.m_propEnumArray = propEnumArray;
            m_publisher->publishPropEnumArrayChanged(propEnumArray);
        }
    } catch (const std::exception& e) {
        AG_LOG_ERROR("StructArrayFieldInterfaceClient JSON error: " + std::string(e.what()));
    }
}

const StructWithArrayOfEnums& StructArrayFieldInterfaceClient::getPropEnumArray() const
{
    return m_data.m_propEnumArray;
}

void StructArrayFieldInterfaceClient::setPropIntArray(const StructWithArrayOfInts& propIntArray)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("tb.struct.array/StructArrayFieldInterface/set/propIntArray");
    m_client->setRemoteProperty(topic, nlohmann::json(propIntArray).dump());
}

void StructArrayFieldInterfaceClient::setPropIntArrayLocal(const std::string& args)
{
    try {
        nlohmann::json fields = nlohmann::json::parse(args);
        if (fields.empty())
        {
            return;
        }

        const StructWithArrayOfInts& propIntArray = fields.get<StructWithArrayOfInts>();
        if (m_data.m_propIntArray != propIntArray) {
            m_data.m_propIntArray = propIntArray;
            m_publisher->publishPropIntArrayChanged(propIntArray);
        }
    } catch (const std::exception& e) {
        AG_LOG_ERROR("StructArrayFieldInterfaceClient JSON error: " + std::string(e.what()));
    }
}

const StructWithArrayOfInts& StructArrayFieldInterfaceClient::getPropIntArray() const
{
    return m_data.m_propIntArray;
}

void StructArrayFieldInterfaceClient::setPropMixed(const MixedStruct& propMixed)
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("tb.struct.array/StructArrayFieldInterface/set/propMixed");
    m_client->setRemoteProperty(topic, nlohmann::json(propMixed).dump());
}

void StructArrayFieldInterfaceClient::setPropMixedLocal(const std::string& args)
{
    try {
        nlohmann::json fields = nlohmann::json::parse(args);
        if (fields.empty())
        {
            return;
        }

        const MixedStruct& propMixed = fields.get<MixedStruct>();
        if (m_data.m_propMixed != propMixed) {
            m_data.m_propMixed = propMixed;
            m_publisher->publishPropMixedChanged(propMixed);
        }
    } catch (const std::exception& e) {
        AG_LOG_ERROR("StructArrayFieldInterfaceClient JSON error: " + std::string(e.what()));
    }
}

const MixedStruct& StructArrayFieldInterfaceClient::getPropMixed() const
{
    return m_data.m_propMixed;
}

MixedStruct StructArrayFieldInterfaceClient::funcMixed(const MixedStruct& paramMixed)
{
    if(m_client == nullptr) {
        return MixedStruct();
    }
    MixedStruct value(funcMixedAsync(paramMixed).get());
    return value;
}

std::future<MixedStruct> StructArrayFieldInterfaceClient::funcMixedAsync(const MixedStruct& paramMixed, std::function<void(MixedStruct)> callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this, callback,
                    paramMixed]()
        {
            auto resultPromise = std::make_shared<std::promise<MixedStruct>>();
            static const auto topic = std::string("tb.struct.array/StructArrayFieldInterface/rpc/funcMixed");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [resultPromise, callback](ApiGear::MQTT::InvokeReplyArg arg) {
                try {
                    const MixedStruct& value = arg.value.get<MixedStruct>();
                    resultPromise->set_value(value);
                    if (callback)
                    {
                        callback(value);
                    }
                } catch (const std::exception& e) {
                    try {
                        resultPromise->set_exception(std::make_exception_ptr(std::runtime_error(std::string("MQTT response error: ") + e.what())));
                    } catch (...) {}
                }
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic, nlohmann::json::array({paramMixed}).dump(), responseId);
            return resultPromise->get_future().get();
        }
    );
}

StructWithArrayOfStructs StructArrayFieldInterfaceClient::funcStructArray(const StructWithArrayOfStructs& paramPoints)
{
    if(m_client == nullptr) {
        return StructWithArrayOfStructs();
    }
    StructWithArrayOfStructs value(funcStructArrayAsync(paramPoints).get());
    return value;
}

std::future<StructWithArrayOfStructs> StructArrayFieldInterfaceClient::funcStructArrayAsync(const StructWithArrayOfStructs& paramPoints, std::function<void(StructWithArrayOfStructs)> callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this, callback,
                    paramPoints]()
        {
            auto resultPromise = std::make_shared<std::promise<StructWithArrayOfStructs>>();
            static const auto topic = std::string("tb.struct.array/StructArrayFieldInterface/rpc/funcStructArray");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [resultPromise, callback](ApiGear::MQTT::InvokeReplyArg arg) {
                try {
                    const StructWithArrayOfStructs& value = arg.value.get<StructWithArrayOfStructs>();
                    resultPromise->set_value(value);
                    if (callback)
                    {
                        callback(value);
                    }
                } catch (const std::exception& e) {
                    try {
                        resultPromise->set_exception(std::make_exception_ptr(std::runtime_error(std::string("MQTT response error: ") + e.what())));
                    } catch (...) {}
                }
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic, nlohmann::json::array({paramPoints}).dump(), responseId);
            return resultPromise->get_future().get();
        }
    );
}
void StructArrayFieldInterfaceClient::onSigMixed(const std::string& args) const
{
    try {
        nlohmann::json json_args = nlohmann::json::parse(args);
        m_publisher->publishSigMixed(json_args[0].get<MixedStruct>());
    } catch (const std::exception& e) {
        AG_LOG_ERROR("StructArrayFieldInterfaceClient JSON error: " + std::string(e.what()));
    }
}
void StructArrayFieldInterfaceClient::onSigStructArray(const std::string& args) const
{
    try {
        nlohmann::json json_args = nlohmann::json::parse(args);
        m_publisher->publishSigStructArray(json_args[0].get<StructWithArrayOfStructs>());
    } catch (const std::exception& e) {
        AG_LOG_ERROR("StructArrayFieldInterfaceClient JSON error: " + std::string(e.what()));
    }
}

int StructArrayFieldInterfaceClient::registerResponseHandler(ApiGear::MQTT::InvokeReplyFunc handler)
{
    auto responseId = 0;
    std::uniform_int_distribution<> distribution (0, 100000);
    m_responseHandlerMutex.lock();
    do {
        responseId = distribution(randomNumberGenerator);
    } while (m_responseHandlerMap.find(responseId) != m_responseHandlerMap.end());
    m_responseHandlerMap.insert(std::pair<int, ApiGear::MQTT::InvokeReplyFunc>(responseId, handler));
    m_responseHandlerMutex.unlock();

    return responseId;
}

void StructArrayFieldInterfaceClient::onInvokeReply(const std::string& args, const std::string& correlationData)
{
    const int randomId = std::stoi(correlationData);
    ApiGear::MQTT::InvokeReplyFunc responseHandler {};
    m_responseHandlerMutex.lock();
    if((m_responseHandlerMap.find(randomId) != m_responseHandlerMap.end()))
    {
        responseHandler = m_responseHandlerMap[randomId];
        m_responseHandlerMap.erase(randomId);
    }
    m_responseHandlerMutex.unlock();
    if(responseHandler) {
        const ApiGear::MQTT::InvokeReplyArg response{nlohmann::json::parse(args)};
        responseHandler(response);
    }
}

bool StructArrayFieldInterfaceClient::isReady() const
{
    return m_isReady;
}

IStructArrayFieldInterfacePublisher& StructArrayFieldInterfaceClient::_getPublisher() const
{
    return *m_publisher;
}
