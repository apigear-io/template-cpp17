
#pragma once
#include "tb_simple/generated/api/tb_simple.h"
#include "tb_simple/generated/api/common.h"
#include "tb_simple/generated/core/nosignalsinterface.data.h"
#include <memory>

namespace Test {
namespace TbSimple {

/**
* The NoSignalsInterface implementation.
*/
class TEST_TB_SIMPLE_EXPORT NoSignalsInterface : public INoSignalsInterface
{
public:
    explicit NoSignalsInterface();
    ~NoSignalsInterface();
public:
    void setPropBool(bool propBool) override;
    bool getPropBool() const override;
    
    void setPropInt(int propInt) override;
    int getPropInt() const override;
    
    void funcVoid() override;
    std::future<void> funcVoidAsync( std::function<void(void)> callback = nullptr) override;
        
    bool funcBool(bool paramBool) override;
    std::future<bool> funcBoolAsync(bool paramBool, std::function<void(bool)> callback = nullptr) override;
        
    /**
    * Access to a publisher, use it to subscribe for NoSignalsInterface changes and signal emission.
    * @return The publisher for NoSignalsInterface.
    */
    INoSignalsInterfacePublisher& _getPublisher() const override;
private:
    /** The publisher for the NoSignalsInterface. */
    std::unique_ptr<INoSignalsInterfacePublisher> m_publisher;
    /** The helper structure to store all the properties for NoSignalsInterface. */
    NoSignalsInterfaceData m_data;
};
} // namespace TbSimple
} // namespace Test
