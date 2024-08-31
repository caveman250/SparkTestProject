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
#include "engine/ui/components/TitleBarComponent.h"
#include "engine/ui/components/WindowComponent.h"
#include "engine/ui/util/WindowUtil.h"

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

        ui::components::RectTransformComponent* windowTransform;
        ui::components::WindowComponent* windowComp;
        ui::components::TitleBarComponent* titleBarComp;
        ecs::Id childArea;
        ui::util::CreateWindow(&windowTransform, &windowComp, &titleBarComp, childArea);
        windowTransform->anchors = { 0.f, 0.f, 0.f, 0.f };
        windowTransform->minX = 800;
        windowTransform->maxX = 1200;
        windowTransform->minY = 200;
        windowTransform->maxY = 720;

        ecs::Id textEntity = world->CreateEntity();
        auto textTransform = world->AddComponent<ui::components::RectTransformComponent>(textEntity);
        textTransform->anchors = { 0.f, 1.f, 0.f, 1.f };
        textTransform->minX = 0;
        textTransform->maxX = 0;
        textTransform->minY = 0;
        textTransform->maxY = 0;
        auto text = world->AddComponent<ui::components::TextComponent>(textEntity);
        text->font = assetManager->GetAsset<asset::Font>("/builtin_assets/fonts/Arial.sass");
        text->fontSize = 24;
        text->text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed ultricies sed felis et pulvinar. Etiam tincidunt magna eget faucibus venenatis.";

        world->AddChild(childArea, textEntity);
    }

    void UITestSystem::OnUpdate(const std::vector<ecs::Id>& , ui::components::RectTransformComponent*)
    {
    }
}
