#pragma once

#include "engine/ecs/System.h"
#include "engine/input/InputComponent.h"
#include "engine/camera/ActiveCameraComponent.h"

using namespace se;

namespace app
{
    class CameraSystem : public ecs::AppSystem<camera::ActiveCameraComponent, input::InputComponent>
    {
        DECLARE_SPARK_SYSTEM(CameraSystem)

        void OnUpdate(const std::vector<se::ecs::Id>& entities, camera::ActiveCameraComponent* camera, input::InputComponent* input) override;
    };

}
