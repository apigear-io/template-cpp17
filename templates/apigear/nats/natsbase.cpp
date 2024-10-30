#include "natsclient.h"
#include "private/natscwrapper.h"

using namespace ApiGear::Nats;

Base::Base()
{
    m_cwrapper = CWrapper::create();
}

void Base::connect(std::string address)
{
    m_cwrapper->connect(address);
}
void Base::subscribe(std::string topic)
{
    m_cwrapper->subscribe(topic);
}
void Base::unsubscribe(std::string topic)
{
    m_cwrapper->unsubscribe(topic);
}
void Base::publish(std::string topic, std::string payload)
{
    m_cwrapper->publish(topic, payload);
}