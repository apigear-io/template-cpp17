#pragma once

#include <memory>
#include "natscommon.h"
#include <string>

namespace ApiGear {
namespace Nats {

class APIGEAR_NATS_EXPORT Service
{
public:
    explicit Service();
    virtual ~Service() = default;

    void connect(std::string address);
    void subscribe(std::string topic);
    void unsubscribe(std::string topic);
    void publish(std::string topic, std::string payload);

private:
    std::shared_ptr<class CWrapper> m_cwrapper;
};
} // namespace Nats
} // namespace ApiGear
