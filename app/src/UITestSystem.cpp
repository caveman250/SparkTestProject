
#include <engine/ui/components/ScrollBoxComponent.h>
#include "spark.h"

#include "UITestSystem.h"

#include <engine/ui/components/ImageComponent.h>

#include "engine/Application.h"
#include "engine/ecs/components/RootComponent.h"
#include "engine/ui/components/ButtonComponent.h"
#include "engine/ui/components/TextComponent.h"
#include "engine/ui/components/TitleBarComponent.h"
#include "engine/ui/components/TreeViewComponent.h"
#include "engine/ui/components/WindowComponent.h"
#include "engine/ui/util/TreeViewUtil.h"
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
        auto assetManager = asset::AssetManager::Get();

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

        auto scrollBoxEntity = world->CreateEntity("ScrollBox");
        auto scrollBox = world->AddComponent<ui::components::ScrollBoxComponent>(scrollBoxEntity);
        auto scrollBoxRect = world->AddComponent<ui::components::RectTransformComponent>(scrollBoxEntity);
        scrollBoxRect->anchors = { 0.f, 1.f, 0.f, 1.f };
        world->AddChild(childArea, scrollBoxEntity);

        auto scrollBarEntity = world->CreateEntity("Scroll Bar");
        auto scrollBarImage = world->AddComponent<ui::components::ImageComponent>(scrollBarEntity);
        auto vert = assetManager->GetAsset<asset::Shader>("/builtin_assets/shaders/ui.sass");
        auto frag = assetManager->GetAsset<asset::Shader>("/builtin_assets/shaders/flat_color.sass");
        scrollBarImage->material = render::Material::CreateMaterial({vert}, {frag});
        scrollBarImage->material->GetShaderSettings().SetSetting("color_setting", math::Vec3(0.8f, 0.8f, 0.8f));
        auto scrollBarRect = world->AddComponent<ui::components::RectTransformComponent>(scrollBarEntity);
        scrollBarRect->anchors = { 1.f, 1.f, 0.f, 0.f };
        scrollBarRect->minX = -10.f;
        scrollBarRect->maxX = 5.f;
        scrollBarRect->minY = 5.f;
        scrollBarRect->maxY = 25.f;
        std::function<void(const ui::components::RectTransformComponent*, float, ui::components::RectTransformComponent*)> scrollCb =
            [](const ui::components::RectTransformComponent* scrollRect, float scrollAmount, ui::components::RectTransformComponent* rect)
        {
            float availableSize = scrollRect->rect.size.y - 25.f - 5.f * 2.f;

            rect->minY = 5.f + availableSize * scrollAmount;
            rect->maxY = rect->minY + 25.f;
            rect->needsLayout = true;

            rect->rect.topLeft.y = scrollRect->rect.topLeft.y + 5.f + availableSize * scrollAmount;
        };
        scrollBox->onScrolled.Subscribe<ui::components::RectTransformComponent>(scrollBarEntity, std::move(scrollCb));
        world->AddChild(childArea, scrollBarEntity);

        ui::components::TreeViewComponent* treeViewComp = nullptr;
        ui::components::RectTransformComponent* transformComp = nullptr;
        auto treeView = ui::util::CreateTreeView(&treeViewComp, &transformComp);
        world->AddChild(scrollBoxEntity, treeView);
        transformComp->anchors = { 0.f, 1.f, 0.f, 0.f };

        std::vector<ecs::Id> treeNodes = {};
        for (size_t i = 0; i < 40; ++i)
        {
            ui::components::TreeNodeComponent* treeNodeComp = nullptr;
            ui::components::TextComponent* textComp = nullptr;
            ecs::Id parent;
            if (!treeNodes.empty())
            {
                parent = treeNodes[std::rand() % treeNodes.size()];
            }
            else
            {
                parent = treeView;
            }

            auto treeNode = ui::util::InsertTreeNode(treeView, treeViewComp, parent, std::format("TreeNode {0}", i), &treeNodeComp, &textComp);
            textComp->text = std::format("Node {0}", i);
            treeNodes.push_back(treeNode);
        }
    }

    void UITestSystem::OnUpdate(const std::vector<ecs::Id>& , ui::components::RectTransformComponent*)
    {
    }
}
