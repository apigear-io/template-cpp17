
#include "tb_struct_array/implementation/structarrayfieldinterface.h"

using namespace Test::TbStructArray;

int main(){
    std::unique_ptr<IStructArrayFieldInterface> testStructArrayFieldInterface = std::make_unique<StructArrayFieldInterface>();

    return 0;
}
