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

#include <Galaxy/ClusterGalaxyGenerator.hpp>
#include <Graphics/Geometry.hpp>
#include <Graphics/Materials/PointsMaterial.hpp>
#include <Graphics/Objects/Points.hpp>

#include "Client/GalaxyState.hpp"

using namespace Client;

GalaxyState::GalaxyState(Application* app) : State(app, "Galaxy state") {
    auto graph = app->GetGraphics();

    auto gen = new Galaxy::ClusterGalaxyGenerator();
    std::vector<Galaxy::Star>& stars = gen->Generate();

    auto geo = new Graphics::Geometry();
    std::vector<float> positions;
    std::vector<float> colors;

    positions.reserve(stars.size() * 3);
    colors.reserve(stars.size() * 3);

    for (size_t i = 0; i < stars.size(); i++) {
        auto& star = stars[i];

        positions[i] = star.position.x;
        positions[i + 1] = star.position.y;
        positions[i + 2] = star.position.z;

        colors[i] = star.color.r;
        colors[i + 1] = star.color.g;
        colors[i + 2] = star.color.b;
    }

    geo->AddBuffer("position", new Graphics::Buffer(positions, 3));
    geo->AddBuffer("color", new Graphics::Buffer(colors, 3));


    auto material = new Graphics::PointsMaterial(15);

    auto system =  std::make_shared<Graphics::Points>(geo, material);

    _scene = new Graphics::Scene();

    _scene->Add(system->shared_from_this());
    _camera = new Graphics::Camera();
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
    renderer.Render(*_scene, *_camera);
}

