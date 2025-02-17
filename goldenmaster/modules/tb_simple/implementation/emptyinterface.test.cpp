#include <memory>
#include "catch2/catch.hpp"
#include "tb_simple/implementation/emptyinterface.h"

using namespace Test::TbSimple;
TEST_CASE("Testing EmptyInterface", "[EmptyInterface]"){
    std::unique_ptr<IEmptyInterface> testEmptyInterface = std::make_unique<EmptyInterface>();
    // setup your test
}
