#include "spark.h"

#include <engine/math/Mat4.h>
#include <engine/asset/texture/Texture.h>
#include <engine/render/Material.h>
#include <engine/asset/shader/ast/Types.h>
#include <engine/ecs/components/MeshComponent.h>
#include <engine/render/RenderState.h>
#include <engine/asset/mesh/Model.h>
#include <engine/render/VertexBuffer.h>
#include "TestSystem.h"

#include "TestApplication.h"
#include "engine/Application.h"
#include "engine/asset/AssetManager.h"
#include "engine/ecs/components/TransformComponent.h"
#include "engine/ecs/relationships/ChildOf.h"
#include "engine/render/IndexBuffer.h"
#include "engine/render/components/PointLightComponent.h"

using namespace se;
using namespace se::ecs::components;

namespace app
{
    DEFINE_SPARK_SYSTEM(TestSystem)

    void LoadCubeMesh(MeshComponent* meshComp)
    {
        meshComp->model = asset::AssetManager::Get()->GetAsset<asset::Model>("/assets/models/cube.sass");
        auto mesh = meshComp->model->GetMesh(0);
        meshComp->vertBuffer = render::VertexBuffer::CreateVertexBuffer(mesh);
        meshComp->vertBuffer->CreatePlatformResource();
        meshComp->indexBuffer = render::IndexBuffer::CreateIndexBuffer(mesh);
        meshComp->indexBuffer->CreatePlatformResource();
    }

    void TestSystem::OnInit(const std::vector<ecs::Id>&, TransformComponent*)
    {
        if (m_Relationships.empty())
        {
            auto app = Application::Get();
            auto world = app->GetWorld();

            ecs::Id light1 = world->CreateEntity();
            auto* light1Transform = world->AddComponent<TransformComponent>(light1);
            light1Transform->pos = {-5.f, 5.f, 5.f};
            auto* light1Light = world->AddComponent<render::components::PointLightComponent>(light1);
            light1Light->color = {0.f, 0.f, 1.f};

            ecs::Id light2 = world->CreateEntity();
            auto* light2Transform = world->AddComponent<TransformComponent>(light2);
            light2Transform->pos = {5.f, 5.f, 5.f};
            auto* light2Light = world->AddComponent<render::components::PointLightComponent>(light2);
            light2Light->color = {1.f, 0.f, 0.f};

            // Cube 1
            ecs::Id entity = world->CreateEntity();
            auto* transform = world->AddComponent<TransformComponent>(entity);
            transform->pos = math::Vec3(-2.f, 0.f, 0.f);

            auto* assetManager = asset::AssetManager::Get();
            auto uberVertex = assetManager->GetAsset<asset::Shader>("/builtin_assets/uber_vertex.sass");
            auto diffuse = assetManager->GetAsset<asset::Shader>("/builtin_assets/diffuse_texture.sass");
            auto pointLght = assetManager->GetAsset<asset::Shader>("/builtin_assets/point_light.sass");

            auto* mesh = world->AddComponent<MeshComponent>(entity);
            LoadCubeMesh(mesh);

            mesh->material = render::Material::CreateMaterial(
                {uberVertex},
                {diffuse, pointLght});
            render::RenderState rs;
            rs.depthComp = render::DepthCompare::Less;
            rs.lit = true;
            mesh->material->SetRenderState(rs);
            auto texture = assetManager->GetAsset<asset::Texture>("/assets/textures/uvmap.sass");
            mesh->material->SetUniform("Texture", asset::shader::ast::AstType::Sampler2D, 1, &texture);

            // Cube 2
            ecs::Id entity2 = world->CreateEntity();
            auto* transform2 = world->AddComponent<TransformComponent>(entity2);
            transform2->pos = math::Vec3(2.f, 0.f, 0.f);

            auto hueShader = assetManager->GetAsset<asset::Shader>("/assets/shaders/hue.sass");

            auto* mesh2 = world->AddComponent<MeshComponent>(entity2);
            LoadCubeMesh(mesh2);
            mesh2->material = render::Material::CreateMaterial(
                {uberVertex},
                {diffuse, pointLght, hueShader});
            mesh2->material->SetRenderState(rs);
            mesh2->material->GetShaderSettings().SetSetting("color_setting", math::Vec3(0, 0, 1));
            auto texture2 = assetManager->GetAsset<asset::Texture>("/assets/textures/uvmap2.sass");
            mesh2->material->SetUniform("Texture", asset::shader::ast::AstType::Sampler2D, 1, &texture2);

            auto testRelationship = ecs::CreateEntityRelationship<ChildOf>(entity);
            world->AddRelationship(entity2, testRelationship);
            world->CreateAppSystem<TestSystem>({ testRelationship });
        }
    }

    void TestSystem::OnUpdate(const std::vector<ecs::Id>& entities, TransformComponent* transform)
    {
        auto app = Application::Get();
        auto dt = app->GetDeltaTime();
        for (size_t i = 0; i < entities.size(); ++i)
        {
            auto& transformComp = transform[i];
            transformComp.rot.y += 5.f * dt;
        }
    }
}
