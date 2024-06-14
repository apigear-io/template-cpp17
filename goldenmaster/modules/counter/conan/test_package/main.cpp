
#include "counter/implementation/counter.h"

using namespace Test::Counter;

int main(){
    std::unique_ptr<ICounter> testCounter = std::make_unique<Counter>();

    return 0;
}
