#pragma once

#include "engine/reflect/Reflect.h"

namespace app
{
    class TestComponent2
    {
        DECLARE_SPARK_COMPONENT(TestComponent2)

    public:
        int lol = 5;
    };
}
