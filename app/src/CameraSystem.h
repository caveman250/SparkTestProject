#pragma once

#include "engine/ecs/System.h"
#include "engine/input/InputComponent.h"
#include "engine/camera/ActiveCameraComponent.h"

using namespace se;

namespace app
{
    class CameraSystem : public ecs::System<camera::ActiveCameraComponent, input::InputComponent>, public reflect::ObjectBase
    {
        DECLARE_SPARK_SYSTEM(CameraSystem)

        void OnUpdate(const std::vector<se::ecs::EntityId>& entities, camera::ActiveCameraComponent* camera, input::InputComponent* input) override;
    };

}
