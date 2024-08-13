#include "TestApplication.h"
#include "CameraSystem.h"
#include "RelationshipTestSystem.h"
#include "TestSystem.h"
#include "engine/render/components/PointLightComponent.h"

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

    void TestApplication::CreateInitialSystems()
    {
        Application::CreateInitialSystems();

        m_World.CreateAppSystem<CameraSystem>({});
        m_World.CreateAppSystem<TestSystem>({});
    }
}
