

#include <platform/PlatformRunLoop.h>

#include "TestApplication.h"
#include "engine/Application.h"

int main(int, char*[])
{
    se::Application::CreateInstance<app::TestApplication>();
    auto runLoop = se::PlatformRunLoop::CreatePlatformRunloop();
    runLoop->Run();
    runLoop->Shutdown();
}
