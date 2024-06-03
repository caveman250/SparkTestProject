#include "CameraSystem.h"

#include "engine/Application.h"
#include "engine/input/InputComponent.h"
#include "engine/input/InputUtil.h"
#include "platform/IWindow.h"

namespace app
{
    DEFINE_SPARK_SYSTEM(CameraSystem)

    void CameraSystem::OnUpdate(const std::vector<se::ecs::EntityId>& entities, camera::ActiveCameraComponent* camera, input::InputComponent* input)
    {
        //Orientation
        auto app = Application::Get();
        auto window = app->GetPrimaryWindow();
        int xDelta = float(window->GetWidth() / 2.f - input->mouseX);
        int yDelta = float(window->GetHeight() / 2.f - input->mouseY);
        debug::Log::Info("{}", yDelta);
        camera->horizontalAngle += 1.f * app->GetDeltaTime() * xDelta;
        camera->verticalAngle += 1.f * app->GetDeltaTime() * yDelta;

        math::Vec3 forward(cos(camera->verticalAngle) * sin(camera->horizontalAngle),
                     sin(camera->verticalAngle),
                     cos(camera->verticalAngle) * cos(camera->horizontalAngle));

        math::Vec3 right = math::Vec3(
            sin(camera->horizontalAngle - 3.14f / 2.0f),
            0,
            cos(camera->horizontalAngle - 3.14f / 2.0f));

        math::Vec3 up = math::Cross(right, forward);

        // Movement
        if (input->keyStates.at(input::Key::W) == input::KeyState::Down)
        {
            camera->pos += forward * 5.f * Application::Get()->GetDeltaTime();
        }

        if (input->keyStates.at(input::Key::S) == input::KeyState::Down)
        {
            camera->pos -= forward * 5.f * Application::Get()->GetDeltaTime();
        }

        if (input->keyStates.at(input::Key::A) == input::KeyState::Down)
        {
            camera->pos -= right * 5.f * Application::Get()->GetDeltaTime();
        }

        if (input->keyStates.at(input::Key::D) == input::KeyState::Down)
        {
            camera->pos += right * 5.f * Application::Get()->GetDeltaTime();
        }


        camera->view = math::LookAt(
            camera->pos,
            camera->pos + forward,
            up);
    }
}
