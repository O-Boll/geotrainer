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

#include "CanvasFilter.h"
#include "../img/Img.h"

using std::uint8_t;
using std::uint32_t;

CanvasFilter::CanvasFilter() {
  canvas = 0;
  canvas_width = canvas_height = 0;
}

CanvasFilter::CanvasFilter(uint32_t* screen, uint32_t width, uint32_t height)
  : Filter(screen, width, height) {

  canvas = 0;
  canvas_width = canvas_height = 0;
}

CanvasFilter::CanvasFilter(const CanvasFilter& cf) {
  *this = cf;
}

CanvasFilter& CanvasFilter::operator=(const CanvasFilter& cf) {
  screen = cf.screen;
  width = cf.width;
  height = cf.height;
  canvas_width = cf.canvas_width;
  canvas_height = cf.canvas_height;
  delete[] canvas;
  canvas = new uint8_t[canvas_width * canvas_height * 2];
  for(uint32_t i = 0; i < canvas_width * canvas_height * 2; i++)
    canvas[i] = cf.canvas[i];
  return *this;
}

CanvasFilter::~CanvasFilter() {
  delete[] canvas;
}

void CanvasFilter::loadCanvas(const char* filename) {
  Img canvas_img;
  canvas_img.loadBMP(filename);
  canvas_width = canvas_img.getWidth();
  canvas_height = canvas_img.getHeight();
  uint32_t sum = 0;
  for(uint32_t i = 0; i <= canvas_width * canvas_height; i++)
    sum += (((canvas_img.getPixels())[i] >> 8) & 0xff);
  uint8_t average_brightness = uint8_t(sum / (canvas_width * canvas_height));


  canvas = new uint8_t[canvas_width * canvas_height * 2];
  for(uint32_t i = 0; i < canvas_width * canvas_height; i++) {
    uint8_t pixel_brightness = (((canvas_img.getPixels())[i] >> 8) & 0xff);
    if(pixel_brightness >= average_brightness) {
      canvas[2 * i] = 1;
      canvas[2 * i + 1] = (pixel_brightness - average_brightness) / 6;
    }
    else {
      canvas[2 * i] = 0;
      canvas[2 * i + 1] = (average_brightness - pixel_brightness) / 4;
    }
  }
}

void CanvasFilter::apply_() {
  uint8_t* pixel = (uint8_t*) &(screen[0]);
  uint8_t* c_i;
  uint32_t c_x, c_y;
  c_y = offset_y;
  for(uint32_t y = 0; y < height; y++) {
    c_x = offset_x;
    c_i = canvas + ((c_y * canvas_width + offset_x) << 1);
    for(uint32_t x = 0; x < width; x++) {
      if(*(c_i++))
        for(int i = 0; i < 3; i++, pixel++)
          *pixel = (*c_i >= 0xff - *pixel ? 0xff : *pixel + *c_i);
      else
        for(int i = 0; i < 3; i++, pixel++)
          *pixel = (*c_i >= *pixel ? 0 : *pixel -= *c_i);
      c_i++;
      if(++c_x % canvas_width == 0) {
        c_i -= canvas_width << 1;
        c_x = 0;
      }
      pixel++;
    }
    if(++c_y == canvas_height)
      c_y = 0;
    else
      c_i += (canvas_width - c_x) << 1;
  }
}

void CanvasFilter::setOffset(int n_offset_x, int n_offset_y) {
  offset_x = n_offset_x;
  if(offset_x > 0)
    offset_x -= canvas_width * (offset_x / canvas_width);
  else if(offset_y < 0)
    offset_x -= canvas_width * (1 + offset_x / canvas_width);
  offset_y = n_offset_y;
  if(offset_y > 0)
    offset_y -= canvas_width * (offset_y / canvas_height);
  else if(offset_y < 0)
    offset_y -= canvas_width * (1 + offset_y / canvas_height);
}
