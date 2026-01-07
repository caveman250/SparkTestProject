#pragma once

#include "engine/ecs/Component.h"

using namespace se;

namespace app
{
    struct RespondsToTestButtonComponent : ecs::Component
    {
        SPARK_COMPONENT()
    };
}