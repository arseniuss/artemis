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

#include <SDL2/SDL_image.h>

#include <Common/Debug.hpp>
#include <Graphics/Texture.hpp>

using namespace Graphics;

size_t Texture::Hash = typeid (Texture).hash_code();

std::shared_ptr<Texture> Texture::Load(const std::string& filename) {
    SDL_Surface *image = IMG_Load(filename.c_str());

    if (!image) {
        DEBUG("Failed to load texture \"" << filename << "\": " << IMG_GetError());
        return {};
    }

    return std::make_shared<Texture>(image);
}

Texture::Texture() {
    _image = nullptr;
}

Texture::Texture(SDL_Surface* image) {
    _image = image;
}

Texture::~Texture() {
    SDL_FreeSurface(_image);
}

ssize_t Texture::GetWidth() const {
    if (_image)
        return _image->w;
    return 0;
}

ssize_t Texture::GetHeight() const {
    if (_image)
        return _image->h;
    return 0;
}

const void* Texture::GetData() const {
    if (_image)
        return _image->pixels;
    return nullptr;
}
