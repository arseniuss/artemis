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

#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Common/Debug.hpp>
#include <Graphics/Camera.hpp>
#include <Graphics/Maths.hpp>
#include <Graphics/Object.hpp>
#include <Graphics/Objects/Light.hpp>

using namespace Graphics;

static int objectCounter = 0;

Object::Object() {
    _id = ++objectCounter;
    _name = "unnamed object";

    _position = {0, 0, 0};
    _translation = glm::mat4(1.0f);
    _orientation = glm::quat_identity<float, glm::defaultp>();
    _scale = {1, 1, 1};

    _matrix = glm::mat4(1.0f);

    _matrixAutoUpdate = true;

    _visible = true;
    _isImmediateObject = true;
    _isInstancedMesh = false;
}

Object::~Object() {
    DEBUG("Object " << _name << " died.");
}

int Object::GetId() const {
    return _id;
}

size_t Object::GetHash() const {
    return _hash;
}

const std::string& Object::GetName() const {
    return _name;
}

glm::vec3 Object::GetPosition() const {
    return _position;
}

void Object::SetPosition(glm::vec3 position) {
    _position = position;
    UpdateMatrix();
}

glm::quat Object::GetOrientation() const {
    return _orientation;
}

void Object::SetOrientation(glm::quat orientation) {
    _orientation = orientation;
    UpdateMatrix();
}

std::vector<std::shared_ptr<Object> >& Object::GetChildren() {
    return _children;
}

Object& Object::Add(std::shared_ptr<Object> obj) {
    if (!obj) {
        DEBUG("Cannot add null object");
    } else if (obj.get() == this) {
        DEBUG("Cannot add object to itself");
    } else {
        if (auto parent = obj->_parent.lock()) {
            parent->Remove(obj);
        }
        obj->_parent = weak_from_this();
        _children.push_back(obj);
    }

    return *this;
}

Object& Object::Remove(std::shared_ptr<Object> obj) {
    _children.erase(
            std::remove_if(_children.begin(), _children.end(), [obj](const std::shared_ptr<Object>& o) {
                return o == obj;
            }), _children.end());

    obj->_parent.reset();

    return *this;
}

bool Object::IsVisible() const {
    return _visible;
}

bool Object::IsFrustumCulled() const {
    return false;
}

bool Object::IsImmediateObject() const {
    return _isImmediateObject;
}

bool Object::IsInstancedMesh() const {
    return _isInstancedMesh;
}

void Object::UpdateMatrix() {
    glm::mat4 rotation = (glm::mat4)_orientation;
    glm::mat4 translation = glm::translate(_translation, _position);
    translation = glm::scale(translation, _scale);

    _matrix = translation * rotation;
}

glm::mat4 Object::GetMatrix() const {
    return _matrix;
}

void Graphics::Traverse(std::shared_ptr<Object>& o, std::function<void(std::shared_ptr<Object>&) > func) {
    func(o);

    if (o.get())
        for (auto c : o->GetChildren()) {
            Graphics::Traverse(c, func);
        }
}

void Graphics::TraverseVisible(std::shared_ptr<Object>& o, std::function<void(std::shared_ptr<Object>&) > func) {
    if (o->IsVisible()) {
        func(o);

        for (auto c : o->GetChildren()) {
            Graphics::TraverseVisible(c, func);
        }
    }
}
