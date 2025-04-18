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

        ecs::SystemCreationInfo firstPersonReg = ecs::SystemCreationInfo("FirstPersonCameraSystem");
        m_World.CreateAppSystem<FirstPersonCameraSystem>(firstPersonReg);

        ecs::SystemCreationInfo testReg = ecs::SystemCreationInfo("TestSystem");
        m_World.CreateAppSystem<TestSystem>(testReg);

        ecs::SystemCreationInfo uiTestReg = ecs::SystemCreationInfo("UITestSystem");
        m_World.CreateAppSystem<UITestSystem>(uiTestReg);
    }
}
