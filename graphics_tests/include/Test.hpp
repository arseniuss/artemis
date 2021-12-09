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

#ifndef TEST_HPP
#define TEST_HPP

#include <memory>
#include <string>
#include <vector>

#include <SDL2/SDL_events.h>

#include <Ui/FreeMovementHandler.hpp>
#include <Graphics/Camera.hpp>
#include <Graphics/Cameras/PerspectiveCamera.hpp>
#include <Graphics/Scene.hpp>
#include <Graphics/Context.hpp>
#include <Graphics/Color.hpp>

namespace Graphics {
    class Camera;
    class Context;
    class Scene;
}

namespace TestingFramework {
    class Test;

    using TestVector = std::vector<std::shared_ptr<Test>>;

    class Test {
    protected:
        std::shared_ptr<Graphics::Camera> _camera;
        std::shared_ptr<Ui::FreeMovementHandler> _movement;
        std::shared_ptr<Graphics::Scene> _scene;

        std::shared_ptr<Graphics::Property> _background;

        std::string _name;
    public:
        Test(std::string name);

        const std::string& GetName() const;

        virtual void Init(std::shared_ptr<Graphics::Context> context) {
            glm::ivec2 size = context->GetSize();

            _camera = std::make_shared<Graphics::PerspectiveCamera>(glm::radians(45.0f), (float) size.x / (float) size.y,
                    0.1f, 100.0f);
            _camera->SetPosition({4, 3, 3});
            _camera->LookAt({0, 0, 0});

            _movement = std::make_shared<Ui::FreeMovementHandler>();
            _movement->Init(context);
            _movement->Attach(_camera);

            _scene = std::make_shared<Graphics::Scene>();

            _background = std::make_shared<Graphics::Color>(0.0f, 0.0f, 0.4f, 0.0f);
            _scene->SetBackground(_background);
        }

        virtual bool HandleEvent(const SDL_Event& event) {
            return _movement->HandleEvent(event);
        }

        virtual void Update(float deltaTime) {
            _movement->Update(deltaTime);
        }

        virtual void Deinit() {
            _scene.reset();
            _camera.reset();
            _background.reset();
        }

        virtual std::shared_ptr<Graphics::Scene> GetScene() {
            return _scene;
        }

        virtual std::shared_ptr<Graphics::Camera> GetCamera() {
            return _camera;
        }
    };

    extern TestVector Tests;
}

#endif /* !TEST_HPP */
