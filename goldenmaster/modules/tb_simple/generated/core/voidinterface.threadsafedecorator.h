
#pragma once
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace Test {
namespace TbSimple {

/**
* @brief The VoidInterfaceThreadSafeDecorator can be used to make property access thread safe.
*
* Each property is guarded with its own @c std::shared_timed_mutex — multiple concurrent
* get calls are allowed, but a set call is exclusive.
*
* @note Operation (method) calls are NOT guarded by this decorator. If the underlying
* implementation is not thread safe, callers must coordinate access to operations themselves.
* Operations can be locked by adding the same mutex mechanism in the concrete
* implementation of VoidInterface.
* @see VoidInterface
*
\code{.cpp}
using namespace Test::TbSimple;

std::unique_ptr<IVoidInterface> testVoidInterface = std::make_unique<VoidInterfaceThreadSafeDecorator>(std::make_shared<VoidInterface>());

// Thread safe access
\endcode
*/
class TEST_TB_SIMPLE_EXPORT VoidInterfaceThreadSafeDecorator : public IVoidInterface
{
public:
    /** 
    * ctor
    * @param impl The VoidInterface object to make thread safe.
    */
    explicit VoidInterfaceThreadSafeDecorator(std::shared_ptr<IVoidInterface> impl);

    /** 
    * Forwards call to VoidInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    void funcVoid() override;
    /** 
    * Forwards call to VoidInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<void> funcVoidAsync( std::function<void(void)> callback = nullptr) override;

    /**
    * Access to a publisher, use it to subscribe for VoidInterface changes and signal emission.
    * This call is thread safe.
    * @return The publisher for VoidInterface.
    */
    IVoidInterfacePublisher& _getPublisher() const override;
private:
    /** The VoidInterface object which is guarded */
    std::shared_ptr<IVoidInterface> m_impl;
};
} // namespace TbSimple
} // namespace Test
