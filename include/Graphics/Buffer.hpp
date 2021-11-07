/**
 *  Artemis game
 *  Copyright (C) 2020 Armands Arseniuss Skolmeisters
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

#ifndef GRAPHICS_BUFFER_HPP
#define GRAPHICS_BUFFER_HPP

#include <string>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include <Common/Observer.hpp>

namespace Graphics {

    enum {
        CONST_BUFFER,
        DYNAMIC_BUFFER
    };

    class Buffer : public std::enable_shared_from_this<Buffer>, public Common::Observable {
    private:
        size_t _size;
        void* _data;
        size_t _itemSize;
        int _type;
        std::string _name;
    public:
        Buffer(std::vector<float>& data, int itemSize);

        size_t GetSize() const {
            return _size;
        }

        void* GetData() {
            return _data;
        }

        int GetType() {
            return _type;
        }

        const std::string& GetName() const {
            return _name;
        }

        void SetName(const std::string& name) {
            _name = name;
        }
    };
}

#endif /* !GRAPHICS_BUFFER_HPP */
