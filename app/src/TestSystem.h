#pragma once

#include "engine/ecs/System.h"
#include "engine/ecs/components/TransformComponent.h"
#include "engine/ecs/components/MeshComponent.h"
#include "engine/ecs/singleton_components/ActiveCameraComponent.h"

using namespace se;
using namespace se::ecs::components;
using namespace se::ecs::singleton_components;

namespace app
{
    class TestSystem : public ecs::System<const TransformComponent, const MeshComponent, ActiveCameraComponent>
    {
        DECLARE_SPARK_SYSTEM(TestSystem)
    public:
        void OnInit(const std::vector<ecs::EntityId> &entities, const TransformComponent* transform, const MeshComponent* mesh, ActiveCameraComponent* camera) override;
        void OnUpdate(const std::vector<ecs::EntityId>& entities, const TransformComponent* transform, const MeshComponent* mesh, ActiveCameraComponent* camera) override;
        void OnRender(const std::vector<se::ecs::EntityId> &entities, const TransformComponent* transform, const MeshComponent* mesh, ActiveCameraComponent* camera) override;
        void OnShutdown(const std::vector<ecs::EntityId> &entities, const TransformComponent* transform, const MeshComponent* mesh, ActiveCameraComponent* camera) override;
    };
}
