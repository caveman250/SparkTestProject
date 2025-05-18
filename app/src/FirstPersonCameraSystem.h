#pragma once

#include "FirstPersonCameraComponent.h"
#include "engine/ecs/System.h"
#include "engine/input/InputComponent.h"
#include "engine/camera/ActiveCameraComponent.h"

using namespace se;

namespace app
{
    class FirstPersonCameraSystem : public ecs::AppSystem
    {
        SPARK_SYSTEM()

        void OnUpdate(const ecs::SystemUpdateData& updateData) override;
    };

}
