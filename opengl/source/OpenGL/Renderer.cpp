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

#include <Common.hpp>
#include <Common/Dictionary.hpp>
#include <Graphics/Common.hpp>
#include <Graphics/Materials/BasicMeshMaterial.hpp>
#include <Graphics/Materials/PointsMaterial.hpp>
#include <Graphics/Objects/Group.hpp>
#include <Graphics/Objects/LOD.hpp>
#include <Graphics/Objects/Light.hpp>
#include <Graphics/Objects/Line.hpp>
#include <Graphics/Objects/Mesh.hpp>
#include <Graphics/Objects/Points.hpp>
#include <Graphics/Objects/Sprite.hpp>
#include <OpenGL/Context.hpp>
#include <OpenGL/Program.hpp>
#include <OpenGL/RenderItem.hpp>
#include <OpenGL/Renderer.hpp>

using namespace OpenGL;

template <typename T>
void SetProperty(Common::Dictionary& dic) {
    std::string name = T().GetTypeName();
    MaterialProperties prop;

    prop.Load(name);
    dic.Set(name, prop);
}

Renderer::Renderer(OpenGL::Context& ctx) : _context(ctx) {
    SetProperty<Graphics::BasicMeshMaterial>(_properties);
}

Renderer::~Renderer() {

}

void Renderer::Render(std::shared_ptr<Graphics::Scene> scene, std::shared_ptr<Graphics::Camera> camera) {
    std::vector<Graphics::Object*> list;
    auto _o = scene.get() ? scene->shared_from_this() : nullptr;

    // Put all scene items into list
    Graphics::Traverse(_o, [this, &list](std::shared_ptr<Graphics::Object>& o) {
        // Note. Do not remove objects if they're just invisible
        if (o.get())
            list.push_back(o.get());
    });

    // Erase items which is left from last frame
    std::erase_if(_items, [&list](const std::pair<std::weak_ptr<Graphics::Object>, std::shared_ptr < RenderItem>>&i) {
        if (auto sp = i.first.lock()) {
            auto *ptr = sp.get();

            bool erase = std::find(list.begin(), list.end(), ptr) == list.end();

            if (erase) {
                DEBUG("Renderer: removing " << sp->GetName());
            }

            return erase;
        }

        DEBUG("Warning: item expired!");

        return true;
    });

    if (camera.get()) {
        // Update matrix
        _projMatrix = camera->GetProjectionMatrix() * camera->GetViewMatrix();
        _frustum.Update(camera->GetProjectionMatrix());
    }

    _opaqueObject.clear();
    _transparentObjects.clear();

    ProjectObject(scene, camera);

    // render background
    background.Render(scene);

    if (camera.get()) {
        if (_opaqueObject.size() > 0) RenderObjects(_opaqueObject, scene, camera);
        if (_transparentObjects.size() > 0) RenderObjects(_transparentObjects, scene, camera);
    }


    auto win = _context.GetWindow();

    _context.DrawLayout();

    SDL_GL_SwapWindow(win);
}

void Renderer::ProjectObject(std::shared_ptr<Graphics::Object> o, std::shared_ptr<Graphics::Camera> camera) {
    if (!o.get()) return;
    if (!o->IsVisible()) return;


    size_t h = o->GetHash();

    if (
            h == Common::__hash<Graphics::Mesh>() ||
            h == Common::__hash<Graphics::Line>() ||
            h == Common::__hash<Graphics::Points>()
            ) {

        if (!o->IsFrustumCulled() || _frustum.Intersects(*o)) {
            auto v = std::static_pointer_cast<Graphics::ViewObject>(o);
            auto g = v->GetGeometry();
            auto m = v->GetMaterial();

            if (m->IsVisible()) {
                Push(*o, *g, *m);
            }
        }
    } else if (h == Common::__hash<Graphics::Scene>()) {
    } else {
        DEBUG("Unrecognised object: " << o->GetName());
    }

    auto& children = o->GetChildren();

    for (size_t i = 0; i < children.size(); i++) {
        std::shared_ptr<Graphics::Object>& c = children[i];

        ProjectObject(c, camera);
    }
}

void Renderer::Push(Graphics::Object& object, Graphics::Geometry& geometry, Graphics::Material& material) {
    std::shared_ptr<RenderItem> item;
    auto it = _items.find(object.weak_from_this());

    if (it == _items.end()) {
        item = std::make_shared<RenderItem>();

        item->object = object.weak_from_this();
        item->geometry = geometry.weak_from_this();
        item->material = material.weak_from_this();

        _items.emplace(object.weak_from_this(), item);
    } else {
        item = it->second;
    }

    if (material.IsTransparent()) {
        _transparentObjects.emplace_back(item);
    } else {
        _opaqueObject.emplace_back(item);
    }
}

void Renderer::RenderObjects(std::vector<std::weak_ptr<RenderItem>> objects,
        std::shared_ptr<Graphics::Scene> scene,
        std::shared_ptr<Graphics::Camera> camera) {

    for (size_t i = 0; i < objects.size(); i++) {
        std::weak_ptr<RenderItem> wri = objects[i];

        if (auto ri = wri.lock()) {
            ri->Render(_state, _properties, camera);
        }
    }
}
