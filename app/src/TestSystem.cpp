#include "spark.h"

#include <engine/math/Mat4.h>
#include <engine/asset/texture/Texture.h>
#include <engine/render/Material.h>
#include <engine/asset/shader/ast/Types.h>
#include <engine/ecs/components/MeshComponent.h>
#include <engine/render/RenderState.h>
#include <engine/render/Renderer.h>
#include <engine/asset/mesh/Model.h>
#include <engine/render/VertexBuffer.h>
#include "TestSystem.h"

#include "TestApplication.h"
#include "engine/Application.h"
#include "engine/asset/AssetManager.h"
#include "engine/ecs/components/TransformComponent.h"
#include "platform/IWindow.h"

namespace se::io
{
    class OutputFileStream;
}

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
    }

    void TestSystem::OnInit(const std::vector<ecs::EntityId>&, TransformComponent*, const MeshComponent*, camera::ActiveCameraComponent*)
    {
        auto app = Application::Get();
        auto world = app->GetWorld();

        world->AddSingletonComponent<camera::ActiveCameraComponent>();

        std::vector<math::Vec3> lightPos = {{-5.f, 5.f, 5.f}, {5.f, 5.f, 5.f} };
        std::vector<math::Vec3> lightColor = {{0.f, 0.f, 1.f}, {1.f, 0.f, 0.f} };

        // Cube 1
        ecs::EntityId entity = world->CreateEntity();
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
        mesh->material->SetRenderState(rs);
        ShaderSettings settings;
        settings.SetSetting("numLights", lightPos.size());
        mesh->material->SetShaderSettings(settings);
        mesh->material->CreatePlatformResources(*mesh->vertBuffer);
        mesh->material->SetUniform("lightPos", asset::shader::ast::AstType::Vec3, lightPos.size(), &lightPos[0]);
        mesh->material->SetUniform("lightColor", asset::shader::ast::AstType::Vec3, lightColor.size(), &lightColor[0]);

        auto texture = assetManager->GetAsset<asset::Texture>("/assets/textures/uvmap.sass");
        texture->CreatePlatformResource();

        mesh->material->SetUniform("Texture", asset::shader::ast::AstType::Sampler2D, 1, texture.get());

        // Cube 2
        ecs::EntityId entity2 = world->CreateEntity();
        auto* transform2 = world->AddComponent<TransformComponent>(entity2);
        transform2->pos = math::Vec3(2.f, 0.f, 0.f);

        auto redShader = assetManager->GetAsset<asset::Shader>("/assets/shaders/hue.sass");

        auto* mesh2 = world->AddComponent<MeshComponent>(entity2);
        LoadCubeMesh(mesh2);
        mesh2->material = render::Material::CreateMaterial(
                {uberVertex},
                {diffuse, pointLght, redShader});
        mesh2->material->SetRenderState(rs);

        ShaderSettings settings2;
        settings2.SetSetting("color_setting", math::Vec3(0, 0, 1));
        settings2.SetSetting("numLights", lightPos.size());
        mesh2->material->SetShaderSettings(settings2);
        mesh2->material->CreatePlatformResources(*mesh2->vertBuffer);
        mesh2->material->SetUniform("lightPos", asset::shader::ast::AstType::Vec3, lightPos.size(), &lightPos[0]);
        mesh2->material->SetUniform("lightColor", asset::shader::ast::AstType::Vec3, lightColor.size(), &lightColor[0]);

        auto texture2 = assetManager->GetAsset<asset::Texture>("/assets/textures/uvmap2.sass");
        texture2->CreatePlatformResource();

        mesh2->material->SetUniform("Texture", asset::shader::ast::AstType::Sampler2D, 1, texture2.get());

        texture->Release();
        texture2->Release();
    }

    void TestSystem::OnUpdate(const std::vector<ecs::EntityId>& entities, TransformComponent* transform,
                              const MeshComponent* mesh, camera::ActiveCameraComponent* camera)
    {
        auto app = Application::Get();

        auto dt = app->GetDeltaTime();
        camera->proj = math::Perspective(math::Radians(45.f), (float)app->GetPrimaryWindow()->GetWidth() / (float)app->GetPrimaryWindow()->GetHeight(),.1f, 100.f);
        for (size_t i = 0; i < entities.size(); ++i)
        {
            auto& transformComp = transform[i];

            transformComp.rot.y += 5.f * dt;

            math::Mat4 model = Translation(transformComp.pos);
            model = model * AxisAngle(math::Vec3(1.0f, 0.0f, 0.0f), transformComp.rot.x);
            model = model * AxisAngle(math::Vec3(0.0f, 1.0f, 0.0f), transformComp.rot.y);
            model = model * AxisAngle(math::Vec3(0.0f, 0.0f, 1.0f), transformComp.rot.z);

            model = model * Scale(transformComp.scale);

            SPARK_ASSERT((float*)&model[0] == &model[0][0]);

            mesh[i].material->SetUniform("model", asset::shader::ast::AstType::Mat4, 1, &model);
            mesh[i].material->SetUniform("view", asset::shader::ast::AstType::Mat4, 1, &camera->view);
            mesh[i].material->SetUniform("proj", asset::shader::ast::AstType::Mat4, 1, &camera->proj);
        }
    }

    void TestSystem::OnRender(const std::vector<ecs::EntityId>& entities, TransformComponent*, const MeshComponent* mesh, camera::ActiveCameraComponent*)
    {
        auto app = TestApplication::GetTestApplication();

        auto renderer = render::Renderer::Get();
        auto window = app->GetPrimaryWindow();
        renderer->Submit<render::commands::Clear>(window, true, true);

        for (size_t i = 0; i < entities.size(); ++i)
        {
            const auto& meshComp = mesh[i];
            renderer->Submit<render::commands::SubmitGeo>(window, meshComp.material, meshComp.vertBuffer, 36);
        }
    }

    void TestSystem::OnShutdown(const std::vector<ecs::EntityId>&, TransformComponent*, const MeshComponent*, camera::ActiveCameraComponent*)
    {

    }
}