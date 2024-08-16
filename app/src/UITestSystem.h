#pragma once

#include "engine/ecs/System.h"
#include "engine/ecs/components/TransformComponent.h"
#include "engine/ui/components/RectTransformComponent.h"

using namespace se;
using namespace se::ecs::components;

namespace app
{
    class UITestSystem : public ecs::AppSystem<ui::components::RectTransformComponent>
    {
        DECLARE_SPARK_SYSTEM(UITestSystem)
    public:
        void OnInit(const std::vector<ecs::Id> &entities, ui::components::RectTransformComponent* transform) override;
        void OnUpdate(const std::vector<ecs::Id>& entities, ui::components::RectTransformComponent* transform) override;
    };
}
