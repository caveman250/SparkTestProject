#include "spark.h"

#include <engine/math/Mat4.h>
#include <engine/asset/binary/Database.h>
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
#include "engine/asset/shader/ast/ASTNode.h"
#include "engine/asset/shader/ast/MainNode.h"
#include "engine/ecs/components/TransformComponent.h"
#include "engine/reflect/Util.h"
#include "platform/IWindow.h"

using namespace se;
using namespace se::ecs::components;

namespace app
{
    DEFINE_SPARK_SYSTEM(TestSystem)

    void LoadCubeMesh(MeshComponent* meshComp)
    {
        auto db = asset::binary::Database::Load("/assets/models/cube.sass", true);
        meshComp->model = reflect::DeserialiseType<asset::Model>(db);
        auto mesh = meshComp->model.GetMesh(0);
        meshComp->vertBuffer = render::VertexBuffer::CreateVertexBuffer(mesh);
        meshComp->vertBuffer->CreatePlatformResource();
    }

    void TestSystem::OnInit(const std::vector<ecs::EntityId>&, TransformComponent*, const MeshComponent*, camera::ActiveCameraComponent*)
    {
        auto app = Application::Get();
        auto world = app->GetWorld();

        world->AddSingletonComponent<camera::ActiveCameraComponent>();

        math::Vec3 lightPos = {5.f, 5.f, 5.f };

        // Cube 1
        ecs::EntityId entity = world->CreateEntity();
        auto* transform = world->AddComponent<TransformComponent>(entity);
        transform->pos = math::Vec3(-2.f, 0.f, 0.f);

        auto* mesh = world->AddComponent<MeshComponent>(entity);
        LoadCubeMesh(mesh);
        mesh->material = render::Material::CreateMaterial(
                {"/builtin_assets/uber_vertex.ssl"},
                {"/builtin_assets/diffuse_texture.ssl", "/builtin_assets/point_light.ssl"});
        render::RenderState rs;
        rs.depthComp = render::DepthCompare::Less;
        mesh->material->SetRenderState(rs);
        mesh->material->CreatePlatformResources(*mesh->vertBuffer);
        mesh->material->SetUniform("lightPos", asset::shader::ast::AstType::Vec3, &lightPos[0]);

        auto db = asset::binary::Database::Load("/assets/textures/uvmap.sass", true);
        asset::Texture texture = reflect::DeserialiseType<asset::Texture>(db);
        texture.CreatePlatformResource();

        mesh->material->SetUniform("Texture", asset::shader::ast::AstType::Sampler2D, &texture);

        // Cube 2
        ecs::EntityId entity2 = world->CreateEntity();
        auto* transform2 = world->AddComponent<TransformComponent>(entity2);
        transform2->pos = math::Vec3(2.f, 0.f, 0.f);

        auto* mesh2 = world->AddComponent<ecs::components::MeshComponent>(entity2);
        LoadCubeMesh(mesh2);
        mesh2->material = render::Material::CreateMaterial(
                {"/builtin_assets/uber_vertex.ssl"},
                {"/builtin_assets/diffuse_texture.ssl", "/builtin_assets/point_light.ssl", "/builtin_assets/red.ssl"});
        mesh2->material->SetRenderState(rs);
        mesh2->material->CreatePlatformResources(*mesh2->vertBuffer);
        mesh2->material->SetUniform("lightPos", asset::shader::ast::AstType::Vec3, &lightPos[0]);

        auto db2 = asset::binary::Database::Load("/assets/textures/uvmap2.sass", true);
        asset::Texture texture2 = reflect::DeserialiseType<asset::Texture>(db);
        texture2.CreatePlatformResource();

        mesh2->material->SetUniform("Texture", asset::shader::ast::AstType::Sampler2D, &texture2);

        texture.Release();
        texture2.Release();
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

            SPARK_ASSERT((float*)&model[0] == &model[0][0]);

            mesh[i].material->SetUniform("model", asset::shader::ast::AstType::Mat4, &model[0][0]);
            mesh[i].material->SetUniform("view", asset::shader::ast::AstType::Mat4, &camera->view[0][0]);
            mesh[i].material->SetUniform("proj", asset::shader::ast::AstType::Mat4, &camera->proj[0][0]);
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