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
#include <Graphics/Geometries/BufferGeometry.hpp>
#include <Graphics/Materials/MeshMaterial.hpp>
#include <Graphics/Objects/Mesh.hpp>

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

const float color_buffer_data[] = {
    0.583f, 0.771f, 0.014f,
    0.609f, 0.115f, 0.436f,
    0.327f, 0.483f, 0.844f,
    0.822f, 0.569f, 0.201f,
    0.435f, 0.602f, 0.223f,
    0.310f, 0.747f, 0.185f,
    0.597f, 0.770f, 0.761f,
    0.559f, 0.436f, 0.730f,
    0.359f, 0.583f, 0.152f,
    0.483f, 0.596f, 0.789f,
    0.559f, 0.861f, 0.639f,
    0.195f, 0.548f, 0.859f,
    0.014f, 0.184f, 0.576f,
    0.771f, 0.328f, 0.970f,
    0.406f, 0.615f, 0.116f,
    0.676f, 0.977f, 0.133f,
    0.971f, 0.572f, 0.833f,
    0.140f, 0.616f, 0.489f,
    0.997f, 0.513f, 0.064f,
    0.945f, 0.719f, 0.592f,
    0.543f, 0.021f, 0.978f,
    0.279f, 0.317f, 0.505f,
    0.167f, 0.620f, 0.077f,
    0.347f, 0.857f, 0.137f,
    0.055f, 0.953f, 0.042f,
    0.714f, 0.505f, 0.345f,
    0.783f, 0.290f, 0.734f,
    0.722f, 0.645f, 0.174f,
    0.302f, 0.455f, 0.848f,
    0.225f, 0.587f, 0.040f,
    0.517f, 0.713f, 0.338f,
    0.053f, 0.959f, 0.120f,
    0.393f, 0.621f, 0.362f,
    0.673f, 0.211f, 0.457f,
    0.820f, 0.883f, 0.371f,
    0.982f, 0.099f, 0.879f
};

class ColoredCube : public Test {
private:
    std::shared_ptr<Graphics::BufferGeometry> _geometry;
    std::shared_ptr<Graphics::MeshMaterial> _material;
    std::shared_ptr<Graphics::Mesh> _object;
public:

    ColoredCube() : Test::Test("Colored cube") {

    }

    void Init(std::shared_ptr<Graphics::Context> context) override {
        Test::Init(context);

        _geometry = std::make_shared<Graphics::BufferGeometry>();
        _material = std::make_shared<Graphics::MeshMaterial>();
        _object = std::make_shared<Graphics::Mesh>(_geometry, _material);
        
        auto posBuffer = std::make_shared<Graphics::Buffer<float>>(vertex_buffer_data, sizeof(vertex_buffer_data), 3);
        auto colBuffer = std::make_shared<Graphics::Buffer<float>>(color_buffer_data, sizeof(color_buffer_data), 3);
        
        _geometry->SetAttribute("position", posBuffer);
        _geometry->SetAttribute("color", colBuffer);
      
        _scene->Add(_object);
    }

    void Deinit() override {  
        _geometry.reset();
        _material.reset();
        _object.reset();
        Test::Deinit();
    }
};

void ColoredCubeConstructor() __attribute__ ((constructor));

void ColoredCubeConstructor() {
    TestingFramework::Tests.emplace_back(std::make_shared<ColoredCube>());
}

