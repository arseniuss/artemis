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

//#include <algorithm>

#include <Common.hpp>
#include <Graphics/Objects/Group.hpp>
#include <Graphics/Objects/LOD.hpp>
#include <Graphics/Objects/Light.hpp>
#include <Graphics/Objects/Line.hpp>
#include <Graphics/Objects/Mesh.hpp>
#include <Graphics/Objects/Points.hpp>
#include <Graphics/Objects/Sprite.hpp>
#include <OpenGL/Context.hpp>
#include <OpenGL/Renderer.hpp>

using namespace OpenGL;

Renderer::Renderer(OpenGL::Context& ctx) : _context(ctx) {

}

Renderer::~Renderer() {

}

void Renderer::Begin() {
    //auto win = _context.GetWindow();


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(std::shared_ptr<Graphics::Scene> scene, std::shared_ptr<Graphics::Camera> camera) {
    std::vector<Graphics::Object*> list;
    auto _o = scene.get() ? scene->shared_from_this() : nullptr;

    // TODO: light and shadow lists

    // Put all scene items into list
    Graphics::Traverse(_o, [this, &list](std::shared_ptr<Graphics::Object>& o) {
        // TODO: check if is renderable
        if (o.get())
            list.push_back(o.get());
    });

    // Erase items which is left from last frame
    std::erase_if(_items, [&list](const std::pair<std::weak_ptr<Graphics::Object>, std::shared_ptr < RenderItem>>&i) {
        if (auto sp = i.first.lock()) {
            auto *ptr = sp.get();

            bool erase = std::find(list.begin(), list.end(), ptr) == list.end();

            if (erase) {
                Common::Debug() << "Renderer: removing " << sp->GetName() << std::endl;
            }

            return erase;
        }

        Common::Debug() << "Warning: item expired!" << std::endl;

        return true;
    });

    if (camera.get()) {
        // Update matrix
        _projMatrix = camera->GetProjectionMatrix() * camera->GetMatrixWorldInverse();
        _frustum.Update(_projMatrix);
    }

    ProjectObject(scene, camera, 0, false);
}

void Renderer::ProjectObject(std::shared_ptr<Graphics::Object> o, std::shared_ptr<Graphics::Camera> camera,
        int groupOrder, bool sortObjects) {
    if (!o.get())
        return;
    if (!o->IsVisible())
        return;

    size_t h = o->GetHash();

    if (h == Common::__hash<Graphics::Group>()) {
        auto g = std::static_pointer_cast<Graphics::Group>(o);

        groupOrder = g->GetRenderOrder();
    } else if (h == Common::__hash<Graphics::LOD>()) {
        auto l = std::static_pointer_cast<Graphics::LOD>(o);

        if (l->AutoUpdate())
            l->Update(camera);
    } else if (h == Common::__hash<Graphics::Light>()) {
        auto l = std::static_pointer_cast<Graphics::Light>(o);

        //_lights.emplace_back(l->weak_from_this());

        if (l->CastsShadow()) {
            //_shadows.emplace_back(l->weak_from_this());
        }
    } else if (h == Common::__hash<Graphics::Sprite>()) {
        if (!o->IsFrustumCulled() || _frustum.Intersects(*o)) {
            float z = 1.0f;

            if (sortObjects) {
                //glm::mat4x4 m = o->GetMatrixWorld();
                //glm::vec3 v = {
                //    m[12],
                //    m[13],
                //    m[14]
                //};

                //v *= _projMatrix;
                //z = v.z;
            }

            auto v = std::static_pointer_cast<Graphics::ViewObject>(o);
            auto* g = v->GetGeometry();
            auto* m = v->GetMaterial();

            if (m->IsVisible()) {
                Push(*o, *g, *m, groupOrder, z, nullptr);
            }
        }
    } else if (
            h == Common::__hash<Graphics::Mesh>() ||
            h == Common::__hash<Graphics::Line>() ||
            h == Common::__hash<Graphics::Points>()
            ) {
        if (!o->IsFrustumCulled() || _frustum.Intersects(*o)) {
            float z = 1.0f;

            if (sortObjects) {
                //glm::mat4x4 m = o->GetMatrixWorld();
                //glm::vec3 v = {
                //    m[12],
                //    m[13],
                //    m[14]
                //};

                //v *= _projMatrix;
                //z = v.z;
            }

            auto v = std::static_pointer_cast<Graphics::ViewObject>(o);
            auto* g = v->GetGeometry();
            auto* m = v->GetMaterial();

            if (m->IsVisible()) {
                if (m->IsArray()) {
                    auto groups = g->GetGroups();
                    auto materials = m->GetMaterials();

                    for (size_t i = 0; i < groups.size(); i++) {
                        auto group = groups[i];
                        //auto material = materials[group->GetMaterialIndex()];

                        //if (auto mat = material.lock()) {
                        //    if (mat->IsVisible()) {
                        //        //Push(*o, *g, *mat, groupOrder, z, *group);
                        //    }
                        //}
                    }
                } else {
                    Push(*o, *g, *m, groupOrder, z, nullptr);
                }
            }
        }

    } else {
        // TODO
    }

    auto& children = o->GetChildren();

    for (size_t i = 0; i < children.size(); i++) {
        //std::shared_ptr<Graphics::Object>& c = children[i];

        //ProjectObject(c, camera, groupOrder, 0, false);
    }


}

void Renderer::Push(Graphics::Object& o, Graphics::Geometry& geometry, Graphics::Material& material, int groupOrder, float z, Graphics::Group* group) {
    /*
        std::shared_ptr<RenderItem> item;
        auto it = _items.find(o.weak_from_this());
        auto materialProperties = Properties.Get(material);

        if (it == _items.end()) {
            item = std::make_shared<RenderItem>(
                    o.GetId(),
                    o,
                    geometry,
                    material,
                    materialProperties.Exists("PROGRAM") ? materialProperties.Get<Program>() : _defaultProgram,
                    groupOrder,
                    o->RenderOrder(),
                    z,
                    group
                    );
        } else {
            item = it->second;
        }

        item->Update(o->shared_from_this());
     */
}

void Renderer::RenderObject(Graphics::Object& object, Graphics::Scene& scene, Graphics::Camera& camera, Graphics::Geometry& geo, Graphics::Material& mat) {

}

void Renderer::Finish() {
    auto win = _context.GetWindow();

    _context.DrawLayout();

    SDL_GL_SwapWindow(win);
}

