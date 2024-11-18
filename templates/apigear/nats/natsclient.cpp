#include "natsclient.h"
#include "private/natscwrapper.h"

using namespace ApiGear::Nats;

Client::Client()
{
    m_cwrapper = CWrapper::create();
}

void Client::connect(std::string address)
{
    m_cwrapper->connect(address);
}
void Client::subscribe(std::string topic)
{
    m_cwrapper->subscribe(topic);
}
void Client::unsubscribe(std::string topic)
{
    m_cwrapper->unsubscribe(topic);
}
void Client::publish(std::string topic, std::string payload)
{
    m_cwrapper->publish(topic, payload);
}