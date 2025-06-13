#include "TestApplication.h"
#include "FirstPersonCameraSystem.h"
#include "TestSystem.h"
#include "engine/ecs/components/TransformComponent.h"
#include "generated/Classes.generated.h"

namespace app
{
    TestApplication* TestApplication::GetTestApplication()
    {
        return static_cast<TestApplication*>(Get());
    }

    void TestApplication::Init()
    {
        Application::Init();
        app_InitClassReflection();
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
