#include "spark.h"

#include <engine/math/Mat4.h>
#include <engine/render/Material.h>
#include <engine/ecs/components/MeshComponent.h>
#include "UITestSystem.h"

#include "TestApplication.h"
#include "engine/Application.h"
#include "engine/asset/AssetManager.h"
#include "engine/ecs/components/RootComponent.h"
#include "engine/ui/components/ButtonComponent.h"
#include "engine/ui/components/ImageComponent.h"
#include "engine/ui/components/TextComponent.h"

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
        auto texture = assetManager->GetAsset<asset::Texture>("/builtin_assets/textures/default_texture.sass");
        image->material->SetUniform("Texture", asset::shader::ast::AstType::Sampler2D, 1, &texture);

        ecs::Id entity2 = world->CreateEntity();
        auto rectTransform2 = world->AddComponent<ui::components::RectTransformComponent>(entity2);
        rectTransform2->anchors = { 0.1f, 0.9f, 0.1f, 0.9f };
        rectTransform2->minX = 0;
        rectTransform2->maxX = 0;
        rectTransform2->minY = 0;
        rectTransform2->maxY = 0;

        auto image2 = world->AddComponent<ui::components::ImageComponent>(entity2);
        image2->material = render::Material::CreateMaterial({vert}, {frag});
        auto texture2 = assetManager->GetAsset<asset::Texture>("/assets/textures/aang.sass");
        image2->material->SetUniform("Texture", asset::shader::ast::AstType::Sampler2D, 1, &texture2);

        world->AddChild(entity, entity2);

        ecs::Id entity3 = world->CreateEntity();
        auto rectTransform3 = world->AddComponent<ui::components::RectTransformComponent>(entity3);
        rectTransform3->anchors = { 0.f, 0.f, 0.f, 0.f };
        rectTransform3->minX = 210;
        rectTransform3->maxX = 710;
        rectTransform3->minY = 10;
        rectTransform3->maxY = 200;

        auto colorFrag = assetManager->GetAsset<asset::Shader>("/builtin_assets/shaders/flat_color.sass");
        auto image3 = world->AddComponent<ui::components::ImageComponent>(entity3);
        image3->material = render::Material::CreateMaterial({vert}, {colorFrag});
        image3->material->GetShaderSettings().SetSetting("color_setting", math::Vec3(0.2f, 0.2f, 0.2f));
        image3->material->SetUniform("Texture", asset::shader::ast::AstType::Sampler2D, 1, &texture);

        ecs::Id entity4 = world->CreateEntity();
        auto rectTransform4 = world->AddComponent<ui::components::RectTransformComponent>(entity4);
        rectTransform4->anchors = { 0.f, 1.f, 0.f, 1.f };
        rectTransform4->minX = 0;
        rectTransform4->maxX = 0;
        rectTransform4->minY = 0;
        rectTransform4->maxY = 0;
        auto text = world->AddComponent<ui::components::TextComponent>(entity4);
        text->font = assetManager->GetAsset<asset::Font>("/builtin_assets/fonts/Arial.sass");
        text->fontSize = 24;
        text->text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed ultricies sed felis et pulvinar. Etiam tincidunt magna eget faucibus venenatis.";

        world->AddChild(entity3, entity4);
    }

    void UITestSystem::OnUpdate(const std::vector<ecs::Id>& , ui::components::RectTransformComponent*)
    {
    }
}
