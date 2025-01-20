
#pragma once
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/core/voidinterface.data.h"
#include <memory>

namespace Test {
namespace TbSimple {

/**
* The VoidInterface implementation.
*/
class TEST_TB_SIMPLE_EXPORT VoidInterface : public IVoidInterface
{
public:
    explicit VoidInterface();
    ~VoidInterface();
public:
    void funcVoid() override;
    std::future<void> funcVoidAsync( std::function<void(void)> callback = nullptr) override;
        
    /**
    * Access to a publisher, use it to subscribe for VoidInterface changes and signal emission.
    * @return The publisher for VoidInterface.
    */
    IVoidInterfacePublisher& _getPublisher() const override;
private:
    /** The publisher for the VoidInterface. */
    std::unique_ptr<IVoidInterfacePublisher> m_publisher;
};
} // namespace TbSimple
} // namespace Test
