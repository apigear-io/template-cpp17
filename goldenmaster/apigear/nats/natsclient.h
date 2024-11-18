#pragma once

#include <memory>
#include <string>
#include "nlohmann/json.hpp"
#include "natscommon.h"
#include "natstypes.h"
#include "natsbase.h"

namespace ApiGear {
namespace Nats {

class APIGEAR_NATS_EXPORT Client :public Base
{
public:
    explicit Client();
    virtual ~Client() = default;
};
} // namespace Nats
} // namespace ApiGear
