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

#ifndef COMMON_STATE_HPP
#define COMMON_STATE_HPP

#include <string>

namespace Common {
    class Application;

    class State {
    public:
        State(Application* app, const std::string& name);
        virtual ~State();

        virtual void OnPush();

        virtual void OnPop();

        virtual void OnDisable();

        virtual void OnEnable();

        virtual void HandleInput();

        virtual void Update(float deltaTime);

        const std::string& GetName() const;
    protected:
        Application& _app;
    private:
        std::string _name;
    };
}

#endif /* !COMMON_STATE_HPP */

