/**
 *  Artemis game
 *  Copyright (C) 2021 Armands Arseniuss Skolmeisters
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this library.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <Graphics/Context.hpp>
#include <Graphics/Object.hpp>
#include <Ui/FreeMovementHandler.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace Ui;

FreeMovementHandler::FreeMovementHandler() {
    _speed = 0.01f;
    _sensitivity = 0.1f;
    _yaw = -90.0f;
    _pitch = 0.0f;
}

void FreeMovementHandler::Init(std::shared_ptr<Graphics::Context> context) {
    glm::ivec2 windowSize = context->GetSize();

    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_WarpMouseInWindow(context->GetWindow(), windowSize.x / 2, windowSize.y / 2);
}

void FreeMovementHandler::Deinit() {
    SDL_SetRelativeMouseMode(SDL_FALSE);
}

void FreeMovementHandler::Attach(std::shared_ptr<Graphics::Object> object) {
    _target = object;
}

bool FreeMovementHandler::HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_MOUSEMOTION) {
        if (_target.get()) {
            float xoffset = glm::radians(event.motion.xrel * _sensitivity);
            float yoffset = glm::radians(event.motion.yrel * _sensitivity);
            auto orientation = _target->GetOrientation();

            auto roll = glm::roll(orientation);

            orientation = glm::rotate(orientation, yoffset, glm::vec3(1, 0, 0));
            orientation = glm::rotate(orientation, xoffset, glm::vec3(0, 1, 0));

            // Note. Moveing mouse introduces weird roll error
            
            // Weird roll error fix
            auto eu2 = glm::eulerAngles(orientation);
            
            eu2.z = roll;

            orientation = glm::quat(eu2);

            _target->SetOrientation(orientation);
        }
    }

    return false;
}

void FreeMovementHandler::Update(float deltaTime) {
    if (_target.get()) {
        float speed = _speed * deltaTime;
        glm::vec3 position = _target->GetPosition();
        bool changed = false;
        auto* state = SDL_GetKeyboardState(nullptr);

        auto orientation = glm::normalize(_target->GetOrientation());
        auto forward = glm::vec3(glm::toMat4(orientation) * glm::vec4(0, 0, -1, 0));
        auto right = glm::vec3(glm::toMat4(orientation) * glm::vec4(1, 0, 0, 0));

        if (state[SDL_SCANCODE_UP]) {
            position += speed * forward;
            changed = true;
        }

        if (state[SDL_SCANCODE_DOWN]) {
            position -= speed * forward;
            changed = true;
        }

        if (state[SDL_SCANCODE_RIGHT]) {
            position += speed * right;
            changed = true;
        }

        if (state[SDL_SCANCODE_LEFT]) {
            position -= speed * right;
            changed = true;
        }

        if (changed) {
            _target->SetPosition(position);
        }
    }
}
