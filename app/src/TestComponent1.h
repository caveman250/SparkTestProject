#pragma once

#include "engine/reflect/Reflect.h"

namespace app
{
    struct TestComponent1
    {
        DECLARE_SPARK_COMPONENT(TestComponent1)

        std::string key = {};
        float value = {};
    };
}
