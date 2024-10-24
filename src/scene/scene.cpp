#include "scene.hpp"
#include "entity.hpp"

#include "util/input_manager.hpp"

#include "glm/gtx/string_cast.hpp"

using namespace engine;

Entity Scene::create_entity(const std::string &id)
{
    Entity e = Entity(m_registry.create(), this);

    e.add<IDComponent>(id);
    e.add<TransformComponent>();

    return e;
}

void Scene::step(float dt)
{
    // Input system
    auto input_view = m_registry.view<InputComponent, TransformComponent>();

    for (auto entity : input_view)
    {
        auto &controller = input_view.get<InputComponent>(entity);
        auto &transform  = input_view.get<TransformComponent>(entity);

        auto  key_states = InputManager::instance().key_states();

        for (const auto &axis_input : controller.axis_inputs())
        {
            for (const auto &bind : axis_input.second)
            {
                if (key_states.contains(bind.first))
                {
                    if (key_states[bind.first] != GLFW_RELEASE)
                    {
                        auto it = controller.axis_callbacks().find(axis_input.first);

                        if (it != controller.axis_callbacks().end())
                        {
                            switch (axis_input.first)
                            {
                            case Axis::MoveForward:
                            case Axis::MoveRight:
                                it->second(bind.second * dt);
                                break;
                            case Axis::Turn:
                            case Axis::LookUp:
                                break;
                            default:
                                break;
                            }
                        }
                    }
                }
            }
        }

        float cursor_x = InputManager::instance().cursor_offset_x();
        float cursor_y = InputManager::instance().cursor_offset_y();

        if (controller.axis_inputs().contains(Axis::Turn))
        {
            if (controller.axis_callbacks().contains(Axis::Turn))
            {
                for (const auto &bind : controller.axis_inputs().at(Axis::Turn))
                {
                    switch (bind.first)
                    {
                    case MouseX:
                        controller.axis_callbacks().at(Axis::Turn)(cursor_x * 0.05f);
                        break;
                    case MouseY:
                        controller.axis_callbacks().at(Axis::Turn)(cursor_y * 0.05f);
                        break;
                    default:
                        break;
                    }
                }
            }
        }

        if (controller.axis_inputs().contains(Axis::LookUp))
        {
            if (controller.axis_callbacks().contains(Axis::LookUp))
            {
                for (const auto &bind : controller.axis_inputs().at(Axis::LookUp))
                {
                    switch (bind.first)
                    {
                    case MouseX:
                        controller.axis_callbacks().at(Axis::LookUp)(cursor_x * 0.05f);
                        break;
                    case MouseY:
                        controller.axis_callbacks().at(Axis::LookUp)(cursor_y * 0.05f);
                        break;
                    default:
                        break;
                    }
                }
            }
        }

        transform.translation = controller.position();
    }

    // Camera system
    auto camera_view = m_registry.view<CameraComponent, TransformComponent>();

    for (auto entity : camera_view)
    {
        auto &camera    = camera_view.get<CameraComponent>(entity);
        auto &transform = camera_view.get<TransformComponent>(entity);

        if (auto *controller = m_registry.try_get<InputComponent>(entity))
        {
            camera.set_yaw(controller->yaw());
            camera.set_pitch(controller->pitch());
        }

        camera.set_position(transform.translation);
    }
}

void Scene::render()
{
    CameraComponent *primary_camera = nullptr;

    // Find the scene's primary camera
    auto camera_view = m_registry.view<CameraComponent, TransformComponent>();

    for (auto entity : camera_view)
    {
        auto &camera    = camera_view.get<CameraComponent>(entity);
        auto &transform = camera_view.get<TransformComponent>(entity);

        if (camera.is_primary)
        {
            primary_camera = &camera;
        }
    }

    // Render
    auto render_view = m_registry.view<ModelComponent, TransformComponent>();

    for (auto entity : render_view)
    {
        auto model     = render_view.get<ModelComponent>(entity);
        auto transform = render_view.get<TransformComponent>(entity);

        if (primary_camera)
        {
            model.draw(primary_camera->projection_matrix(), primary_camera->view_matrix(), transform.transform());
        }
    }
}

void Scene::on_viewport_resize(uint16_t width, uint16_t height)
{
    auto camera_view = m_registry.view<CameraComponent>();

    for (auto entity : camera_view)
    {
        CameraComponent &camera = camera_view.get<CameraComponent>(entity);

        if (!camera.lock_aspect_ratio)
        {
            camera.set_aspect_ratio(width, height);
        }
    }
}

void Scene::on_debug()
{
    if (ImGui::TreeNode("Scene"))
    {
        if (ImGui::TreeNode("Entities"))
        {
            auto view = m_registry.view<IDComponent, TransformComponent>();

            for (auto entity : view)
            {
                auto &id        = view.get<IDComponent>(entity);
                auto &transform = view.get<TransformComponent>(entity);

                if (ImGui::TreeNode(id.id.c_str()))
                {
                    if (ImGui::TreeNode("Transform"))
                    {
                        ImGui::DragFloat("Translation X", &transform.translation.x, 0.1f);
                        ImGui::DragFloat("Translation Y", &transform.translation.y, 0.1f);
                        ImGui::DragFloat("Translation Z", &transform.translation.z, 0.1f);
                        ImGui::DragFloat("Rotation X", &transform.rotation.x, 0.1f);
                        ImGui::DragFloat("Rotation Y", &transform.rotation.y, 0.1f);
                        ImGui::DragFloat("Rotation Z", &transform.rotation.z, 0.1f);
                        ImGui::DragFloat("Scale X", &transform.scale.x, 0.1f);
                        ImGui::DragFloat("Scale Y", &transform.scale.y, 0.1f);
                        ImGui::DragFloat("Scale Z", &transform.scale.z, 0.1f);
                        ImGui::TreePop();
                    }

                    if (auto *model = m_registry.try_get<ModelComponent>(entity))
                    {
                        if (ImGui::TreeNode("Model"))
                        {
                            if (ImGui::TreeNode("Textures"))
                            {
                                ImVec2 size = ImVec2(96, 96);

                                ImGui::Spacing();
                                for (auto &texture : model->model.m_textures)
                                {
                                    ImGui::BeginGroup();

                                    float image_width = size.x;
                                    float text_width  = ImGui::CalcTextSize(texture.type.c_str()).x;

                                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ((image_width - text_width) / 2));

                                    ImGui::Text("%s", texture.type.c_str());
                                    ImGui::Image((void *)(intptr_t)texture.id, size);

                                    ImGui::EndGroup();
                                    ImGui::SameLine(0.0f, 15.0f);
                                }
                                ImGui::Spacing();

                                ImGui::TreePop();
                            }

                            ImGui::TreePop();
                        }
                    }

                    ImGui::TreePop();
                }
            }

            ImGui::TreePop();
        }

        ImGui::TreePop();
    }
}