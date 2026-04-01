
#pragma once
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace Test {
namespace TbSimple {

/**
* @brief The NoPropertiesInterfaceThreadSafeDecorator can be used to make property access thread safe.
*
* Each property is guarded with its own @c std::shared_timed_mutex — multiple concurrent
* get calls are allowed, but a set call is exclusive.
*
* @note Operation (method) calls are NOT guarded by this decorator. If the underlying
* implementation is not thread safe, callers must coordinate access to operations themselves.
* Operations can be locked by adding the same mutex mechanism in the concrete
* implementation of NoPropertiesInterface.
* @see NoPropertiesInterface
*
\code{.cpp}
using namespace Test::TbSimple;

std::unique_ptr<INoPropertiesInterface> testNoPropertiesInterface = std::make_unique<NoPropertiesInterfaceThreadSafeDecorator>(std::make_shared<NoPropertiesInterface>());

// Thread safe access
\endcode
*/
class TEST_TB_SIMPLE_EXPORT NoPropertiesInterfaceThreadSafeDecorator : public INoPropertiesInterface
{
public:
    /** 
    * ctor
    * @param impl The NoPropertiesInterface object to make thread safe.
    */
    explicit NoPropertiesInterfaceThreadSafeDecorator(std::shared_ptr<INoPropertiesInterface> impl);

    /** 
    * Forwards call to NoPropertiesInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    void funcVoid() override;
    /** 
    * Forwards call to NoPropertiesInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<void> funcVoidAsync( std::function<void(void)> callback = nullptr) override;

    /** 
    * Forwards call to NoPropertiesInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    bool funcBool(bool paramBool) override;
    /** 
    * Forwards call to NoPropertiesInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<bool> funcBoolAsync(bool paramBool, std::function<void(bool)> callback = nullptr) override;

    /**
    * Access to a publisher, use it to subscribe for NoPropertiesInterface changes and signal emission.
    * This call is thread safe.
    * @return The publisher for NoPropertiesInterface.
    */
    INoPropertiesInterfacePublisher& _getPublisher() const override;
private:
    /** The NoPropertiesInterface object which is guarded */
    std::shared_ptr<INoPropertiesInterface> m_impl;
};
} // namespace TbSimple
} // namespace Test
