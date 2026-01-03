#pragma once

#include "engine/ecs/System.h"
#include "engine/ecs/components/MeshComponent.h"

using namespace se;
using namespace se::ecs::components;

namespace app
{
    class TestSystem : public ecs::AppSystem
    {
        SPARK_SYSTEM()
    public:
        static ecs::SystemDeclaration GetSystemDeclaration();
        void OnInit(const ecs::SystemUpdateData& updateData) override;
        void OnUpdate(const ecs::SystemUpdateData& updateData) override;
    };
}
