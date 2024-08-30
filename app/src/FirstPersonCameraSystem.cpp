#include "FirstPersonCameraSystem.h"

#include "engine/Application.h"
#include "engine/input/InputComponent.h"
#include "engine/input/InputUtil.h"
#include "engine/input/MouseButton.h"

namespace app
{
    DEFINE_SPARK_SYSTEM(FirstPersonCameraSystem)

    void FirstPersonCameraSystem::OnUpdate(const std::vector<ecs::Id>& entities, FirstPersonCameraComponent* camera, camera::ActiveCameraComponent* activeCamera, input::InputComponent* input)
    {
        if (entities.empty())
        {
            return;
        }

        auto app = Application::Get();
        SPARK_ASSERT(entities.size() == 1, "Multiple cameras not supported");

        auto dx = static_cast<float>(activeCamera->lastMouseX - input->mouseX);
        auto dy = static_cast<float>(activeCamera->lastMouseY - input->mouseY);
        activeCamera->lastMouseX = input->mouseX;
        activeCamera->lastMouseY = input->mouseY;

        input::InputUtil::ProcessMouseEvents(input, [&camera](const input::MouseEvent& mouseEvent)
        {
            if (mouseEvent.button == input::MouseButton::Left)
            {
                if (mouseEvent.state == input::KeyState::Down)
                {
                    camera->mouseDown = true;
                }
                else
                {
                    camera->mouseDown = false;
                }

                return true;
            }

            return false;
        });

        if (camera->mouseDown)
        {
            auto dt = app->GetDeltaTime();
            activeCamera->rot = activeCamera->rot + math::Vec3(dy * dt, dx * dt, 0.0f);
        }

        math::Vec3 forward(cos(activeCamera->rot.x) * sin(activeCamera->rot.y),
                     sin(activeCamera->rot.x),
                     cos(activeCamera->rot.x) * cos(activeCamera->rot.y));

        math::Vec3 right = math::Vec3(
            sin(activeCamera->rot.y - 3.14f / 2.0f),
            0,
            cos(activeCamera->rot.y - 3.14f / 2.0f));

        math::Vec3 up = math::Cross(right, forward);

        // Movement
        if (input->keyStates.at(input::Key::W) == input::KeyState::Down)
        {
            activeCamera->pos += forward * 5.f * Application::Get()->GetDeltaTime();
        }

        if (input->keyStates.at(input::Key::S) == input::KeyState::Down)
        {
            activeCamera->pos -= forward * 5.f * Application::Get()->GetDeltaTime();
        }

        if (input->keyStates.at(input::Key::A) == input::KeyState::Down)
        {
            activeCamera->pos -= right * 5.f * Application::Get()->GetDeltaTime();
        }

        if (input->keyStates.at(input::Key::D) == input::KeyState::Down)
        {
            activeCamera->pos += right * 5.f * Application::Get()->GetDeltaTime();
        }

        activeCamera->view = math::LookAt(
                activeCamera->pos,
                activeCamera->pos + forward,
                up);
    }
}
