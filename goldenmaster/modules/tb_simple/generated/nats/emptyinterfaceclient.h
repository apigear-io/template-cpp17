#pragma once

#include <future>
#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/core/emptyinterface.data.h"
#include "apigear/nats/natsclient.h"

namespace Test {
namespace TbSimple {
namespace Nats {
class TEST_TB_SIMPLE_EXPORT EmptyInterfaceClient : public IEmptyInterface
{
public:
    explicit EmptyInterfaceClient(std::shared_ptr<ApiGear::Nats::Client> client);
    virtual ~EmptyInterfaceClient() override;
    IEmptyInterfacePublisher& _getPublisher() const override;
private:
    std::shared_ptr<ApiGear::Nats::Client> m_client;

    /** The publisher for EmptyInterface */
    std::unique_ptr<IEmptyInterfacePublisher> m_publisher;

};
} // namespace Nats
} // namespace TbSimple
} // namespace Test
