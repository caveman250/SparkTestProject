#include "spark.h"

#include <engine/math/Mat4.h>
#include <engine/asset/texture/Texture.h>
#include <engine/render/Material.h>
#include <engine/asset/shader/ast/Types.h>
#include <engine/ecs/components/MeshComponent.h>
#include <engine/render/RenderState.h>
#include <engine/asset/mesh/Model.h>
#include <engine/render/VertexBuffer.h>
#include "TestButtonSystem.h"

#include "TestApplication.h"
#include "TestObserver.h"
#include "engine/Application.h"
#include "engine/asset/AssetManager.h"
#include "engine/ecs/components/TransformComponent.h"
#include "engine/ecs/relationships/ChildOf.h"
#include "engine/render/IndexBuffer.h"
#include "engine/render/components/PointLightComponent.h"
#include "engine/ui/button/ButtonSubscription.h"

using namespace se;
using namespace se::ecs::components;

namespace app
{
    DEFINE_SPARK_SYSTEM(TestButtonSystem)

    void TestButtonSystem::OnUpdate(const std::vector<ecs::Id>& entities, TransformComponent* transformComps, const ui::components::ReactToButtonComponent* reactToButtonComps)
    {
        auto app = Application::Get();
        auto dt = app->GetDeltaTime();
        for (size_t i = 0; i < entities.size(); ++i)
        {
            auto& transformComp = transformComps[i];
            const auto& reactTobuttonComp = reactToButtonComps[i];
            if (reactTobuttonComp.subscription->Pressed())
            {
                transformComp.pos.y += 10.f * dt;
            }
        }
    }
}
