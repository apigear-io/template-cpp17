#pragma once

#include <memory>
#include <string>
#include "nlohmann/json.hpp"
#include "natscommon.h"
#include "natstypes.h"

namespace ApiGear {
namespace Nats {

class APIGEAR_NATS_EXPORT Base
{
public:
    explicit Base();
    virtual ~Base() = default;

    void connect(std::string address);
    void subscribe(std::string topic);
    void unsubscribe(std::string topic);
    void publish(std::string topic, std::string payload);

private:
    std::shared_ptr<class CWrapper> m_cwrapper;
};
} // namespace Nats
} // namespace ApiGear
