#pragma once
#include "engine/reflect/Reflect.h"

using namespace se;

namespace app
{
    class FirstPersonCameraComponent : public reflect::ObjectBase
    {
        SPARK_COMPONENT(FirstPersonCameraComponent)

        SPARK_MEMBER()
        bool mouseDown = false;
    };
}
