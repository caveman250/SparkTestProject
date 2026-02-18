#include "FirstPersonCameraSystem.h"

#include <engine/math/math.h>

#include "../components/FirstPersonCameraComponent.h"
#include "engine/Application.h"
#include "engine/camera/ActiveCameraComponent.h"
#include "engine/ecs/components/TransformComponent.h"
#include "engine/ecs/util/SystemUtil.h"
#include "engine/input/InputComponent.h"
#include "engine/input/InputUtil.h"
#include "engine/input/MouseButton.h"

namespace app
{
    ecs::SystemDeclaration FirstPersonCameraSystem::GetSystemDeclaration()
    {
        return ecs::SystemDeclaration("First Person Camera System")
            .WithComponent<FirstPersonCameraComponent>()
            .WithComponent<ecs::components::TransformComponent>()
            .WithSingletonComponent<camera::ActiveCameraComponent>()
            .WithSingletonComponent<input::InputComponent>();
    }

    void FirstPersonCameraSystem::OnUpdate(const ecs::QueryResults& results)
    {
        ecs::ForEachArcheType(results, ecs::UpdateMode::MultiThreaded, false, [](const ecs::SystemUpdateData& updateData)
        {
            const auto& entities = updateData.GetEntities();
            auto* activeCamera = updateData.GetSingletonComponent<camera::ActiveCameraComponent>();
            auto* input = updateData.GetSingletonComponent<input::InputComponent>();
            auto* cameras = updateData.GetComponentArray<FirstPersonCameraComponent>();
            auto* transforms = updateData.GetComponentArray<ecs::components::TransformComponent>();

            if (entities.empty())
            {
                return;
            }

            const auto app = Application::Get();
            SPARK_ASSERT(entities.size() == 1, "Multiple cameras not supported");

            const auto dx = static_cast<float>(activeCamera->lastMouseX - input->mouseX);
            const auto dy = static_cast<float>(activeCamera->lastMouseY - input->mouseY);
            activeCamera->lastMouseX = input->mouseX;
            activeCamera->lastMouseY = input->mouseY;

            for (size_t i = 0; i < entities.size(); ++i)
            {
                const auto& entity = entities[i];
                auto& camera = cameras[i];
                auto& transform = transforms[i];
                input::InputUtil::ProcessMouseEvents(entity, input, [&camera](const input::MouseEvent& mouseEvent)
                {
                    if (mouseEvent.button == input::MouseButton::Left)
                    {
                        if (mouseEvent.state == input::KeyState::Down)
                        {
                            camera.mouseDown = true;
                        }
                        else
                        {
                            camera.mouseDown = false;
                        }

                        return true;
                    }

                    return false;
                });

                if (camera.mouseDown)
                {
                    const auto dt = app->GetDeltaTime();
                    transform.rot = transform.rot + math::Vec3(dy * dt, dx * dt, 0.0f);
                }

                math::Vec3 forward(cos(transform.rot.x) * sin(transform.rot.y),
                             sin(transform.rot.x),
                             cos(transform.rot.x) * cos(transform.rot.y));

                math::Vec3 right = math::Vec3(
                    sin(transform.rot.y - 3.14f / 2.0f),
                    0,
                    cos(transform.rot.y - 3.14f / 2.0f));

                math::Vec3 up = math::Cross(right, forward);

                // Movement
                if (input->keyStates.at(static_cast<int>(input::Key::W)) == input::KeyState::Down)
                {
                    transform.pos += forward * 5.f * Application::Get()->GetDeltaTime();
                }

                if (input->keyStates.at(static_cast<int>(input::Key::S)) == input::KeyState::Down)
                {
                    transform.pos -= forward * 5.f * Application::Get()->GetDeltaTime();
                }

                if (input->keyStates.at(static_cast<int>(input::Key::A)) == input::KeyState::Down)
                {
                    transform.pos -= right * 5.f * Application::Get()->GetDeltaTime();
                }

                if (input->keyStates.at(static_cast<int>(input::Key::D)) == input::KeyState::Down)
                {
                    transform.pos += right * 5.f * Application::Get()->GetDeltaTime();
                }

                activeCamera->pos = transform.pos;
                activeCamera->rot = transform.rot;
                activeCamera->view = math::LookAt(
                        transform.pos,
                        transform.pos + forward,
                        up);

                const auto gameViewport = app->GetGameViewportSize();
                activeCamera->proj = math::Perspective(math::Radians(45.f),
                    static_cast<float>(gameViewport.x) / static_cast<float>(gameViewport.y),
                    .1f,
                    100.f);
            }
        });
    }
}
