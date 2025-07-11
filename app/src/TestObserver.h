#pragma once
#include "engine/ecs/Observer.h"
#include "engine/ecs/components/MeshComponent.h"

using namespace se;

namespace app
{
    class TestObserver : public ecs::Observer<ecs::components::MeshComponent>
    {
    public:
        TestObserver() = default;

    private:
        void OnAdded(const ecs::Id& entity, ecs::components::MeshComponent *component) override;
        void OnRemoved(const ecs::Id& , ecs::components::MeshComponent *) override;
    };
}
