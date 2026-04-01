
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
* Each property is guarded with its own @c std::shared_timed_mutex — multiple concurrent
* get calls are allowed, but a set call is exclusive.
*
* @note Operation (method) calls are NOT guarded by this decorator. If the underlying
* implementation is not thread safe, callers must coordinate access to operations themselves.
* Operations can be locked by adding the same mutex mechanism in the concrete
* implementation of EmptyInterface.
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
