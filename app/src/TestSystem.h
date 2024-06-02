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
        void OnUpdate(float dt, size_t count, const app::TestComponent1* ts, const app::TestComponent2* ts1, const TestSingletonComponent* testSingletonComp) override;
    };
}
