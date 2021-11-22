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

#ifndef GRAPHICS_MATERIAL_HPP
#define GRAPHICS_MATERIAL_HPP

#include <memory>
#include <vector>

namespace Graphics {

    enum {
        DOUBLE_SIDED
    };

    class Material : public std::enable_shared_from_this<Material> {
    protected:
        size_t _hash;
        int _id;
        std::string& _typeName;
        std::string _name;
        int _version;
        int _sides;

        bool _isVisible;

        bool _transparent;
    public:
        static size_t Hash;
        
        Material();
        Material(const std::string& name, const std::string& typeName);

        const std::string& GetName() const;

        const std::string& GetTypeName() const {
            return _typeName;
        }

        bool IsVisible() const;

        float GetTransmission() const;
        bool IsTransparent() const;

        int GetVersion() const {
            return _version;
        }

        int GetSides() const {
            return _sides;
        }

        size_t GetHash() const {
            return _hash;
        }
    };
}

#endif /* !GRAPHICS_MATERIAL_HPP */
