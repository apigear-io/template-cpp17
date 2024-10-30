#include "tb_names/generated/nats/namesclient.h"
#include "tb_names/generated/core/names.publisher.h"
#include "tb_names/generated/core/tb_names.json.adapter.h"

using namespace Test::TbNames;
using namespace Test::TbNames::Nats;


Nam_EsClient::Nam_EsClient(std::shared_ptr<ApiGear::Nats::Client> client)
    : m_client(client)
    , m_publisher(std::make_unique<NamEsPublisher>())
{
}

Nam_EsClient::~Nam_EsClient()
{
}

void Nam_EsClient::setSwitch(bool Switch)
{
    if(m_client == nullptr) {
        return;
    }
    (void) Switch;
    //TODO
}

void Nam_EsClient::setSwitchLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    bool Switch = fields.get<bool>();
    if (m_data.m_Switch != Switch) {
        m_data.m_Switch = Switch;
        m_publisher->publishSwitchChanged(Switch);
    }
}

bool Nam_EsClient::getSwitch() const
{
    return m_data.m_Switch;
}

void Nam_EsClient::setSomeProperty(int SOME_PROPERTY)
{
    if(m_client == nullptr) {
        return;
    }
    (void) SOME_PROPERTY;
    //TODO
}

void Nam_EsClient::setSomePropertyLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    int SOME_PROPERTY = fields.get<int>();
    if (m_data.m_SOME_PROPERTY != SOME_PROPERTY) {
        m_data.m_SOME_PROPERTY = SOME_PROPERTY;
        m_publisher->publishSomePropertyChanged(SOME_PROPERTY);
    }
}

int Nam_EsClient::getSomeProperty() const
{
    return m_data.m_SOME_PROPERTY;
}

void Nam_EsClient::setSomePoperty2(int Some_Poperty2)
{
    if(m_client == nullptr) {
        return;
    }
    (void) Some_Poperty2;
    //TODO
}

void Nam_EsClient::setSomePoperty2Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    int Some_Poperty2 = fields.get<int>();
    if (m_data.m_Some_Poperty2 != Some_Poperty2) {
        m_data.m_Some_Poperty2 = Some_Poperty2;
        m_publisher->publishSomePoperty2Changed(Some_Poperty2);
    }
}

int Nam_EsClient::getSomePoperty2() const
{
    return m_data.m_Some_Poperty2;
}

void Nam_EsClient::setEnumProperty(Enum_With_Under_scoresEnum enum_property)
{
    if(m_client == nullptr) {
        return;
    }
    (void) enum_property;
    //TODO
}

void Nam_EsClient::setEnumPropertyLocal(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    Enum_With_Under_scoresEnum enum_property = fields.get<Enum_With_Under_scoresEnum>();
    if (m_data.m_enum_property != enum_property) {
        m_data.m_enum_property = enum_property;
        m_publisher->publishEnumPropertyChanged(enum_property);
    }
}

Enum_With_Under_scoresEnum Nam_EsClient::getEnumProperty() const
{
    return m_data.m_enum_property;
}

void Nam_EsClient::sOME_FUNCTION(bool SOME_PARAM)
{
    if(m_client == nullptr) {
        return;
    }
    sOME_FUNCTIONAsync(SOME_PARAM);
}

std::future<void> Nam_EsClient::sOME_FUNCTIONAsync(bool SOME_PARAM)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    SOME_PARAM]()
        {
            std::promise<void> resultPromise;
            //TODO 
            return resultPromise.get_future().get();
        }
    );
}

void Nam_EsClient::some_Function2(bool Some_Param)
{
    if(m_client == nullptr) {
        return;
    }
    some_Function2Async(Some_Param);
}

std::future<void> Nam_EsClient::some_Function2Async(bool Some_Param)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    return std::async(std::launch::async, [this,
                    Some_Param]()
        {
            std::promise<void> resultPromise;
            //TODO 
            return resultPromise.get_future().get();
        }
    );
}
void Nam_EsClient::onSomeSignal(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSomeSignal(json_args[0].get<bool>());
}
void Nam_EsClient::onSomeSignal2(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publishSomeSignal2(json_args[0].get<bool>());
}


INamEsPublisher& Nam_EsClient::_getPublisher() const
{
    return *m_publisher;
}
