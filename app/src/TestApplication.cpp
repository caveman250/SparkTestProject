#include "TestApplication.h"
#include "FirstPersonCameraSystem.h"
#include "TestSystem.h"
#include "UITestSystem.h"

namespace app
{
    TestApplication* TestApplication::GetTestApplication()
    {
        return static_cast<TestApplication*>(Get());
    }

    void TestApplication::CreateInitialSystems()
    {
        Application::CreateInitialSystems();

        m_World.CreateAppSystem<FirstPersonCameraSystem>({}, {}, {});
        m_World.CreateAppSystem<TestSystem>({}, {}, {});
        m_World.CreateAppSystem<UITestSystem>({}, {}, {});
    }
}
