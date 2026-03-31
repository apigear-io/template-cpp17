#pragma once

#include <catch2/catch.hpp>

#include <catch2/trompeloeil.hpp>
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif
#include "olink/iobjectsource.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

namespace tests
{
    class SourceObjectMock : public trompeloeil::mock_interface<ApiGear::ObjectLink::IObjectSource>
    {
    public:
        IMPLEMENT_MOCK0(olinkObjectName);
        IMPLEMENT_MOCK2(olinkInvoke);
        IMPLEMENT_MOCK2(olinkSetProperty);
        IMPLEMENT_MOCK2(olinkLinked);
        IMPLEMENT_MOCK1(olinkUnlinked);
        IMPLEMENT_MOCK0(olinkCollectProperties);
    };
}

