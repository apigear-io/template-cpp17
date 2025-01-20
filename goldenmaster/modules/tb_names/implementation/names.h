
#pragma once
#include "tb_names/generated/api/tb_names.h"
#include "tb_names/generated/api/common.h"
#include "tb_names/generated/core/names.data.h"
#include <memory>

namespace Test {
namespace TbNames {

/**
* The Nam_Es implementation.
*/
class TEST_TB_NAMES_EXPORT NamEs : public INamEs
{
public:
    explicit NamEs();
    ~NamEs();
public:
    void setSwitch(bool Switch) override;
    bool getSwitch() const override;
    
    void setSomeProperty(int SOME_PROPERTY) override;
    int getSomeProperty() const override;
    
    void setSomePoperty2(int Some_Poperty2) override;
    int getSomePoperty2() const override;
    
    void setEnumProperty(Enum_With_Under_scoresEnum enum_property) override;
    Enum_With_Under_scoresEnum getEnumProperty() const override;
    
    void sOME_FUNCTION(bool SOME_PARAM) override;
    std::future<void> sOME_FUNCTIONAsync(bool SOME_PARAM, std::function<void(void)> callback = nullptr) override;
        
    void some_Function2(bool Some_Param) override;
    std::future<void> some_Function2Async(bool Some_Param, std::function<void(void)> callback = nullptr) override;
        
    /**
    * Access to a publisher, use it to subscribe for Nam_Es changes and signal emission.
    * @return The publisher for Nam_Es.
    */
    INamEsPublisher& _getPublisher() const override;
private:
    /** The publisher for the Nam_Es. */
    std::unique_ptr<INamEsPublisher> m_publisher;
    /** The helper structure to store all the properties for Nam_Es. */
    NamEsData m_data;
};
} // namespace TbNames
} // namespace Test
