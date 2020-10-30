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

#ifndef NETWORK_PAYLOAD_HPP
#define NETWORK_PAYLOAD_HPP

#include <cstdint>
#include <string>

#include <Network/Protocol.hpp>

namespace Network {

    struct Payload {
        int32_t _id;
        bool _isValid = false;

        char *_begin;
        size_t _sz;
        size_t _readPos = 0;
    public:
        typedef bool (Payload::*BoolType)(std::size_t);
        
        Payload(char *data, size_t sz);

        ToServerCommand GetServerCommand();
        
        bool checkSize(size_t size);
        
        operator BoolType() const;

        Payload& operator>>(bool& data);
        Payload& operator>>(int8_t& data);
        Payload& operator>>(uint8_t& data);
        Payload& operator>>(int16_t& data);
        Payload& operator>>(uint16_t& data);
        Payload& operator>>(int32_t& data);
        Payload& operator>>(uint32_t& data);
        Payload& operator>>(int64_t& data);
        Payload& operator>>(uint64_t& data);
        Payload& operator>>(float& data);
        Payload& operator>>(double& data);
        Payload& operator>>(std::string& data);

        Payload& operator<<(bool& data);
        Payload& operator<<(int8_t& data);
        Payload& operator<<(uint8_t& data);
        Payload& operator<<(int16_t& data);
        Payload& operator<<(uint16_t& data);
        Payload& operator<<(int32_t& data);
        Payload& operator<<(uint32_t& data);
        Payload& operator<<(int64_t& data);
        Payload& operator<<(uint64_t& data);
        Payload& operator<<(float& data);
        Payload& operator<<(double& data);
        Payload& operator<<(char& data);
        Payload& operator<<(std::string& data);
    };

    template<ToServerCommand cmd>
    class ServerPayload {
    public:
        ServerPayload(Payload payload);
    };

    template<>
    class ServerPayload<Network::HandshakeRequest> {
    public:

        ServerPayload(Payload payload) {
        }
    };
}

#endif /* !NETWORK_PAYLOAD_HPP */
