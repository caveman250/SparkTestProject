

#include <platform/PlatformRunLoop.h>

#include "spark.h"
#include "TestApplication.h"
#include "engine/Application.h"

int main(int, char*[])
{
    se::Application::CreateInstance<app::TestApplication>();
    auto runLoop = PlatformRunLoop::CreatePlatformRunloop();
    runLoop->Run();
    runLoop->Shutdown();
}
