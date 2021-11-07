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

#ifndef COMMON_DICTIONARY_HPP
#define COMMON_DICTIONARY_HPP

#include <string>
#include <map>

namespace Common {

    class Dictionary {
    protected:
        std::map<std::string, void*> _data;
    public:
        Dictionary();

        bool Exists(const std::string& name) const;

        template<typename Type>
        void Set(const std::string& name, Type value) {
            Type* i = new Type();

            *i = value;

            _data.emplace(name, i);
        }

        template<typename Type>
        void Set(const std::string& name, Type* value) {
            _data.emplace(name, value);
        }

        template<typename RetType>
        RetType& Get(const std::string& name) {
            auto it = _data.find(name);

            if (it == _data.end())
                throw std::runtime_error(std::string("Dictionary has no key \"") + name + "\"");

            return *(RetType *) it->second;
        }

        template<typename RetType>
        RetType& GetOrEmpty(const std::string& name) {
            auto it = _data.find(name);

            if (it == _data.end()) {
                auto ret = new RetType();

                _data.emplace(name, ret);

                return *ret;
            }

            return *(RetType *) it->second;
        }

        template<typename RetType>
        const RetType& ConstGet(const std::string& name) const {
            auto it = _data.find(name);

            if (it == _data.end())
                throw std::runtime_error(std::string("Dictionary has no key \"") + name + "\"");

            return *(RetType *) it->second;
        }

        const Common::Dictionary& GetDictionary(const std::string& name) const;
        const std::string& GetString(const std::string& name) const;

    };
}

#endif /* !COMMON_DICTIONARY_HPP */
