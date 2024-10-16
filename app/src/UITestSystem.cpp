#include "spark.h"

#include "UITestSystem.h"

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

        ui::components::TreeViewComponent* treeViewComp = nullptr;
        ui::components::RectTransformComponent* transformComp = nullptr;
        auto treeView = ui::util::CreateTreeView(&treeViewComp, &transformComp);
        world->AddChild(childArea, treeView);
        transformComp->anchors = { 0.f, 1.f, 0.f, 1.f };

        ui::components::TreeNodeComponent* treeNodeComp = nullptr;
        ui::components::TextComponent* textComp = nullptr;
        auto treeNode = ui::util::InsertTreeNode(treeView, treeViewComp, treeView, "TreeNode One", &treeNodeComp, &textComp);
        textComp->text = "one";

        ui::components::TreeNodeComponent* treeNodeComp2 = nullptr;
        ui::components::TextComponent* textComp2 = nullptr;
        auto treeNode2 = ui::util::InsertTreeNode(treeView, treeViewComp, treeNode, "TreeNode Two", &treeNodeComp2, &textComp2);
        textComp2->text = "two";

        ui::components::TreeNodeComponent* treeNodeComp3 = nullptr;
        ui::components::TextComponent* textComp3 = nullptr;
        ui::util::InsertTreeNode(treeView, treeViewComp, treeNode, "TreeNode Three", &treeNodeComp3, &textComp3);
        textComp3->text = "three";

        ui::components::TreeNodeComponent* treeNodeComp4 = nullptr;
        ui::components::TextComponent* textComp4 = nullptr;
        ui::util::InsertTreeNode(treeView, treeViewComp, treeNode2, "TreeNode Four", &treeNodeComp4, &textComp4);
        textComp4->text = "four";
    }

    void UITestSystem::OnUpdate(const std::vector<ecs::Id>& , ui::components::RectTransformComponent*)
    {
    }
}
