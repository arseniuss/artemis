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

#ifndef OPENGL_RENDERITEM_HPP
#define OPENGL_RENDERITEM_HPP

#include <memory>

#include <Graphics/Object.hpp>

namespace OpenGL {
    class RenderItem {
    public:
        
        /**
         * Update render item from updated object
         * @param o
         */
        void Update(std::shared_ptr<Graphics::Object>& o);
    };
}

#endif /* !OPENGL_RENDERITEM_HPP */
