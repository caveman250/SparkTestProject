#include "spark.h"

#include <engine/math/Mat4.h>
#include <engine/render/Material.h>
#include <engine/ecs/components/MeshComponent.h>
#include "UITestSystem.h"

#include "TestApplication.h"
#include "engine/Application.h"

using namespace se;
using namespace se::ecs::components;

namespace app
{
    DEFINE_SPARK_SYSTEM(UITestSystem)

    void UITestSystem::OnInit(const std::vector<ecs::Id>&, ui::components::RectTransformComponent*)
    {
        auto app = Application::Get();
        auto world = app->GetWorld();

        ecs::Id entity = world->CreateEntity();
        auto rectTransform = world->AddComponent<ui::components::RectTransformComponent>(entity);
        rectTransform->anchors = { 0.f, 0.f, 0.f, 0.f };
        rectTransform->minX = 10;
        rectTransform->maxX = 20;
        rectTransform->minY = 10;
        rectTransform->maxY = 20;

        ecs::Id entity2 = world->CreateEntity();
        ui::components::RectTransformComponent* rectTransform2 = world->AddComponent<ui::components::RectTransformComponent>(entity2);
        rectTransform2->anchors = { 0.f, 0.8f, 0.f, 0.8f };
        rectTransform2->minX = 0;
        rectTransform2->maxX = 0;
        rectTransform2->minY = 0;
        rectTransform2->maxY = 0;
        world->AddChild(entity, entity2);
    }

    void UITestSystem::OnUpdate(const std::vector<ecs::Id>& entities, ui::components::RectTransformComponent* transform)
    {
        auto app = Application::Get();
        auto dt = app->GetDeltaTime();
        for (size_t i = 0; i < entities.size(); ++i)
        {
            auto& transformComp = transform[i];
            int lol = 1;
        }
    }
}
