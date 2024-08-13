#pragma once

#include "spark.h"
#include "engine/ecs/System.h"
#include "engine/ecs/components/TransformComponent.h"

using namespace se;
using namespace se::ecs::components;

namespace app
{
    class RelationshipTestSystem : public ecs::System<TransformComponent>
    {
        DECLARE_SPARK_SYSTEM(RelationshipTestSystem)

        void OnUpdate(const std::vector<se::ecs::EntityId>&, TransformComponent*) override;
    };
}
