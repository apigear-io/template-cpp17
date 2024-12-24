#pragma once

#include <memory>
#include "natscommon.h"
#include "natsbase.h"
#include <string>

namespace ApiGear {
namespace Nats {

class APIGEAR_NATS_EXPORT Service : public Base
{
public:
    explicit Service();
    virtual ~Service() = default;
};
} // namespace Nats
} // namespace ApiGear
