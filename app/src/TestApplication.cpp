#include "TestApplication.h"
#include "CameraSystem.h"
#include "TestSystem.h"
#include "UITestSystem.h"

namespace app
{
    TestApplication* TestApplication::GetTestApplication()
    {
        return static_cast<TestApplication*>(Get());
    }

    void TestApplication::CreateInitialSingletonComponents()
    {
        Application::CreateInitialSingletonComponents();

        m_World.AddSingletonComponent<camera::ActiveCameraComponent>();
    }

    void TestApplication::CreateInitialSystems()
    {
        Application::CreateInitialSystems();

        m_World.CreateAppSystem<CameraSystem>({}, {});
        m_World.CreateAppSystem<TestSystem>({}, {});
        m_World.CreateAppSystem<UITestSystem>({}, {});
    }
}
