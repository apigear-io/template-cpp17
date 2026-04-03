
#pragma once
#include "tb_struct_array/generated/api/tb_struct_array.h"
#include "tb_struct_array/generated/api/common.h"
#include <memory>
#include <shared_mutex>

namespace Test {
namespace TbStructArray {

/**
* @brief The StructArrayFieldInterfaceThreadSafeDecorator can be used to make property access thread safe.
*
* Each property is guarded with its own @c std::shared_timed_mutex — multiple concurrent
* get calls are allowed, but a set call is exclusive.
*
* @note Operation (method) calls are NOT guarded by this decorator. If the underlying
* implementation is not thread safe, callers must coordinate access to operations themselves.
* Operations can be locked by adding the same mutex mechanism in the concrete
* implementation of StructArrayFieldInterface.
* @see StructArrayFieldInterface
*
\code{.cpp}
using namespace Test::TbStructArray;

std::unique_ptr<IStructArrayFieldInterface> testStructArrayFieldInterface = std::make_unique<StructArrayFieldInterfaceThreadSafeDecorator>(std::make_shared<StructArrayFieldInterface>());

// Thread safe access
auto propStructArray = testStructArrayFieldInterface->getPropStructArray();
testStructArrayFieldInterface->setPropStructArray(StructWithArrayOfStructs());
auto propEnumArray = testStructArrayFieldInterface->getPropEnumArray();
testStructArrayFieldInterface->setPropEnumArray(StructWithArrayOfEnums());
auto propIntArray = testStructArrayFieldInterface->getPropIntArray();
testStructArrayFieldInterface->setPropIntArray(StructWithArrayOfInts());
auto propMixed = testStructArrayFieldInterface->getPropMixed();
testStructArrayFieldInterface->setPropMixed(MixedStruct());
\endcode
*/
class TEST_TB_STRUCT_ARRAY_EXPORT StructArrayFieldInterfaceThreadSafeDecorator : public IStructArrayFieldInterface
{
public:
    /** 
    * ctor
    * @param impl The StructArrayFieldInterface object to make thread safe.
    */
    explicit StructArrayFieldInterfaceThreadSafeDecorator(std::shared_ptr<IStructArrayFieldInterface> impl);

    /** 
    * Forwards call to StructArrayFieldInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    MixedStruct funcMixed(const MixedStruct& paramMixed) override;
    /** 
    * Forwards call to StructArrayFieldInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<MixedStruct> funcMixedAsync(const MixedStruct& paramMixed, std::function<void(MixedStruct)> callback = nullptr) override;

    /** 
    * Forwards call to StructArrayFieldInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    StructWithArrayOfStructs funcStructArray(const StructWithArrayOfStructs& paramPoints) override;
    /** 
    * Forwards call to StructArrayFieldInterface implementation.
    * @warning This forward call is not made thread safe by this class.
    */
    std::future<StructWithArrayOfStructs> funcStructArrayAsync(const StructWithArrayOfStructs& paramPoints, std::function<void(StructWithArrayOfStructs)> callback = nullptr) override;

    /** Guards and forwards call to StructArrayFieldInterface implementation. */
    void setPropStructArray(const StructWithArrayOfStructs& propStructArray) override;
    /** Guards and forwards call to StructArrayFieldInterface implementation. */
    const StructWithArrayOfStructs& getPropStructArray() const override;

    /** Guards and forwards call to StructArrayFieldInterface implementation. */
    void setPropEnumArray(const StructWithArrayOfEnums& propEnumArray) override;
    /** Guards and forwards call to StructArrayFieldInterface implementation. */
    const StructWithArrayOfEnums& getPropEnumArray() const override;

    /** Guards and forwards call to StructArrayFieldInterface implementation. */
    void setPropIntArray(const StructWithArrayOfInts& propIntArray) override;
    /** Guards and forwards call to StructArrayFieldInterface implementation. */
    const StructWithArrayOfInts& getPropIntArray() const override;

    /** Guards and forwards call to StructArrayFieldInterface implementation. */
    void setPropMixed(const MixedStruct& propMixed) override;
    /** Guards and forwards call to StructArrayFieldInterface implementation. */
    const MixedStruct& getPropMixed() const override;

    /**
    * Access to a publisher, use it to subscribe for StructArrayFieldInterface changes and signal emission.
    * This call is thread safe.
    * @return The publisher for StructArrayFieldInterface.
    */
    IStructArrayFieldInterfacePublisher& _getPublisher() const override;
private:
    /** The StructArrayFieldInterface object which is guarded */
    std::shared_ptr<IStructArrayFieldInterface> m_impl;
    // Mutex for propStructArray property
    mutable std::shared_timed_mutex m_propStructArrayMutex;
    // Mutex for propEnumArray property
    mutable std::shared_timed_mutex m_propEnumArrayMutex;
    // Mutex for propIntArray property
    mutable std::shared_timed_mutex m_propIntArrayMutex;
    // Mutex for propMixed property
    mutable std::shared_timed_mutex m_propMixedMutex;
};
} // namespace TbStructArray
} // namespace Test
