#include "spark.h"

#include <engine/math/Mat4.h>
#include <engine/asset/binary/Database.h>
#include <engine/asset/texture/Texture.h>
#include <engine/render/Material.h>
#include <engine/shader/ast/Types.h>
#include <engine/ecs/components/MeshComponent.h>
#include <engine/render/RenderState.h>
#include <engine/render/Renderer.h>
#include "TestSystem.h"
#include "engine/debug/Log.h"
#include "engine/Application.h"
#include "engine/ecs/components/TransformComponent.h"
#include "platform/IWindow.h"

using namespace se;
using namespace se::ecs::components;

namespace app
{
    DEFINE_SPARK_SYSTEM(TestSystem)

    void TestSystem::OnInit(const std::vector<ecs::EntityId>&, const TransformComponent*, const MeshComponent*, ActiveCameraComponent*)
    {
        auto app = Application::Get();
        auto world = app->GetWorld();

        auto* activeCameraComp = world->AddSingletonComponent<ActiveCameraComponent>();
        activeCameraComp->view = math::LookAt(math::Vec3(-4.f, 3.f, 4.f),
                                              math::Vec3(0.f, 0.f, 0.f),
                                              math::Vec3(0.f, 1.f, 0.f));

        // Cube 1
        ecs::EntityId entity = world->CreateEntity();
        auto* transform = world->AddComponent<ecs::components::TransformComponent>(entity);
        transform->pos = math::Vec3(-1.1f, 0.f, -1.1f);

        auto* mesh = world->AddComponent<ecs::components::MeshComponent>(entity);
        mesh->material = render::Material::CreateMaterial(
                {"/builtin_assets/shader.vert"},
                {"/builtin_assets/shader.frag", "/builtin_assets/shader2.frag"});
        render::RenderState rs;
        rs.depthComp = render::DepthCompare::Less;
        mesh->material->SetRenderState(rs);
        mesh->material->CreatePlatformResources();

        auto db = asset::binary::Database::Load("/assets/textures/uvtemplate.sass", true);
        asset::Texture texture;
        texture.Deserialise(db);
        texture.CreatePlatformResource();

        mesh->material->SetUniform("Texture", shader::ast::Type::Sampler2D, &texture);

        // Cube 2
        ecs::EntityId entity2 = world->CreateEntity();
        auto* transform2 = world->AddComponent<ecs::components::TransformComponent>(entity2);
        transform2->pos = math::Vec3(1.1f, 0.f, 1.1f);

        auto* mesh2 = world->AddComponent<ecs::components::MeshComponent>(entity2);
        mesh2->material = render::Material::CreateMaterial(
                {"/builtin_assets/shader.vert"},
                {"/builtin_assets/shader.frag", "/builtin_assets/shader2.frag"});
        mesh2->material->SetRenderState(rs);
        mesh2->material->CreatePlatformResources();

        auto db2 = asset::binary::Database::Load("/assets/textures/uvtemplate2.sass", true);
        asset::Texture texture2;
        texture2.Deserialise(db2);
        texture2.CreatePlatformResource();

        mesh2->material->SetUniform("Texture", shader::ast::Type::Sampler2D, &texture2);
    }

    void TestSystem::OnUpdate(const std::vector<ecs::EntityId>& entities, const TransformComponent* transform,
                              const MeshComponent* mesh, ActiveCameraComponent* camera)
    {
        auto app = Application::Get();
        camera->proj = math::Perspective(math::Radians(45.f), (float)app->GetPrimaryWindow()->GetWidth() / (float)app->GetPrimaryWindow()->GetHeight(),.1f, 100.f);
        for (int i = 0; i < entities.size(); ++i)
        {
            math::Mat4 mvp = camera->proj * camera->view * math::Translation(transform[i].pos);
            mesh[i].material->SetUniform("MVP", shader::ast::Type::Mat4, &mvp[0]);
        }
    }

    void TestSystem::OnRender(const std::vector<se::ecs::EntityId>& entities, const TransformComponent*, const MeshComponent* mesh, ActiveCameraComponent*)
    {
        auto app = Application::Get();

        auto renderer = se::render::Renderer::Get();
        auto window = app->GetPrimaryWindow();
        renderer->Submit(window, se::render::RenderCommand([]
        {
            se::render::RenderCommand::Clear(true, true);
        }));

        for (int i = 0; i < entities.size(); ++i)
        {
            const auto& meshComp = mesh[i];
            renderer->Submit(window, se::render::RenderCommand([&meshComp]
            {
                se::render::RenderCommand::SubmitGeo(meshComp.material, meshComp.vertBuffer, 12 * 3);
            }));
        }
    }

    void TestSystem::OnShutdown(const std::vector<ecs::EntityId>&, const TransformComponent*,
                                const MeshComponent*, ActiveCameraComponent*)
    {

    }
}