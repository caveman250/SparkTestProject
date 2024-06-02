#include "spark.h"
#include "TestSingletonComponent.h"

namespace app
{
    DEFINE_SPARK_COMPONENT_BEGIN(TestSingletonComponent)
        DEFINE_MEMBER(value)
    DEFINE_SPARK_COMPONENT_END()
}