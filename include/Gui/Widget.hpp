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

#ifndef GUI_WIDGET_HPP
#define GUI_WIDGET_HPP

namespace Gui {

#define LAYOUT_LEFT     0x020
#define LAYOUT_TOP      0x040
#define LAYOUT_RIGHT    0x080
#define LAYOUT_DOWN     0x100
#define LAYOUT_HFILL    0x0a0
#define LAYOUT_VFILL    0x140
#define LAYOUT_HCENTER  0x000
#define LAYOUT_VCENTER  0x000
#define LAYOUT_CENTER   0x000
#define LAYOUT_FILL     0x1e0
#define LAYOUT_BREAK    0x200

#define BOX_ROW         0x002
#define BOX_COLUMN      0x003
#define BOX_LAYOUT      0x000
#define BOX_FLEX        0x002
#define BOX_NO_WRAP     0x000
#define BOX_WRAP        0x004
#define BOX_START       0x000

#define CORNER_NONE         0
#define CORNER_TOP_LEFT     1
#define CORNER_TOP_RIGHT    2
#define CORNER_DOWN_RIGHT   4
#define CORNER_DOWN_LEFT    8
#define CORNER_ALL          0xf
#define CORNER_TOP          3
#define CORNER_DOWN         0xc
#define CORNER_LEFT         9
#define CORNER_RIGHT        6

    struct WidgetBase {
    protected:
        virtual void setBox(unsigned int box) = 0;
        virtual void setCorners(int corners) = 0;
        virtual void setLayout(unsigned int layout) = 0;
        virtual void setMargins(int l, int t, int r, int b) = 0;
        virtual void setSize(int w, int h) = 0;
        virtual void setIsVisible(bool isVisible) = 0;
        virtual void setDebug(bool debug) = 0;
    public:
        virtual int GetId() const = 0;
    };

    template<typename T>
    struct TWidget : virtual WidgetBase {

        T* SetDebug(bool debug) {
            setDebug(debug);

            return (T*)this;
        }

        T* SetBox(unsigned int box) {
            setBox(box);

            return (T*)this;
        }

        T* SetCorners(int corner) {
            setCorners(corner);

            return (T*)this;
        }

        T* SetLayout(unsigned int layout) {
            setLayout(layout);

            return (T*)this;
        }

        T* SetMargins(int a, int b, int c, int d) {
            setMargins(a, b, c, d);
            return (T*)this;
        }

        T* SetSize(int w, int h) {
            setSize(w, h);
            return (T*)this;
        }

        T* SetIsVisible(bool isVisible) {
            setIsVisible(isVisible);
            return (T*)this;
        }
    };

    struct Widget : public TWidget<Widget> {
    };
}

#endif /* !GUI_WIDGET_HPP */
