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

#ifndef CLIENT_CLIENTAPPLICATION_HPP
#define CLIENT_CLIENTAPPLICATION_HPP

#include <Common/Application.hpp>
#include <Graphics/Context.hpp>

namespace Client {

    class Application : public Common::Application {
    public:

        Application();

        ~Application();

        Graphics::Context& GetContext();

        void Run() override;

        Graphics::Context& GetGraphics() {
            return *_graphics;
        }
    private:
        std::shared_ptr<Graphics::Context> _graphics;
    };
}


#endif /* !CLIENT_CLIENTAPPLICATION_HPP */

