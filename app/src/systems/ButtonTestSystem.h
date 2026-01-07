#pragma once

#include "engine/ecs/System.h"
#include "engine/ecs/components/MeshComponent.h"

using namespace se;
using namespace se::ecs::components;

namespace app
{
    class ButtonTestSystem : public ecs::AppSystem
    {
        SPARK_SYSTEM()
    public:
        static ecs::SystemDeclaration GetSystemDeclaration();
        void OnUpdate(const ecs::SystemUpdateData& updateData) override;

        SPARK_FUNCTION()
        void OnTestButtonPressed();
    };
}
