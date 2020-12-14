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

#ifndef COMMON_EVENT_HPP
#define COMMON_EVENT_HPP

template<typename R>
class EventCallbackBase {
public:
    virtual R operator()() = 0;
    virtual bool is(void *) = 0;
};

template<typename T, typename R>
class EventCallback : public EventCallbackBase<R> {
private:
    T* _instance;
    R(T::*_function)();
public:

    EventCallback(T* instance, R(T::*function)()) :
    _instance(instance), _function(function) {

    }

    virtual R operator()() override {
        return (_instance->*_function)();
    }
    
    virtual bool is(void *ptr) override {
        return ptr == _instance;
    }
};

#endif /* !COMMON_EVENT_HPP */
