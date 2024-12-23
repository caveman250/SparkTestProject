
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

    }

    void UITestSystem::OnUpdate(const std::vector<ecs::Id>& , ui::components::RectTransformComponent*)
    {
    }
}
