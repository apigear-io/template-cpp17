
#pragma once
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace Test {
namespace TbSimple {

/**
* @brief The NoOperationsInterfaceThreadSafeDecorator can be used to make property access thread safe.
*
* Each property is guarded with its own @c std::shared_timed_mutex — multiple concurrent
* get calls are allowed, but a set call is exclusive.
*
* @note Operation (method) calls are NOT guarded by this decorator. If the underlying
* implementation is not thread safe, callers must coordinate access to operations themselves.
* Operations can be locked by adding the same mutex mechanism in the concrete
* implementation of NoOperationsInterface.
* @see NoOperationsInterface
*
\code{.cpp}
using namespace Test::TbSimple;

std::unique_ptr<INoOperationsInterface> testNoOperationsInterface = std::make_unique<NoOperationsInterfaceThreadSafeDecorator>(std::make_shared<NoOperationsInterface>());

// Thread safe access
auto propBool = testNoOperationsInterface->getPropBool();
testNoOperationsInterface->setPropBool(false);
auto propInt = testNoOperationsInterface->getPropInt();
testNoOperationsInterface->setPropInt(0);
\endcode
*/
class TEST_TB_SIMPLE_EXPORT NoOperationsInterfaceThreadSafeDecorator : public INoOperationsInterface
{
public:
    /** 
    * ctor
    * @param impl The NoOperationsInterface object to make thread safe.
    */
    explicit NoOperationsInterfaceThreadSafeDecorator(std::shared_ptr<INoOperationsInterface> impl);

    /** Guards and forwards call to NoOperationsInterface implementation. */
    void setPropBool(bool propBool) override;
    /** Guards and forwards call to NoOperationsInterface implementation. */
    bool getPropBool() const override;

    /** Guards and forwards call to NoOperationsInterface implementation. */
    void setPropInt(int propInt) override;
    /** Guards and forwards call to NoOperationsInterface implementation. */
    int getPropInt() const override;

    /**
    * Access to a publisher, use it to subscribe for NoOperationsInterface changes and signal emission.
    * This call is thread safe.
    * @return The publisher for NoOperationsInterface.
    */
    INoOperationsInterfacePublisher& _getPublisher() const override;
private:
    /** The NoOperationsInterface object which is guarded */
    std::shared_ptr<INoOperationsInterface> m_impl;
    // Mutex for propBool property
    mutable std::shared_timed_mutex m_propBoolMutex;
    // Mutex for propInt property
    mutable std::shared_timed_mutex m_propIntMutex;
};
} // namespace TbSimple
} // namespace Test
