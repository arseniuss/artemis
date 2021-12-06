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

#ifndef GRAPHICS_TEXTURE_HPP
#define GRAPHICS_TEXTURE_HPP

#include <SDL2/SDL_image.h>

#include <Common/Observer.hpp>
#include <Graphics/Property.hpp>

namespace Graphics {

    class Texture : public Property, public Common::Observable {
    private:
        SDL_Surface *_image;
    public:
        static size_t Hash;

        Texture();
        Texture(SDL_Surface* image);
        ~Texture();
        
        ssize_t GetWidth() const;
        ssize_t GetHeight() const;
        const void *GetData() const;

        static std::shared_ptr<Texture> Load(const std::string& filename);
    };
}

#endif /* !GRAPHICS_TEXTURE_HPP */
