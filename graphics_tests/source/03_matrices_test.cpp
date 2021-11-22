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

#include <Common/Debug.hpp>
#include <Graphics/Buffer.hpp>
#include <Graphics/Camera.hpp>
#include <Graphics/Cameras/PerspectiveCamera.hpp>
#include <Graphics/Color.hpp>
#include <Graphics/Context.hpp>
#include <Graphics/Materials/BasicMeshMaterial.hpp>
#include <Graphics/Materials/CustomMaterial.hpp>
#include <Graphics/Objects/Mesh.hpp>
#include <Graphics/Scene.hpp>

#include "Test.hpp"

using namespace TestingFramework;

class MatricesTest : public Test {
private:
    std::shared_ptr<Graphics::Camera> _camera;
    std::shared_ptr<Graphics::Scene> _scene;

    std::shared_ptr<Graphics::Property> _background;

    std::shared_ptr<Graphics::Geometry> _geometry;
    std::shared_ptr<Graphics::BasicMeshMaterial> _material;
    std::shared_ptr<Graphics::Mesh> _object;

public:

    MatricesTest() : Test::Test("Matrices test") {

    }

    void Init(std::shared_ptr<Graphics::Context> context) override {
        glm::ivec2 size = context->GetSize();

        _camera = std::make_shared<Graphics::PerspectiveCamera>(glm::radians(45.0f), (float) size.x / (float) size.y,
                0.1f, 100.0f);
        _camera->SetPosition({4, 3, 3});
        _camera->LookAt({4, 3, 3});

        _scene = std::make_shared<Graphics::Scene>();

        _background = std::make_shared<Graphics::Color>(0.0f, 0.0f, 0.4f, 0.0f);
        _scene->SetBackground(_background);

        _geometry = std::make_shared<Graphics::Geometry>();
        _material = std::make_shared<Graphics::BasicMeshMaterial>();
        _object = std::make_shared<Graphics::Mesh>(_geometry, _material);

        static const float position[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
        };

        auto positionBuffer = std::make_shared<Graphics::Buffer<float>>(position, sizeof(position), 3);

        _geometry->AddBuffer("position", positionBuffer);



        _material->SetColor({1, 0, 0});

        _scene->Add(_object);
    }

    std::shared_ptr<Graphics::Scene> GetScene() override {
        return _scene;
    }

    std::shared_ptr<Graphics::Camera> GetCamera() override {
        return _camera;
    }


};

void MatricesTestConstructor() __attribute__ ((constructor));

void MatricesTestConstructor() {
    TestingFramework::Tests.emplace_back(std::make_shared<MatricesTest>());
}
