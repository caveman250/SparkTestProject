#include "spark.h"

#include "ButtonTestSystem.h"

#include "components/RespondsToTestButtonComponent.h"
#include "engine/Application.h"
#include "engine/ecs/components/MeshComponent.h"
#include "engine/ecs/components/TransformComponent.h"
#include "singleton_components/ButtonTestComponent.h"

using namespace se;
using namespace se::ecs::components;

namespace app
{
    struct ButtonTestComponent;

    ecs::SystemDeclaration ButtonTestSystem::GetSystemDeclaration()
    {
        return ecs::SystemDeclaration("ButtonTestSystem")
            .WithComponent<TransformComponent>()
            .WithComponent<const MeshComponent>()
            .WithComponent<const RespondsToTestButtonComponent>()
            .WithSingletonComponent<ButtonTestComponent>();
    }

    void ButtonTestSystem::OnUpdate(const ecs::SystemUpdateData& updateData)
    {
        const auto& entities = updateData.GetEntities();
        auto* transform = updateData.GetComponentArray<TransformComponent>();
        auto* buttonTestComp = updateData.GetSingletonComponent<ButtonTestComponent>();

        if (buttonTestComp->buttonPressed)
        {
            for (size_t i = 0; i < entities.size(); ++i)
            {
                auto& transformComp = transform[i];
                transformComp.rot.y += 90.f;
            }
        }

        buttonTestComp->buttonPressed = false;
    }

    void ButtonTestSystem::OnTestButtonPressed()
    {
        auto* world = Application::Get()->GetWorld();
        auto* buttonTestComp = world->GetSingletonComponent<ButtonTestComponent>();
        buttonTestComp->buttonPressed = true;
    }
}


