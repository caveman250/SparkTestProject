

#include <iostream>
#include <platform/PlatformRunLoop.h>

#include "TestApplication.h"
#include "engine/Application.h"

int main(int, char*[])
{
#if SPARK_ENABLE_PROFILING
    EASY_PROFILER_ENABLE;
#endif
    se::Application::CreateInstance<app::TestApplication>();
    auto runLoop = se::PlatformRunLoop::CreatePlatformRunloop();
    runLoop->Run();
    runLoop->Shutdown();
}
