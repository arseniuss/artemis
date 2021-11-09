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

#ifndef COMMON_OBSERVER_HPP
#define COMMON_OBSERVER_HPP

#include <filesystem>
#include <functional>
#include <memory>
#include <vector>

#include <Common/Debug.hpp>

namespace Common {
    class Observable;

    using OnDestructCallback = std::function<void(Observable*)>;

    class Observable {
    private:
        std::vector<OnDestructCallback> _onDestruct;
    public:

        Observable() {
        }

        virtual ~Observable() {
            DEBUG("Observable died (destructs=" << _onDestruct.size() << ")");

            for (OnDestructCallback callback : _onDestruct) {
                callback(this);
            }
        }

        void OnDestruct(OnDestructCallback callback) {
            _onDestruct.emplace_back(callback);
        }
    };

    template<class TObserver, class TObservable>
    inline void RegisterOnDestruct(TObserver* observer, std::shared_ptr<TObservable> observable,
            std::function<void(TObserver*, std::weak_ptr<TObservable>) > func) {
        //std::weak_ptr<TObserver> w = a->weak_from_this();

        DEBUG("Registering " << typeid (TObserver).name() << " to " << typeid (TObservable).name());

        observable->OnDestruct([observer, func](Common::Observable * o) {
            TObservable* b = reinterpret_cast<TObservable*> (o);

            DEBUG("On " << typeid (TObservable).name() << " died (" << typeid (TObserver).name() << ")");

            //if (auto s = w.lock()) {
            DEBUG(typeid (TObservable).name() << " died --> calling " << typeid (TObserver).name());

            func(observer, b->weak_from_this());
            //}
        });
    }
}

#endif /* !COMMON_OBSERVER_HPP */
