#include "RelationshipTestSystem.h"

namespace app
{
    DEFINE_SPARK_SYSTEM(RelationshipTestSystem)

    void RelationshipTestSystem::OnUpdate(const std::vector<ecs::Id>& entities, TransformComponent* transform)
    {
        float dt = Application::Get()->GetDeltaTime();
        for (size_t i = 0; i < entities.size(); ++i)
        {
            transform[i].pos.y += 2.f * dt;
        }
    }
}