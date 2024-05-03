#include "spark.h"
#include "TestApplication.h"
#include "engine/Application.h"

int main(int, char*[])
{
    se::Application::CreateInstance<app::TestApplication>();

    auto app = app::TestApplication::GetTestApplication();
    app->Init();
    app->Run();
    app->Shutdown();
}
