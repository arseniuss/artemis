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

#ifndef GRAPHICS_OBJECT_HPP
#define GRAPHICS_OBJECT_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <memory>
#include <vector>
#include <functional>

namespace Graphics {

    class Object : public std::enable_shared_from_this<Object> {
    protected:
        int _id;
        size_t _hash;
        std::string _name;

        std::weak_ptr<Object> _parent;
        std::vector<std::shared_ptr<Object>> _children;

        glm::mat4x4 _matrix;
        glm::mat4x4 _matrixWorld;

        glm::vec3 _position;
        glm::mat4 _rotation;
        glm::vec3 _scale;
        glm::quat _quat;
        bool _visible;
    public: 
        Object();

        int GetId() const;
        size_t GetHash() const;
        const std::string& GetName() const;
        glm::mat4x4 GetMatrixWorld() const;

        std::vector<std::shared_ptr<Object>>&GetChildren();

        Object& Add(std::shared_ptr<Object> obj);
        Object& Remove(std::shared_ptr<Object> obj);
        
        void UpdateMatrix();
        
        bool IsVisible() const;
        bool IsFrustumCulled() const;
    };
    
    void Traverse(std::shared_ptr<Object>& o, std::function<void(std::shared_ptr<Object>&)> func);
    void TraverseVisible(std::shared_ptr<Object>& o, std::function<void(std::shared_ptr<Object>&)> func);
}

#endif /* !GRAPHICS_OBJECT_HPP */
