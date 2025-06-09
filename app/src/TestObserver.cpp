#include "TestObserver.h"

namespace app
{
    void TestObserver::OnAdded(const ecs::Id&, ecs::components::MeshComponent*)
    {
    }

    void TestObserver::OnRemoved(const ecs::Id&, ecs::components::MeshComponent*)
    {

    }
}
