#pragma once

#include "ReactToButtonComponent.h"
#include "engine/ecs/System.h"
#include "engine/ecs/components/TransformComponent.h"
#include "engine/ecs/components/MeshComponent.h"
#include "engine/camera/ActiveCameraComponent.h"
#include "engine/ui/components/ButtonComponent.h"

using namespace se;
using namespace se::ecs::components;

namespace app
{
    class TestButtonSystem : public ecs::AppSystem<TransformComponent, const ui::components::ReactToButtonComponent>
    {
        DECLARE_SPARK_SYSTEM(TestButtonSystem)
    public:
        void OnUpdate(const std::vector<ecs::Id>& entities, TransformComponent* transform, const ui::components::ReactToButtonComponent*) override;
    };
}
