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

#include <endian.h>    // __BYTE_ORDER
#include <algorithm>   // std::reverse

#include <Network/Payload.hpp>

using namespace Network;

template <typename T>
constexpr T htonT(T value) noexcept {
#if __BYTE_ORDER == __LITTLE_ENDIAN
    char* ptr = reinterpret_cast<char*> (&value);
    std::reverse(ptr, ptr + sizeof (T));
#endif
    return value;
}

Payload::Payload() {

}

Payload::Payload(char* data, size_t sz) {
    _begin = data;
    _sz = sz;

    *this >> _id;
}

ToServerCommand Payload::GetServerCommand() {
    return (ToServerCommand) _id;
}

bool Payload::checkSize(size_t size) {
    _isValid = _isValid && (_readPos + size <= _sz);

    return _isValid;
}

const void *Payload::GetData() const {
    return _begin;
}

size_t Payload::GetDataSize() {
    return _sz;
}

Payload::operator BoolType() const {
    return _isValid ? &Payload::checkSize : nullptr;
}

Payload& Payload::operator>>(bool& data) {
    uint8_t value;

    if (*this >> value)
        data = (value != 0);

    return *this;
}

Payload& Payload::operator>>(int8_t& data) {
    if (checkSize(sizeof (data))) {
        data = *reinterpret_cast<const int8_t*> (_begin[_readPos]);
        _readPos += sizeof (data);
    }

    return *this;
}

Payload& Payload::operator>>(uint8_t& data) {
    if (checkSize(sizeof (data))) {
        data = *reinterpret_cast<const uint8_t*> (_begin[_readPos]);
        _readPos += sizeof (data);
    }

    return *this;
}

Payload& Payload::operator>>(int16_t& data) {
    if (checkSize(sizeof (data))) {
        data = htonT<int16_t>(*reinterpret_cast<const int16_t*> (_begin[_readPos]));
        _readPos += sizeof (data);
    }

    return *this;
}

Payload& Payload::operator>>(uint16_t& data) {
    if (checkSize(sizeof (data))) {
        data = htonT<uint16_t>(*reinterpret_cast<const uint16_t*> (_begin[_readPos]));
        _readPos += sizeof (data);
    }

    return *this;
}

Payload& Payload::operator>>(int32_t& data) {
    if (checkSize(sizeof (data))) {
        data = htonT<int32_t>(*reinterpret_cast<const int32_t*> (_begin[_readPos]));
        _readPos += sizeof (data);
    }

    return *this;
}

Payload& Payload::operator>>(uint32_t& data) {
    if (checkSize(sizeof (data))) {
        data = htonT<uint32_t>(*reinterpret_cast<const uint32_t*> (_begin[_readPos]));
        _readPos += sizeof (data);
    }

    return *this;
}

Payload& Payload::operator>>(int64_t& data) {
    if (checkSize(sizeof (data))) {
        data = htonT<int64_t>(*reinterpret_cast<const int64_t*> (_begin[_readPos]));
        _readPos += sizeof (data);
    }

    return *this;
}

Payload& Payload::operator>>(uint64_t& data) {
    if (checkSize(sizeof (data))) {
        data = htonT<uint64_t>(*reinterpret_cast<const uint64_t*> (_begin[_readPos]));
        _readPos += sizeof (data);
    }

    return *this;
}

Payload& Payload::operator>>(float& data) {
    if (checkSize(sizeof (data))) {
        data = htonT<float>(*reinterpret_cast<const float*> (_begin[_readPos]));
        _readPos += sizeof (data);
    }

    return *this;
}

Payload& Payload::operator>>(double& data) {
    if (checkSize(sizeof (data))) {
        data = htonT<double>(*reinterpret_cast<const double*> (_begin[_readPos]));
        _readPos += sizeof (data);
    }

    return *this;
}

Payload& Payload::operator>>(std::string& data) {
    uint32_t len;

    *this >> len;
    data.clear();
    if ((len > 0) && checkSize(len)) {
        data.assign(&_begin[_readPos], len);
        _readPos += len;
    }

    return *this;
}

ClientPayload<Network::HandshakeResponse>::ClientPayload() : Payload() {
    
}

