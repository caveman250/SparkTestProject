#pragma once

#include "engine/Application.h"

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
    };
}
