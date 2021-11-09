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

#ifndef COMMON_CONFIG_HPP
#define COMMON_CONFIG_HPP

#include <string>

#include <yaml-cpp/yaml.h>

#include <Common/Debug.hpp>

namespace Common {

    class Config {
    private:
        std::string _filename;
        YAML::Node _config;
    public:
        Config(const std::string& filename);

        template<class T>
        T Get(const std::string& section, const std::string& key,
                T defaultValue) const {
            if (_config.Type() == YAML::NodeType::Map && _config[section]) {
                if (_config[section][key] && _config[section][key].IsScalar()) {
                    return _config[section][key].as<T>();
                }
            }

            DEBUG("Config " << section << "." << key << " do not exist!");

            return defaultValue;
        }

        template<typename T>
        void Set(const std::string& section, const std::string& key, T value) {
            DEBUG("Set config " << section << " " << key << " := " << value);
            _config[section][key] = value;
        }
        
        void Save();
    };
}

#endif /* !COMMON_CONFIG_H */

