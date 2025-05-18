#pragma once
#include "engine/reflect/Reflect.h"

using namespace se;

namespace app
{
    class FirstPersonCameraComponent : public reflect::ObjectBase
    {
        DECLARE_SPARK_COMPONENT(FirstPersonCameraComponent)

        SPARK_MEMBER()
        bool mouseDown = false;
    };
}
