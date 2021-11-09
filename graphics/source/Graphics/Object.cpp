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

#include <glm/gtx/matrix_decompose.hpp>

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
    _quaternion = {1, 0, 0, 0};
    _scale = {1, 1, 1};
    _up = {0, 1, 0};
    _visible = true;
    _isImmediateObject = true;
    _isInstancedMesh = false;
    _matrixAutoUpdate = true;
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

void Object::LookAt(glm::vec3 target) {
    glm::mat4 m1;

    UpdateWorldMatrix(true, false);

    _position = _matrixWorld[3]; // decompose 3rd column

    if (Graphics::Camera::IsCameraHash(_hash) || Graphics::Light::IsLightHash(_hash)) {
        m1 = glm::lookAt(_position, target, _up);
    } else {
        m1 = glm::lookAt(target, _position, _up);
    }

    _quaternion = glm::quat_cast(m1);

    if (auto p = _parent.lock()) {
        m1 = Maths::ExtractRotation(p->GetMatrixWorld());
        glm::quat q1 = glm::quat_cast(m1);
        _quaternion = q1 * _quaternion;
    }
}

void Object::UpdateMatrix() {
    glm::mat4 rotation = (glm::mat4)_quaternion;
    glm::mat4 translation = glm::translate(_translation, _position);
    translation = glm::scale(translation, _scale);

    _matrix = translation * rotation;
}

void Object::UpdateWorldMatrix(bool updateParents, bool updateChildren) {
    if (updateParents) {
        if (auto p = _parent.lock()) {
            p->UpdateWorldMatrix(true, false);
        }
    }

    if (_matrixAutoUpdate) UpdateMatrix();
    if (auto p = _parent.lock()) {
        _matrixWorld = p->GetMatrixWorld() * _matrix;
    } else {
        _matrixWorld = _matrix;
    }

    if (updateChildren) {
        for (auto child : _children) {
            child->UpdateWorldMatrix(false, true);
        }
    }
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