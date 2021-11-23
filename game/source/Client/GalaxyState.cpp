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

#include <random>

#include <Common/Debug.hpp>
#include <Galaxy/SphereGalaxyGenerator.hpp>
#include <Graphics/Buffer.hpp>
#include <Graphics/Cameras/PerspectiveCamera.hpp>
#include <Graphics/Geometry.hpp>
#include <Graphics/Materials/PointsMaterial.hpp>
#include <Graphics/Objects/Points.hpp>

#include "Client/GalaxyState.hpp"
#include "Client/Application.hpp"

using namespace Client;

GalaxyState::GalaxyState(Application* app) : State(app, "Galaxy state") {
    auto graph = app->GetGraphics();

    Utility::Random rand(0);
    auto gen = new Galaxy::SphereGalaxyGenerator(10000);
    std::vector<Galaxy::Star>& stars = gen->Generate(rand);

    auto geo = std::make_shared<Graphics::Geometry>();
    std::vector<float> positions;
    std::vector<float> colors;

    glm::vec3 maxes(0);
    glm::vec3 mines(0);
    
    for (size_t i = 0; i < stars.size(); i++) {
        auto& star = stars[i];

        auto pos = star.position * 50.0f;
        
        positions.emplace_back(pos.x);
        positions.emplace_back(pos.y);
        positions.emplace_back(pos.z);
        
        if(maxes.x < star.position.x) maxes.x = star.position.x;
        if(maxes.y < star.position.y) maxes.y = star.position.y;
        if(maxes.z < star.position.z) maxes.z = star.position.z;
        
        if(mines.x > star.position.x) mines.x = star.position.x;
        if(mines.y > star.position.y) mines.y = star.position.y;
        if(mines.z > star.position.z) mines.z = star.position.z;
        

        colors.emplace_back(1.0f);
        colors.emplace_back(1.0f);
        colors.emplace_back(1.0f); // TODO: convert
    }
    
    DEBUG("Max is " << maxes << " Min is " << mines);

    geo->AddBuffer("position", std::make_shared<Graphics::Buffer<float>>(positions, 3));
    geo->AddBuffer("color", std::make_shared<Graphics::Buffer<float>>(colors, 3));

    geo->Compute();

    auto mat = std::make_shared<Graphics::PointsMaterial>(1);

    auto system = std::make_shared<Graphics::Points>(geo, mat);

    _scene = std::make_shared<Graphics::Scene>();

    auto windowSize = graph->GetSize();
    _scene->Add(system->shared_from_this());
    _camera = std::make_shared<Graphics::PerspectiveCamera>(27, windowSize.x / windowSize.y, 1, 10000);
    _camera->LookAt({0, 0, 0});
    _camera->SetPosition({0, 0, 1000});
    _camera->UpdateWorldMatrix(true, true);
}

void GalaxyState::BuildUI(Gui::LayoutBuilder& builder) {

}

bool GalaxyState::HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                _app.PopState();
                return true;
        }
    }

    return State::HandleEvent(event);
}

void GalaxyState::Render(Graphics::Renderer& renderer) {
    Utility::Random rand(0);
    
    _camera->LookAt({0, 0, rand.next()});
    _camera->UpdateMatrix();
    
    renderer.Render(_scene, _camera);
}

