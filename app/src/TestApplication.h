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

        se::IWindow* GetSecondaryWindow() const { return m_SecondaryWindow; }

    private:
        se::IWindow* m_SecondaryWindow = nullptr;
    };
}
