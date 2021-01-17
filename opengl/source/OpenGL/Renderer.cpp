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

#include <OpenGL/Renderer.hpp>
#include <OpenGL/Context.hpp>

using namespace OpenGL;

Renderer::Renderer(OpenGL::Context& ctx) : _context(ctx) {

}

Renderer::~Renderer() {

}

void Renderer::Begin() {
    auto win = _context.GetWindow();


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(Graphics::Scene& scene, Graphics::Camera& camera) {
    _projMatrix = camera.GetProjectionMatrix() * camera.GetMatrixWorldInverse();
    _frustum.Update(_projMatrix);
}

void Renderer::Finish() {
    auto win = _context.GetWindow();

    _context.DrawLayout();

    SDL_GL_SwapWindow(win);
}

