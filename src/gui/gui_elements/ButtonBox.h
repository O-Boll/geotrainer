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

#ifndef BUTTON_BOX_H
#define BUTTON_BOX_H

#include <vector>
#include <string>

#include <SDL.h>

#include "Button.h"
#include "../text/Typewriter.h"

class ButtonBox {

  public:

    enum {none = -1};

  private:

    Uint32* screen;

    int width, height;

    int x, y, w, h;

    Box body;

    Typewriter *tw;

    std::vector<Button> buttons;

    Uint32 color, alt_color, border_color;

    int position, spacing;

    void drawButtonAtPosition(Button b, int n) const;

    bool buttonIsOver(Button& b, int n, int mouse_x, int mouse_y);

  public:

    ButtonBox();

    ButtonBox(Uint32*     n_screen,
              int         n_width,
              int         n_height,
              int         n_x,
              int         n_y,
              int         n_w,
              int         n_h,
              Uint32      n_color,
              Uint32      n_alt_color,
              Uint32      n_border_color,
              Typewriter* n_tw           );

    void addButton(std::string n_label);

    void setPosition(int n);

    int getPosition() const;

    int size() const;

    void step();

    void draw() const;

    int isOver(int mouse_x, int mouse_y);

};

#endif
