
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
#include "engine/ui/util/ScrollBoxUtil.h"

using namespace se;
using namespace se::ecs::components;

namespace app
{
    DEFINE_SPARK_SYSTEM(UITestSystem)

    void UITestSystem::OnInit(const std::vector<ecs::Id>&, ui::components::RectTransformComponent*)
    {
        auto app = Application::Get();
        auto world = app->GetWorld();

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

        ui::components::ScrollBoxComponent* scrollBox = nullptr;
        ui::components::RectTransformComponent* scrollBoxTransform = nullptr;
        auto scrollBoxEntity = ui::util::CreateScrollBox(&scrollBox, &scrollBoxTransform);
        world->AddChild(childArea, scrollBoxEntity);

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
