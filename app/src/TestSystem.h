#pragma once

#include "engine/ecs/System.h"
#include "engine/ecs/components/TransformComponent.h"
#include "engine/ecs/components/MeshComponent.h"
#include "engine/camera/ActiveCameraComponent.h"

using namespace se;
using namespace se::ecs::components;

namespace app
{
    class TestSystem : public ecs::AppSystem
    {
        SPARK_SYSTEM()
    public:
        void OnInit(const ecs::SystemUpdateData& updateData) override;
        void OnUpdate(const ecs::SystemUpdateData& updateData) override;
    };
}
