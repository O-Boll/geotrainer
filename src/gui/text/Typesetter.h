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

#ifndef TYPESETTER_H
#define TYPESETTER_H

#include <string>
#include <vector>

#include <SDL.h>

#include "../img/Img.h"
#include "../../timer/Timer.h"
#include "Typewriter.h"

class Typesetter {

  public:

    struct Box {
      int x, y, w, h;
    };

    struct Line {
      std::string s;
      Uint32 color;
      bool in_queue;
      Timer life;
      int n_chars;
      int n_typed_chars;
    };

  private:

    Typewriter* tw;

    Uint32* screen;

    int width, height;

    std::vector<Line> lines;

    int max_number_of_lines, max_line_size;

    Box box;

    Box clipping_box;

    int text_w, text_h;

    double def_life_span;

    Uint32 def_color;

    bool add_top;

    bool slow_typing; /* if true, text is printed one letter at a time */

    int typing_speed; /* characters per second */

    Timer typing_timer; /* timer used for slow typing */

    int typing_counter;
    /* At a given time, the value of typing_counter is the maximum number
       of characters that may have been printed by the typesetter (using
       slow typing). If at any time the typesetter finished printing all
       of its lines without any new lines being added immediately
       thereafter, the actual total number of printed characters will be
       less than typing_counter. */

    int typing_counter_offset;
    /* At any given time, the value of typing_counter_offset is the
       difference between typing_counter and the the actual total number
       of characters that have been printed. */

    void calcTextSize();

    void typeString(int& y, const char *str, Uint32 color, int& letter_count) const;

    void typeCharacter(Img *c, int x, int y, Uint32 color) const;

  public:

    Typesetter();

    Typesetter(Uint32* n_screen, int n_width, int n_height, Typewriter* n_tw);

    void setBox(int n_x, int n_y, int n_w, int n_h );

    void setClipping(int n_x, int n_y, int n_w, int n_h );

    void addLine(std::string s, double life, Uint32 color);

    void addLine(std::string s, double life);

    void addLine(std::string s);

    void setLineColor(int n, Uint32 color);

    void setDefLineColor(int n);

    void setColor(Uint32 color);

    void clearLines();

    void removeLine(int n);

    void setSlowTyping(bool n_slow_typing);

    void step();

    int getNumberOfLines() const;

    int getX() const;

    int getY() const;

    int getW() const;

    int getH() const;

    int getTextWidth() const;

    int getTextHeight() const;

    void type() const;

};

#endif
