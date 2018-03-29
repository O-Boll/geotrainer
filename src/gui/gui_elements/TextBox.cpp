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

#include "TextBox.h"

TextBox::TextBox() {
}

TextBox::TextBox(Uint32*     n_screen,
                 int         n_width,
                 int         n_height,
                 int         n_x,
                 int         n_y,
                 int         n_w,
                 int         n_h,
                 Uint32      n_color,
                 Uint32      n_border_color,
                 int         n_shadow_mode,
                 Typewriter* tw             )

  : Box(n_screen,
        n_width,
        n_height,
        n_x,
        n_y,
        n_w,
        n_h,
        n_color,
        n_border_color,
        n_shadow_mode  ),

    ts(n_screen, n_width, n_height, tw) {

  spacing = 2;

  ts.setBox(n_x + spacing,
            n_y + spacing,
            n_w - 2 * spacing,
            n_h - 2 * spacing );

  ts.setClipping(n_x + spacing,
                 n_y + spacing,
                 n_w - 2 * spacing,
                 n_h - 2 * spacing);
}


void TextBox::addLine(std::string s, double life) {
  ts.addLine(s, life);
}


void TextBox::clearLines() {
  ts.clearLines();
}

void TextBox::step() {
  ts.step();
}

void TextBox::setSlowTyping(bool slow_typing) {
  ts.setSlowTyping(slow_typing);
}

void TextBox::draw() const {
  Box::draw();
  ts.type();
}
