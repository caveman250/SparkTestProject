#include "spark.h"

#include "engine/asset/texture/Texture.h"
#include "engine/render/Material.h"
#include "engine/asset/shader/ast/Types.h"
#include "engine/ecs/components/MeshComponent.h"
#include "engine/render/RenderState.h"
#include "engine/asset/mesh/Model.h"
#include "engine/render/VertexBuffer.h"
#include "engine/render/MaterialInstance.h"
#include "TestSystem.h"

#include "FirstPersonCameraComponent.h"
#include "TestObserver.h"
#include "engine/Application.h"
#include "engine/asset/AssetManager.h"
#include "engine/ecs/components/TransformComponent.h"
#include "engine/render/IndexBuffer.h"
#include "engine/render/components/PointLightComponent.h"
#include "engine/ui/components/ButtonComponent.h"
#include "engine/ui/components/RectTransformComponent.h"

using namespace se;
using namespace se::ecs::components;

namespace app
{
    void LoadCubeMesh(MeshComponent* meshComp)
    {
        meshComp->model = asset::AssetManager::Get()->GetAsset<asset::Model>("/assets/models/cube.sass");
        auto mesh = meshComp->model->GetMesh(0);
        meshComp->vertBuffer = render::VertexBuffer::CreateVertexBuffer(mesh);
        meshComp->vertBuffer->CreatePlatformResource();
        meshComp->indexBuffer = render::IndexBuffer::CreateIndexBuffer(mesh);
        meshComp->indexBuffer->CreatePlatformResource();
    }

    void TestSystem::OnInit(const ecs::SystemUpdateData&)
    {
        auto app = Application::Get();
        auto world = app->GetWorld();

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

        auto* assetManager = asset::AssetManager::Get();
        auto uberVertex = assetManager->GetAsset<asset::Shader>("/engine_assets/shaders/uber_vertex.sass");
        auto diffuse = assetManager->GetAsset<asset::Shader>("/engine_assets/shaders/diffuse_texture.sass");
        auto pointLght = assetManager->GetAsset<asset::Shader>("/engine_assets/shaders/point_light.sass");
        auto hueShader = assetManager->GetAsset<asset::Shader>("/assets/shaders/hue.sass");

        auto* mesh = world->AddComponent<MeshComponent>(entity);
        LoadCubeMesh(mesh);

        auto material = render::Material::CreateMaterial(
            {uberVertex},
            {diffuse, pointLght, hueShader});
        material->GetShaderSettings().SetSetting("color_setting", math::Vec3(0, 0, 1));
        render::RenderState rs;
        rs.depthComp = render::DepthCompare::Less;
        rs.lit = true;
        material->SetRenderState(rs);

        mesh->materialInstance = render::MaterialInstance::CreateMaterialInstance(material);
        auto texture = assetManager->GetAsset<asset::Texture>("/assets/textures/uvmap.sass");
        mesh->materialInstance->SetUniform("Texture", asset::shader::ast::AstType::Sampler2D, 1, &texture);

        // Cube 2
        ecs::Id entity2 = world->CreateEntity("Cube 2");
        auto* transform2 = world->AddComponent<TransformComponent>(entity2);
        transform2->pos = math::Vec3(3.f, 0.f, 0.f);

        auto* mesh2 = world->AddComponent<MeshComponent>(entity2);
        LoadCubeMesh(mesh2);
        auto material2 = render::Material::CreateMaterial(
                {uberVertex},
                {diffuse, pointLght});
        material2->SetRenderState(rs);

        mesh2->materialInstance = render::MaterialInstance::CreateMaterialInstance(material2);
        auto texture2 = assetManager->GetAsset<asset::Texture>("/assets/textures/uvmap2.sass");
        mesh2->materialInstance->SetUniform("Texture", asset::shader::ast::AstType::Sampler2D, 1, &texture2);

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
