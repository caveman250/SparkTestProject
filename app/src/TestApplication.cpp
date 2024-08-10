#include "TestApplication.h"
#include "CameraSystem.h"
#include "TestSystem.h"

namespace app
{
    TestApplication* TestApplication::GetTestApplication()
    {
        return static_cast<TestApplication*>(Get());
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

    void TestApplication::CreateInitialSystemUpdateGroups()
    {
        Application::CreateInitialSystemUpdateGroups();

        m_World.RegisterSystemUpdateGroup<CameraSystem>();
        m_World.RegisterSystemUpdateGroup<TestSystem>();
    }

    void TestApplication::CreateInitialSystems()
    {
        Application::CreateInitialSystems();

        m_World.CreateSystem<CameraSystem>();
        m_World.CreateSystem<TestSystem>();
    }
}
