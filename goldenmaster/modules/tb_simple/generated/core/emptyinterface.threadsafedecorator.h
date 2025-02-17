
#pragma once
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace Test {
namespace TbSimple {

/** 
* @brief The EmptyInterfaceThreadSafeDecorator can be used to make property access thread safe.
*
* Each property is guarded with its own mutex.
* Multiple read/get operations can occur at the same time but only one write/set operation at a time.
*
* Operations are not guarded by default since the function logic can be too complex than to simply lock it.
* However, functions can be locked by just adding the same mechanism in the implementation file of
* the EmptyInterface interface.
* @see EmptyInterface
*
\code{.cpp}
using namespace Test::TbSimple;

std::unique_ptr<IEmptyInterface> testEmptyInterface = std::make_unique<EmptyInterfaceThreadSafeDecorator>(std::make_shared<EmptyInterface>());

// Thread safe access
\endcode
*/
class TEST_TB_SIMPLE_EXPORT EmptyInterfaceThreadSafeDecorator : public IEmptyInterface
{
public:
    /** 
    * ctor
    * @param impl The EmptyInterface object to make thread safe.
    */
    explicit EmptyInterfaceThreadSafeDecorator(std::shared_ptr<IEmptyInterface> impl);

    /**
    * Access to a publisher, use it to subscribe for EmptyInterface changes and signal emission.
    * This call is thread safe.
    * @return The publisher for EmptyInterface.
    */
    IEmptyInterfacePublisher& _getPublisher() const override;
private:
    /** The EmptyInterface object which is guarded */
    std::shared_ptr<IEmptyInterface> m_impl;
};
} // namespace TbSimple
} // namespace Test
