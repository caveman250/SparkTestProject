#[[#pragma once]]# 

#[[#include]]# "spark.h"
#[[#include]]# "engine/ecs/System.h"

namespace ${namespace} 
{
    class ${NAME} : public ecs::EngineSystem
    {
        SPARK_SYSTEM()
        
        static ecs::SystemDeclaration GetSystemDeclaration();
    };
}