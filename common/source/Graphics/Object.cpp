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

#include <Graphics/Object.hpp>
#include <Common/Debug.hpp>
#include <algorithm>

using namespace Graphics;

static int objectCounter = 0;

Object::Object() {
    _id = ++objectCounter;
    _name = "unnamed object";
    
    

    _scale = {1, 1, 1};
    _visible = true;
}

int Object::GetId() const {
    return _id;
}

const std::string& Object::GetName() const {
    return _name;
}

std::vector<std::shared_ptr<Object> >& Object::GetChildren() {
    return _children;
}

Object& Object::Add(std::shared_ptr<Object> obj) {
    if (!obj) {
        Common::Debug() << "Cannot add null object" << std::endl;
    } else if (obj.get() == this) {
        Common::Debug() << "Cannot add object to itself" << std::endl;
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

void Graphics::Traverse(std::shared_ptr<Object>& o, std::function<void(std::shared_ptr<Object>&) > func) {
    func(o);

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