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

#include <Graphics/Buffer.hpp>
#include <Graphics/Cameras/PerspectiveCamera.hpp>
#include <Graphics/Color.hpp>
#include <Graphics/Context.hpp>
#include <Graphics/Geometries/BufferGeometry.hpp>
#include <Graphics/Materials/MeshMaterial.hpp>
#include <Graphics/Objects/Mesh.hpp>
#include <Graphics/Scene.hpp>
#include <Graphics/Texture.hpp>

#include "Test.hpp"

using namespace TestingFramework;

const float vertex_buffer_data[] = {
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f
};

const float uv_buffer_data[] = {
    0.000059f, 1.0f - 0.000004f,
    0.000103f, 1.0f - 0.336048f,
    0.335973f, 1.0f - 0.335903f,
    1.000023f, 1.0f - 0.000013f,
    0.667979f, 1.0f - 0.335851f,
    0.999958f, 1.0f - 0.336064f,
    0.667979f, 1.0f - 0.335851f,
    0.336024f, 1.0f - 0.671877f,
    0.667969f, 1.0f - 0.671889f,
    1.000023f, 1.0f - 0.000013f,
    0.668104f, 1.0f - 0.000013f,
    0.667979f, 1.0f - 0.335851f,
    0.000059f, 1.0f - 0.000004f,
    0.335973f, 1.0f - 0.335903f,
    0.336098f, 1.0f - 0.000071f,
    0.667979f, 1.0f - 0.335851f,
    0.335973f, 1.0f - 0.335903f,
    0.336024f, 1.0f - 0.671877f,
    1.000004f, 1.0f - 0.671847f,
    0.999958f, 1.0f - 0.336064f,
    0.667979f, 1.0f - 0.335851f,
    0.668104f, 1.0f - 0.000013f,
    0.335973f, 1.0f - 0.335903f,
    0.667979f, 1.0f - 0.335851f,
    0.335973f, 1.0f - 0.335903f,
    0.668104f, 1.0f - 0.000013f,
    0.336098f, 1.0f - 0.000071f,
    0.000103f, 1.0f - 0.336048f,
    0.000004f, 1.0f - 0.671870f,
    0.336024f, 1.0f - 0.671877f,
    0.000103f, 1.0f - 0.336048f,
    0.336024f, 1.0f - 0.671877f,
    0.335973f, 1.0f - 0.335903f,
    0.667969f, 1.0f - 0.671889f,
    1.000004f, 1.0f - 0.671847f,
    0.667979f, 1.0f - 0.335851f
};

class RotateLookAtTest : public Test {
private:
    std::shared_ptr<Graphics::BufferGeometry> _geometry;
    std::shared_ptr<Graphics::MeshMaterial> _material;
    std::shared_ptr<Graphics::Mesh> _object;

    float _distance;
public:

    RotateLookAtTest() : Test::Test("Rotate lookat") {

    }

    void Init(std::shared_ptr<Graphics::Context> context) override {
        Test::Init(context);

        _geometry = std::make_shared<Graphics::BufferGeometry>();
        _material = std::make_shared<Graphics::MeshMaterial>();

        std::shared_ptr<Graphics::Texture> texture = Graphics::Texture::Load("data/uvtemplate.bmp");

        _material->SetTexture(texture);

        _object = std::make_shared<Graphics::Mesh>(_geometry, _material);

        auto posBuffer = std::make_shared<Graphics::Buffer<float>>(vertex_buffer_data, sizeof (vertex_buffer_data), 3);
        auto uvBuffer = std::make_shared<Graphics::Buffer<float>>(uv_buffer_data, sizeof (uv_buffer_data), 2);

        _geometry->SetAttribute("position", posBuffer);
        _geometry->SetAttribute("uv", uvBuffer);

        _scene->Add(_object);
        _object->SetPosition({0, 0, 0});
        _camera->SetPosition({0, 0, 4});
        _camera->LookAt({0, 0, 0});


        _distance = glm::distance(_camera->GetPosition(), _object->GetPosition());

        DEBUG("DISTANCE = " << _distance);
    }

    void Update(float deltaTime) override {
        Test::Update(deltaTime);


    }

    void Deinit() override {
        _geometry.reset();
        _material.reset();
        _object.reset();
        Test::Deinit();
    }
};

void RotateLookAtTestConstructor() __attribute__ ((constructor));

void RotateLookAtTestConstructor() {
    TestingFramework::Tests.emplace_back(std::make_shared<RotateLookAtTest>());
}

