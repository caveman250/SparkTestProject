#include "TestApplication.h"
#include "FirstPersonCameraSystem.h"
#include "TestSystem.h"

namespace app
{
    TestApplication* TestApplication::GetTestApplication()
    {
        return static_cast<TestApplication*>(Get());
    }

    void TestApplication::CreateInitialSystems()
    {
        Application::CreateInitialSystems();

        ecs::SystemDeclaration firstPersonReg = ecs::SystemDeclaration("FirstPersonCameraSystem")
            .WithComponent<FirstPersonCameraComponent>()
            .WithSingletonComponent<camera::ActiveCameraComponent>()
            .WithSingletonComponent<input::InputComponent>();
        m_World.CreateAppSystem<FirstPersonCameraSystem>(firstPersonReg);

        ecs::SystemDeclaration testReg = ecs::SystemDeclaration("TestSystem")
            .WithComponent<TransformComponent>();
        m_World.CreateAppSystem<TestSystem>(testReg);
    }
}
