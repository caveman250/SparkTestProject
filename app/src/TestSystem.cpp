#include "spark.h"

#include "TestSystem.h"
#include "FirstPersonCameraComponent.h"
#include "TestObserver.h"
#include "engine/Application.h"
#include "engine/asset/AssetManager.h"
#include "engine/asset/mesh/Model.h"
#include "engine/asset/texture/Texture.h"
#include "engine/ecs/components/MeshComponent.h"
#include "engine/ecs/components/TransformComponent.h"
#include "engine/render/Material.h"
#include "engine/render/components/PointLightComponent.h"
#include "engine/ui/components/ButtonComponent.h"
#include "engine/ui/components/RectTransformComponent.h"

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
        auto app = Application::Get();
        auto world = app->GetWorld();
        auto assetManager = asset::AssetManager::Get();

        ecs::Id cameraEntity = world->CreateEntity("Camera");
        world->AddComponent<FirstPersonCameraComponent>(cameraEntity);

        ecs::Id light1 = world->CreateEntity("Light 1");
        auto* light1Transform = world->AddComponent<TransformComponent>(light1);
        light1Transform->pos = {-5.f, 5.f, 5.f};
        auto* light1Light = world->AddComponent<render::components::PointLightComponent>(light1);
        light1Light->color = {0.f, 0.f, 1.f};

        ecs::Id light2 = world->CreateEntity("Light 2");
        auto* light2Transform = world->AddComponent<TransformComponent>(light2);
        light2Transform->pos = {5.f, 5.f, 5.f};
        auto* light2Light = world->AddComponent<render::components::PointLightComponent>(light2);
        light2Light->color = {1.f, 0.f, 0.f};

        // Cube 1
        ecs::Id entity = world->CreateEntity("Cube 1");
        auto* transform = world->AddComponent<TransformComponent>(entity);
        transform->pos = math::Vec3(0.f, 0.f, 0.f);

        auto* mesh = world->AddComponent<MeshComponent>(entity);
        mesh->model = asset::AssetReference<asset::Model>("/assets/models/cube.sass");
        mesh->material = asset::AssetReference<render::Material>("/assets/materials/cube_mat.sass");

        // Cube 2
        ecs::Id entity2 = world->CreateEntity("Cube 2");
        auto* transform2 = world->AddComponent<TransformComponent>(entity2);
        transform2->pos = math::Vec3(3.f, 0.f, 0.f);

        auto* mesh2 = world->AddComponent<MeshComponent>(entity2);
        mesh2->model = asset::AssetReference<asset::Model>("/assets/models/cube.sass");
        mesh2->material = asset::AssetReference<render::Material>("/assets/materials/cube2_mat.sass");

        world->AddChild(entity, entity2);

        world->CreateObserver<TestObserver, MeshComponent>();

        ecs::Id buttonEntity = world->CreateEntity("Button");
        auto rectTransform5 = world->AddComponent<ui::components::RectTransformComponent>(buttonEntity);
        rectTransform5->anchors = { 0.f, 0.f, 0.f, 0.f };
        rectTransform5->minX = 20;
        rectTransform5->maxX = 120;
        rectTransform5->minY = 20;
        rectTransform5->maxY = 120;

        auto button = world->AddComponent<ui::components::ButtonComponent>(buttonEntity);
        button->image = assetManager->GetAsset<asset::Texture>("/engine_assets/textures/default_button.sass");
        button->pressedImage = assetManager->GetAsset<asset::Texture>("/engine_assets/textures/default_button_pressed.sass");
        button->hoveredImage = assetManager->GetAsset<asset::Texture>("/engine_assets/textures/default_button_hovered.sass");

        std::function<void()> cb = [entity]()
        {
            auto transform = Application::Get()->GetWorld()->GetComponent<TransformComponent>(entity);
            transform->rot.y += 90.f;

            Application::Get()->GetWorld()->DumpWidgetHeirachy();
        };
        button->onReleased.Subscribe(std::move(cb));
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


