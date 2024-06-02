#include "TestSystem.h"
#include "engine/debug/Log.h"
#include "engine/Application.h"

namespace app
{
DEFINE_SPARK_SYSTEM(TestSystem)

    void TestSystem::OnUpdate(const std::vector<se::ecs::EntityId>& entities, const app::TestComponent1* , const app::TestComponent2* , const TestSingletonComponent* )
    {
        auto app = se::Application::Get();
        auto world = app->GetWorld();

        float dt = app->GetDeltaTime();

        for (int i = 0; i < entities.size(); ++i)
        {
            se::debug::Log::Info("TestSystem - Entity {}", entities[i]);
        }
    }
}