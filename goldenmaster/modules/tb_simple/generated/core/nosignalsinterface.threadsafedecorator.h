
#pragma once
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace Test {
namespace TbSimple {

/** 
* @brief The NoSignalsInterfaceThreadSafeDecorator can be used to make property access thread safe.
*
* Each property is guarded with its own mutex.
* Multiple read/get operations can occur at the same time but only one write/set operation at a time.
*
* Operations are not guarded by default since the function logic can be too complex than to simply lock it.
* However, functions can be locked by just adding the same mechanism in the implementation file of
* the NoSignalsInterface interface.
* @see NoSignalsInterface
*
\code{.cpp}
using namespace Test::TbSimple;

std::unique_ptr<INoSignalsInterface> testNoSignalsInterface = std::make_unique<NoSignalsInterfaceThreadSafeDecorator>(std::make_shared<NoSignalsInterface>());

// Thread safe access
auto propBool = testNoSignalsInterface->getPropBool();
testNoSignalsInterface->setPropBool(false);
auto propInt = testNoSignalsInterface->getPropInt();
testNoSignalsInterface->setPropInt(0);
\endcode
*/
class TEST_TB_SIMPLE_EXPORT NoSignalsInterfaceThreadSafeDecorator : public INoSignalsInterface
{
public:
    /** 
    * ctor
    * @param impl The NoSignalsInterface object to make thread safe.
    */
    explicit NoSignalsInterfaceThreadSafeDecorator(std::shared_ptr<INoSignalsInterface> impl);

    /** 
    * Forwards call to NoSignalsInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    void funcVoid() override;
    /** 
    * Forwards call to NoSignalsInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<void> funcVoidAsync( std::function<void(void)> callback = nullptr) override;

    /** 
    * Forwards call to NoSignalsInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    bool funcBool(bool paramBool) override;
    /** 
    * Forwards call to NoSignalsInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<bool> funcBoolAsync(bool paramBool, std::function<void(bool)> callback = nullptr) override;

    /** Guards and forwards call to NoSignalsInterface implementation. */
    void setPropBool(bool propBool) override;
    /** Guards and forwards call to NoSignalsInterface implementation. */
    bool getPropBool() const override;

    /** Guards and forwards call to NoSignalsInterface implementation. */
    void setPropInt(int propInt) override;
    /** Guards and forwards call to NoSignalsInterface implementation. */
    int getPropInt() const override;

    /**
    * Access to a publisher, use it to subscribe for NoSignalsInterface changes and signal emission.
    * This call is thread safe.
    * @return The publisher for NoSignalsInterface.
    */
    INoSignalsInterfacePublisher& _getPublisher() const override;
private:
    /** The NoSignalsInterface object which is guarded */
    std::shared_ptr<INoSignalsInterface> m_impl;
    // Mutex for propBool property
    mutable std::shared_timed_mutex m_propBoolMutex;
    // Mutex for propInt property
    mutable std::shared_timed_mutex m_propIntMutex;
};
} // namespace TbSimple
} // namespace Test
