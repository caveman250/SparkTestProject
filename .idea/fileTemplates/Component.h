#[[#pragma once]]# 

#[[#include]]# "spark.h"
#[[#include]]# "engine/ecs/Component.h"

namespace ${namespace} 
{
    struct ${NAME} : ecs::Component
    {
        SPARK_COMPONENT()
    };
}