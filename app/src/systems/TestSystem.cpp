#include "spark.h"

#include "TestSystem.h"
#include "engine/Application.h"
#include "engine/ecs/components/MeshComponent.h"
#include "engine/ecs/components/TransformComponent.h"

using namespace se;
using namespace se::ecs::components;

namespace app
{
    ecs::SystemDeclaration TestSystem::GetSystemDeclaration()
    {
        return ecs::SystemDeclaration("TestSystem")
            .WithComponent<TransformComponent>()
            .WithComponent<const MeshComponent>();
    }

    void TestSystem::OnInit(const ecs::SystemUpdateData&)
    {
        const auto app = Application::Get();
        const auto world = app->GetWorld();

        world->LoadScene("/assets/scenes/test_scene.sass");
    }

    void TestSystem::OnUpdate(const ecs::SystemUpdateData& updateData)
    {
        auto app = Application::Get();
        auto dt = app->GetDeltaTime();

        const auto& entities = updateData.GetEntities();
        auto* transform = updateData.GetComponentArray<TransformComponent>();
        for (size_t i = 0; i < entities.size(); ++i)
        {
            auto& transformComp = transform[i];
            transformComp.rot.y += 10.f * dt;
            if (transformComp.rot.y > 360.f)
            {
                transformComp.rot.y -= 360.f;
            }
        }
    }
}


