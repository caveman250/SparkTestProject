#pragma once

#include "engine/reflect/Reflect.h"

namespace app
{
    class TestComponent1
    {
        DECLARE_SPARK_COMPONENT(TestComponent1)
    public:
        std::string key;
        float value;
    };
}
