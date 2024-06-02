#include <engine/asset/binary/Database.h>
#include <engine/asset/texture/Texture.h>
#include <engine/ecs/System.h>
#include "TestApplication.h"

#include "engine/math/Mat4.h"
#include "engine/render/Material.h"
#include "engine/render/Renderer.h"
#include "engine/render/VertexBuffer.h"
#include "engine/shader/ast/Types.h"
#include "platform/IWindow.h"
#include "engine/io/VFS.h"

#include "TestSystem.h"

namespace app
{
    TestApplication* TestApplication::GetTestApplication()
    {
        return static_cast<TestApplication*>(Get());
    }

    void TestApplication::Init()
    {
        using namespace se;

        Application::Init();

        m_World.RegisterSystemUpdateGroup<TestSystem>();
        m_World.CreateSystem<TestSystem>();

        m_World.Init();
    }

    void TestApplication::Update()
    {
        m_World.Update();
    }

    void TestApplication::Render()
    {
       m_World.Render();
    }
}
