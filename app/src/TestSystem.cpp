#include "TestSystem.h"
#include "engine/debug/Log.h"

namespace app
{
DEFINE_SPARK_SYSTEM(TestSystem)

    TestSystem::TestSystem(se::ecs::World& world)
            : se::ecs::System<const TestComponent1, const TestComponent2>(world)
    {

    }

    void TestSystem::OnUpdate(float dt, size_t count, const app::TestComponent1* nodes, const app::TestComponent2* otherComps)
    {
        //se::debug::Log::Info("dt: {}", dt);
        for (size_t i = 0; i < count; ++i)
        {
            const TestComponent1& node = nodes[i];
            const TestComponent2& otherComp = otherComps[i];

            //se::debug::Log::Info("node {} {}", node.key, node.value);
            //se::debug::Log::Info("otherComp {}", otherComp.lol);
        }
    }
}