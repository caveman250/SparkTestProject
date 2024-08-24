#include "TestObserver.h"

namespace app
{
    void TestObserver::OnAdded(ecs::Id entity, ecs::components::MeshComponent *component)
    {
        int lol =1;
    }

    void TestObserver::OnRemoved(ecs::Id, ecs::components::MeshComponent *)
    {

    }
}
