
#include "testbed1/implementation/structinterface.h"
#include "testbed1/implementation/structarrayinterface.h"
#include "testbed1/implementation/structarray2interface.h"

using namespace Test::Testbed1;

int main(){
    std::unique_ptr<IStructInterface> testStructInterface = std::make_unique<StructInterface>();
    std::unique_ptr<IStructArrayInterface> testStructArrayInterface = std::make_unique<StructArrayInterface>();
    std::unique_ptr<IStructArray2Interface> testStructArray2Interface = std::make_unique<StructArray2Interface>();

    return 0;
}
