#pragma once

#include "spark.h"
#include "engine/reflect/Reflect.h"

namespace app
{
    struct TestSingletonComponent
    {
        DECLARE_SPARK_SINGLETON_COMPONENT(TestSingletonComponent)

        int value = 0;
    };
}
