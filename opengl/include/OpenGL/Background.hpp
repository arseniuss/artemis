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

#ifndef OPENGL_BACKGROUND_HPP
#define OPENGL_BACKGROUND_HPP

#include <memory>

#include <Graphics/Color.hpp>

namespace Graphics {
    class Scene;
}

namespace OpenGL {

    class Background {
    private:
        Graphics::Color _clearColor;

        void clearColor(Graphics::Color color);
        void clear();
    public:
        Background();


        void Render(std::shared_ptr<Graphics::Scene> scene);
    };
}

#endif /* !OPENGL_BACKGROUND_HPP */
