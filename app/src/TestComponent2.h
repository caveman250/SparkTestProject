#pragma once

#include "engine/reflect/Reflect.h"

namespace app
{
    struct TestComponent2
    {
        DECLARE_SPARK_COMPONENT(TestComponent2)

        int lol = 5;
    };
}
