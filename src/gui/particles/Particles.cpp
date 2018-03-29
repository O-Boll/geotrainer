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

#include "Particles.h"

Particles::Particles() {
  screen = 0;
  width = height = 0;
  init();
}

Particles::Particles(uint32_t* screen, uint32_t width, uint32_t height)
  : screen(screen), width(width), height(height) {
  init();
}

void Particles::init() {
  last_step_time = T.getElapsedMilliseconds();
  def_life = 2.0;
  def_life_variation = 0.5;
  def_color = 0xFFFFFFFF;
  def_speed = 100.0;
  def_speed_variation = 200.0;
  g = 200.0;
}

void Particles::create(const uint32_t x, const uint32_t y, const uint32_t n) {
  for(uint32_t i = 0; i < n; i++) {
    double r, v;
    Particle p;
    p.x = (double) x;
    p.y = (double) y;
    r = double(def_speed + def_speed_variation * (double(rand()) / RAND_MAX ));
    v = (double) rand();
    p.sx = r * sin(r);
    p.sy = r * cos(r);
    p.life.setTimer(def_life
                    + def_life_variation * (double(rand()) / RAND_MAX - .5));
    p.color = def_color;
    particles.push_back(p);
  }
}

double Particles::getStepTime() {
  return (T.getElapsedMilliseconds() - last_step_time) / 1000.0;
}

void Particles::step() {
  double delta = getStepTime();
  for(uint32_t i = 0; i < particles.size(); i++) {
    Particle* p = &particles.at(i);
    if(p->life.isExpired())
      particles.erase(particles.begin() + i--);
    else {
      p->x += delta * p->sx;
      p->y += delta * p->sy;
      p->sy += delta * g;
      if(p->y >= height - offset_y) {
        p->y = height - offset_y - 1;
        p->sy = -p->sy / (double(128 + rand() % 128) / 128.0);
      }
      if(p->x < 0) {
        p->x = 0;
        p->sx = -p->sx;
      }
      if(p->x >= width - offset_x) {
        p->x = width - offset_x - 1;
        p->sx = -p->sx;
      }
    }
  }
  last_step_time = T.getElapsedMilliseconds();
}

void Particles::draw() {
  for(int i = 0; i < (int) particles.size(); i++) {
    Particle p = particles.at(i);
    int x = (int) p.x + offset_x;
    int y = (int) p.y + offset_y;

    if(x     > 0 && y     > 0 && x     < width && y     < height) screen[ y      * width + x    ] = p.color;
    if(x + 1 > 0 && y     > 0 && x + 1 < width && y     < height) screen[ y      * width + x + 1] = p.color;
    if(x     > 0 && y + 1 > 0 && x     < width && y + 1 < height) screen[(y + 1) * width + x    ] = p.color;
    if(x + 1 > 0 && y + 1 > 0 && x + 1 < width && y + 1 < height) screen[(y + 1) * width + x + 1] = p.color;

    x += 1;
    y += 1;

    if(x + 1 > 0 && y     > 0 && x + 1 < width && y     < height) screen[ y      * width + x + 1] = 0;
    if(x     > 0 && y + 1 > 0 && x     < width && y + 1 < height) screen[(y + 1) * width + x    ] = 0;
    if(x + 1 > 0 && y + 1 > 0 && x + 1 < width && y + 1 < height) screen[(y + 1) * width + x + 1] = 0;
  }
}

void Particles::setOffset(int n_offset_x, int n_offset_y) {
  offset_x = n_offset_x;
  offset_y = n_offset_y;
}

void Particles::clear() {
  particles.clear();
}
