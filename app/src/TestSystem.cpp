#include "spark.h"

#include <engine/math/Mat4.h>
#include <engine/asset/binary/Database.h>
#include <engine/asset/texture/Texture.h>
#include <engine/render/Material.h>
#include <engine/shader/ast/Types.h>
#include <engine/ecs/components/MeshComponent.h>
#include <engine/render/RenderState.h>
#include <engine/render/Renderer.h>
#include <engine/asset/mesh/Model.h>
#include <engine/render/VertexBuffer.h>
#include "TestSystem.h"

#include "TestApplication.h"
#include "engine/Application.h"
#include "engine/ecs/components/TransformComponent.h"
#include "platform/IWindow.h"

using namespace se;
using namespace se::ecs::components;

namespace app
{
    DEFINE_SPARK_SYSTEM(TestSystem)

    void LoadCubeMesh(MeshComponent* meshComp)
    {
        auto db = asset::binary::Database::Load("/assets/models/cube.sass", true);
        meshComp->model.Deserialise(db);
        auto mesh = meshComp->model.GetMesh(0);
        meshComp->vertBuffer = render::VertexBuffer::CreateVertexBuffer(mesh);
        meshComp->vertBuffer->CreatePlatformResource();
    }

    void TestSystem::OnInit(const std::vector<ecs::EntityId>&, TransformComponent*, const MeshComponent*, camera::ActiveCameraComponent*)
    {
        auto app = Application::Get();
        auto world = app->GetWorld();

        world->AddSingletonComponent<camera::ActiveCameraComponent>();

        // Cube 1
        ecs::EntityId entity = world->CreateEntity();
        auto* transform = world->AddComponent<TransformComponent>(entity);
        transform->pos = math::Vec3(-2.f, 0.f, 0.f);

        auto* mesh = world->AddComponent<ecs::components::MeshComponent>(entity);
        LoadCubeMesh(mesh);
        mesh->material = render::Material::CreateMaterial(
                {"/builtin_assets/uber_vertex.slsl"},
                {"/builtin_assets/diffuse_texture.slsl", "/builtin_assets/point_light.slsl"});
        render::RenderState rs;
        rs.depthComp = render::DepthCompare::Less;
        mesh->material->SetRenderState(rs);
        mesh->material->CreatePlatformResources(*mesh->vertBuffer);

        auto db = asset::binary::Database::Load("/assets/textures/uvmap.sass", true);
        asset::Texture texture;
        texture.Deserialise(db);
        texture.CreatePlatformResource();

        mesh->material->SetUniform("Texture", shader::ast::Type::Sampler2D, &texture);

        // Cube 2
        ecs::EntityId entity2 = world->CreateEntity();
        auto* transform2 = world->AddComponent<TransformComponent>(entity2);
        transform2->pos = math::Vec3(2.f, 0.f, 0.f);

        auto* mesh2 = world->AddComponent<ecs::components::MeshComponent>(entity2);
        LoadCubeMesh(mesh2);
        mesh2->material = render::Material::CreateMaterial(
                {"/builtin_assets/uber_vertex.slsl"},
                {"/builtin_assets/diffuse_texture.slsl", "/builtin_assets/point_light.slsl", "/builtin_assets/red.slsl"});
        mesh2->material->SetRenderState(rs);
        mesh2->material->CreatePlatformResources(*mesh2->vertBuffer);

        auto db2 = asset::binary::Database::Load("/assets/textures/uvmap2.sass", true);
        asset::Texture texture2;
        texture2.Deserialise(db2);
        texture2.CreatePlatformResource();

        mesh2->material->SetUniform("Texture", shader::ast::Type::Sampler2D, &texture2);
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

            math::Mat4 model = math::Translation(transformComp.pos);
            model = model * math::AxisAngle(math::Vec3(1.0f, 0.0f, 0.0f), transformComp.rot.x);
            model = model * math::AxisAngle(math::Vec3(0.0f, 1.0f, 0.0f), transformComp.rot.y);
            model = model * math::AxisAngle(math::Vec3(0.0f, 0.0f, 1.0f), transformComp.rot.z);

            model = model * math::Scale(transformComp.scale);

            mesh[i].material->SetUniform("model", shader::ast::Type::Mat4, &model[0]);
            mesh[i].material->SetUniform("view", shader::ast::Type::Mat4, &camera->view[0]);
            mesh[i].material->SetUniform("proj", shader::ast::Type::Mat4, &camera->proj[0]);
            math::Vec3 lol = {5.f, 5.f, 5.f };
            mesh[i].material->SetUniform("lightPos", shader::ast::Type::Vec3, &lol[0]);
        }
    }

    void TestSystem::OnRender(const std::vector<se::ecs::EntityId>& entities, TransformComponent*, const MeshComponent* mesh, camera::ActiveCameraComponent*)
    {
        auto app = TestApplication::GetTestApplication();

        auto renderer = se::render::Renderer::Get();
        auto window = app->GetPrimaryWindow();
        renderer->Submit<se::render::commands::Clear>(window, true, true);

        for (size_t i = 0; i < entities.size(); ++i)
        {
            const auto& meshComp = mesh[i];
            renderer->Submit<se::render::commands::SubmitGeo>(window, meshComp.material, meshComp.vertBuffer, 36);
        }
    }

    void TestSystem::OnShutdown(const std::vector<ecs::EntityId>&, TransformComponent*, const MeshComponent*, camera::ActiveCameraComponent*)
    {

    }
}