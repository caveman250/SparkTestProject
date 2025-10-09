#include "TestApplication.h"
#include "generated/Classes.generated.h"
#include "generated/Systems.generated.h"

namespace app
{
    TestApplication* TestApplication::GetTestApplication()
    {
        return static_cast<TestApplication*>(Get());
    }

    void TestApplication::Init()
    {
        Application::Init();
        se::app_InitClassReflection();
        se::app_InitSystems(&m_World);
    }
}
