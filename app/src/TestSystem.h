#pragma once

#include "engine/ecs/System.h"
#include "engine/ecs/components/TransformComponent.h"
#include "engine/ecs/components/MeshComponent.h"
#include "engine/camera/ActiveCameraComponent.h"

using namespace se;
using namespace se::ecs::components;

namespace app
{
    class TestSystem : public ecs::System<TransformComponent>
    {
        DECLARE_SPARK_SYSTEM(TestSystem)
    public:
        void OnInit(const std::vector<ecs::EntityId> &entities, TransformComponent* transform) override;
        void OnUpdate(const std::vector<ecs::EntityId>& entities, TransformComponent* transform) override;
    };
}
