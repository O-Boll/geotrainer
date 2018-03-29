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

#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

#include <cstdint>

#include "Filter.h"

using std::uint32_t;

class MedianFilter : public Filter {

  private:

    struct median_return {
      std::uint32_t ul, ur, ll, lr;
    };

    median_return r;

    std::uint32_t* s_screen;
    std::uint32_t s_width, s_height, scale;

    virtual void apply_();

  public:

    MedianFilter();
    MedianFilter(std::uint32_t* screen, std::uint32_t width, std::uint32_t height);
    void setSmallScreen(std::uint32_t* n_s_screen,
                        std::uint32_t n_s_width,
                        std::uint32_t n_s_height,
                        std::uint32_t n_scale);
    virtual ~MedianFilter();
    std::uint32_t getBrightness(std::uint32_t color);
    bool calculateMedians(std::uint32_t x, std::uint32_t y);

};

#endif
