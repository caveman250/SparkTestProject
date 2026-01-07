#pragma once

#include "engine/ecs/Component.h"

using namespace se;

namespace app
{
    struct ButtonTestComponent : ecs::Component
    {
        SPARK_SINGLETON_COMPONENT()

        SPARK_MEMBER()
        bool buttonPressed = false;
    };
}