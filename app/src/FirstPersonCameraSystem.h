#pragma once

#include "FirstPersonCameraComponent.h"
#include "engine/ecs/System.h"
#include "engine/input/InputComponent.h"
#include "engine/camera/ActiveCameraComponent.h"

using namespace se;

namespace app
{
    class FirstPersonCameraSystem : public ecs::AppSystem<FirstPersonCameraComponent, camera::ActiveCameraComponent, input::InputComponent>
    {
        DECLARE_SPARK_SYSTEM(FirstPersonCameraSystem)

        void OnUpdate(const std::vector<se::ecs::Id>& entities, FirstPersonCameraComponent* camera, camera::ActiveCameraComponent* activeCamera, input::InputComponent* input) override;
    };

}
