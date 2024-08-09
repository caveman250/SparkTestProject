#include "TestApplication.h"
#include "CameraSystem.h"
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

        m_World.RegisterSystemUpdateGroup<CameraSystem>();
        m_World.RegisterSystemUpdateGroup<TestSystem>();

        m_World.CreateSystem<CameraSystem>();
        m_World.CreateSystem<TestSystem>();

        m_World.Init();
    }

    void TestApplication::Update()
    {
        Application::Update();
        m_World.Update();
    }

    void TestApplication::Render()
    {
       m_World.Render();
    }
}
