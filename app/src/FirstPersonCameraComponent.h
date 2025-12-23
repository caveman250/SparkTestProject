#pragma once

using namespace se;

namespace app
{
    class FirstPersonCameraComponent : public reflect::ObjectBase
    {
        SPARK_COMPONENT()

        SPARK_MEMBER()
        bool mouseDown = false;
    };
}