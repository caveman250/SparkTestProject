#pragma once

#include "engine/Application.h"
#include "engine/math/Mat4.h"
#include "engine/ecs/World.h"

namespace se::render
{
    class VertexBuffer;
    class Material;
}

namespace app
{
    struct Node;
    struct OtherComp;

    class TestApplication : public se::Application
    {
    public:
        static TestApplication* GetTestApplication();

        void Init() override;
        void Update() override;
        void Render() override;
    private:

        std::shared_ptr<se::render::Material> m_Material1;
        std::shared_ptr<se::render::Material> m_Material2;
        se::math::Mat4 m_View;
        std::shared_ptr<se::render::VertexBuffer> m_VertBuffer;
        se::ecs::World m_World;
    };
}
