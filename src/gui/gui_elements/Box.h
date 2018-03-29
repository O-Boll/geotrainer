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

#ifndef BOX_H
#define BOX_H

#include <SDL.h>

using namespace std;

class Box {

  private:

    Uint32* screen; /* this is where we draw the box */

    int width, height; /* width and height of screen */

    int x, y, w, h;

    int clip_x, clip_y, clip_w, clip_h; /* for clipping */

    Uint32 color, border_color;

    int shadow_mode; /* 0 = no shadow, 1 = outside shadow, 2 = inside shadow */

  public:

    Box();

    Box(Uint32* n_screen,
        int     n_width,
        int     n_height,
        int     n_x,
        int     n_y,
        int     n_w,
        int     n_h,
        Uint32  n_color,
        Uint32  n_border_color,
        int     n_shadow_mode);

    void setClipping(int n_clip_x,
                     int n_clip_y,
                     int n_clip_w,
                     int n_clip_h);

    virtual void draw() const;

  private:

    void drawBorder() const;

    void drawOutsideShadow() const;

    void drawInsideShadow() const;

  public:

    void setColor(Uint32 n_color);

    void setShadowMode(int n_shadow_mode);

    void moveTo(int n_x, int n_y);

    int getX() const;

    int getY() const;

    int getWidth() const;

    int getHeight() const;

    int getClippingX() const;

    int getClippingY() const;

    int getClippingWidth() const;

    int getClippingHeight() const;

};

#endif

