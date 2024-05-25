#pragma once

#include "engine/reflect/Reflect.h"

namespace app
{
    class TestComponent1
    {
        DECLARE_SPARK_COMPONENT()
    public:
        std::string key;
        float value;
    };
}
