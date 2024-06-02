#pragma once

#include <engine/ecs/System.h>
#include "TestComponent1.h"
#include "TestComponent2.h"
#include "TestSingletonComponent.h"

namespace app
{
    class TestSystem : public se::ecs::System<const TestComponent1, const TestComponent2, const TestSingletonComponent>
    {
        DECLARE_SPARK_SYSTEM(TestSystem)
    public:
        void OnUpdate(const std::vector<se::ecs::EntityId>& entities, const app::TestComponent1* tc1, const app::TestComponent2* tc2, const TestSingletonComponent* tsc) override;
    };
}
