#include "CameraSystem.h"

#include "engine/Application.h"
#include "engine/input/InputComponent.h"
#include "engine/input/InputUtil.h"
#include "platform/IWindow.h"
#include "engine/input/MouseButton.h"

namespace app
{
    DEFINE_SPARK_SYSTEM(CameraSystem)

    void CameraSystem::OnUpdate(const std::vector<ecs::Id>&, camera::ActiveCameraComponent* camera, input::InputComponent* input)
    {
        //Orientation
        auto app = Application::Get();

        float dx = camera->lastMouseX - input->mouseX;
        float dy = camera->lastMouseY - input->mouseY;
        camera->lastMouseX = input->mouseX;
        camera->lastMouseY = input->mouseY;

        if (input->mouseButtonStates.at(input::MouseButton::Left) == input::KeyState::Down)
        {
            auto dt = app->GetDeltaTime();
            camera->rot = camera->rot + math::Vec3(dy * dt, dx * dt, 0.0f);

        }

        math::Vec3 forward(cos(camera->rot.x) * sin(camera->rot.y),
                     sin(camera->rot.x),
                     cos(camera->rot.x) * cos(camera->rot.y));

        math::Vec3 right = math::Vec3(
            sin(camera->rot.y - 3.14f / 2.0f),
            0,
            cos(camera->rot.y - 3.14f / 2.0f));

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
