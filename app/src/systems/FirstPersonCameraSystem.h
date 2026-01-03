#pragma once

#include "engine/ecs/System.h"

using namespace se;

namespace app
{
    class FirstPersonCameraSystem : public ecs::AppSystem
    {
        SPARK_SYSTEM()

        static ecs::SystemDeclaration GetSystemDeclaration();
        void OnUpdate(const ecs::SystemUpdateData& updateData) override;
    };

}
