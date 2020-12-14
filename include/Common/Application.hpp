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

#ifndef COMMON_APPLICATION_HPP
#define COMMON_APPLICATION_HPP

#include <vector>
#include <memory>

#include <Common/Config.hpp>
#include <Common/Debug.hpp>
#include <Common/Event.hpp>
#include <Common/State.hpp>

namespace Common {

    class Application {
    public:
        Application();
        ~Application();

        template<typename T, typename... Args>
        void PushState(Args&&... args) {
            if (_states.size()) {
                auto& c = _states.back();

                c->OnDisable();
            }

            _states.push_back(std::make_unique<T>(std::forward<Args>(args)...));
            auto& s = _states.back();

            Debug() << "Pushing state " << s->GetName() << std::endl;

            s->OnPush();
        }

        void PopState();

        virtual void Run() = 0;

        void AddLoop(EventCallbackBase<bool>* loop);
        void RemoveLoop(EventCallbackBase<bool>* loop);

    protected:
        typedef std::vector<EventCallbackBase<bool>*> LoopVectorT;

        std::vector<std::unique_ptr<State>> _states;
        bool _isPoping = false;
        LoopVectorT _loops;
    };
}


#endif /* !COMMON_APPLICATION_HPP */

