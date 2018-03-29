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

#ifndef IMG_H
#define IMG_H

#include <vector>

#include <SDL.h>

class Img {

  private:

    int w, h;

    Uint32 *pixels;

    bool isDifferent(Uint32 A, Uint32 B, int mode) const;

  public:

    Img();

    Img(const Img& img);

    Img(int w, int h, Uint32 color);

    ~Img();

    Img& operator=(const Img& img);

    void loadBMP(const char* f_name);

    void loadRegionBMP(const char* f_name,
                       std::vector<int>& region_center_x,
                       std::vector<int>& region_center_y);

    void loadBMPtoSizeKeepAspect(const char *f_name, int n_w, int n_h);

    void loadSurface(SDL_Surface *surf);

    bool isLoaded() const;

    void fillImg(Uint32 color);

    bool isBorder(int x, int y, int mode) const;

    Uint32* getPixels() const;

    Uint32 getPixelAt(int x, int y) const;

    int getWidth() const;

    int getHeight() const;

    void setPixel(int x, int y, Uint32 color);

};

#endif
