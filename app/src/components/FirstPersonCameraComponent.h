#pragma once

#include "engine/ecs/Component.h"

using namespace se;

namespace app
{
    struct FirstPersonCameraComponent : ecs::Component
    {
        SPARK_COMPONENT()

        SPARK_MEMBER()
        bool mouseDown = false;
    };
}