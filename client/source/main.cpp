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

#include <stdexcept>
#include <iostream>

#include <Client/MenuState.hpp>

using namespace std;
using namespace Client;

int main(int argc, char** argv) {
    try {
        Application app;

        app.PushState<MenuState>(&app);

        app.Run();

    } catch (runtime_error& re) {
        cerr << "Runtime error: " << re.what() << endl;

        return 1;
    }

    return 0;
}

