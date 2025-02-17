
#pragma once
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/core/emptyinterface.data.h"
#include <memory>

namespace Test {
namespace TbSimple {

/**
* The EmptyInterface implementation.
*/
class TEST_TB_SIMPLE_EXPORT EmptyInterface : public IEmptyInterface
{
public:
    explicit EmptyInterface();
    ~EmptyInterface();
public:
    /**
    * Access to a publisher, use it to subscribe for EmptyInterface changes and signal emission.
    * @return The publisher for EmptyInterface.
    */
    IEmptyInterfacePublisher& _getPublisher() const override;
private:
    /** The publisher for the EmptyInterface. */
    std::unique_ptr<IEmptyInterfacePublisher> m_publisher;
};
} // namespace TbSimple
} // namespace Test
