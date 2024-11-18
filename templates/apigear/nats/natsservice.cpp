#include "natsservice.h"
#include "private/natscwrapper.h"

using namespace ApiGear::Nats;

Service::Service()
{
    m_cwrapper = CWrapper::create();
}

void Service::connect(std::string address)
{
    m_cwrapper->connect(address);
}
void Service::subscribe(std::string topic)
{
    m_cwrapper->subscribe(topic);
}
void Service::unsubscribe(std::string topic)
{
    m_cwrapper->unsubscribe(topic);
}
void Service::publish(std::string topic, std::string payload)
{
    m_cwrapper->publish(topic, payload);
}
