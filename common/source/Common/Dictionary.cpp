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

#include <Common/Dictionary.hpp>

using namespace Common;

Dictionary::Dictionary() {
    Set<int>("VERSION", 0);
}

bool Dictionary::Exists(const std::string& name) const {
    return _data.find(name) != _data.end();
}

const Common::Dictionary& Dictionary::GetDictionary(const std::string& name) const {
    return ConstGet<Common::Dictionary>(name);
}

const std::string& Dictionary::GetString(const std::string& name) const {
    auto it = _data.find(name);

    if (it == _data.end())
        throw std::runtime_error(std::string("Dictionary has no key ") + name);

    return *(std::string *)it->second;
}
