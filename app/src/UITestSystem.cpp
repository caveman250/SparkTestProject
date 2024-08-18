#include "spark.h"

#include <engine/math/Mat4.h>
#include <engine/render/Material.h>
#include <engine/ecs/components/MeshComponent.h>
#include "UITestSystem.h"

#include "TestApplication.h"
#include "engine/Application.h"
#include "engine/asset/AssetManager.h"
#include "engine/ui/components/ImageComponent.h"

using namespace se;
using namespace se::ecs::components;

namespace app
{
    DEFINE_SPARK_SYSTEM(UITestSystem)

    void UITestSystem::OnInit(const std::vector<ecs::Id>&, ui::components::RectTransformComponent*)
    {
        auto app = Application::Get();
        auto world = app->GetWorld();

        auto* assetManager = asset::AssetManager::Get();
        auto vert = assetManager->GetAsset<asset::Shader>("/builtin_assets/shaders/ui.sass");
        auto frag = assetManager->GetAsset<asset::Shader>("/builtin_assets/shaders/diffuse_texture.sass");

        ecs::Id entity = world->CreateEntity();
        auto rectTransform = world->AddComponent<ui::components::RectTransformComponent>(entity);
        rectTransform->anchors = { 0.f, 0.f, 0.f, 0.f };
        rectTransform->minX = 10;
        rectTransform->maxX = 200;
        rectTransform->minY = 10;
        rectTransform->maxY = 200;

        auto image = world->AddComponent<ui::components::ImageComponent>(entity);
        image->material = render::Material::CreateMaterial({vert}, {frag});
        auto texture = assetManager->GetAsset<asset::Texture>("/assets/textures/red.sass");
        image->material->SetUniform("Image", asset::shader::ast::AstType::Sampler2D, 1, &texture);

        ecs::Id entity2 = world->CreateEntity();
        auto rectTransform2 = world->AddComponent<ui::components::RectTransformComponent>(entity2);
        rectTransform2->anchors = { 0.f, 0.8f, 0.f, 0.8f };
        rectTransform2->minX = 0;
        rectTransform2->maxX = 0;
        rectTransform2->minY = 0;
        rectTransform2->maxY = 0;

        auto image2 = world->AddComponent<ui::components::ImageComponent>(entity2);
        image2->material = render::Material::CreateMaterial({vert}, {frag});
        auto texture2 = assetManager->GetAsset<asset::Texture>("/assets/textures/blue.sass");
        image2->material->SetUniform("Image", asset::shader::ast::AstType::Sampler2D, 1, &texture2);

        world->AddChild(entity, entity2);
    }

    void UITestSystem::OnUpdate(const std::vector<ecs::Id>& entities, ui::components::RectTransformComponent* rect)
    {
    }
}
