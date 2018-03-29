/*----------------------------------------------------------------------------
This file is part of GeoTrainer.

MIT License

Copyright (c) 2018 Olle Eriksson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
----------------------------------------------------------------------------*/

#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include <string>

#include "Box.h"
#include "../text/Typesetter.h"

class TextBox : public Box {

  private:

    Typesetter ts;

    int spacing;

  public:

    TextBox();

    TextBox(Uint32*     n_screen,
            int         n_width,
            int         n_height,
            int         n_x,
            int         n_y,
            int         n_w,
            int         n_h,
            Uint32      n_color,
            Uint32      n_border_color,
            int         n_shadow_mode,
            Typewriter* tw             );

    void addLine(std::string s, double life);

    void clearLines();

    void step();

    void setSlowTyping(bool slow_typing);

    void draw() const;
};

#endif
