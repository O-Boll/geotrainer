#ifndef PARTICLES_H
#define PARTICLES_H

#include <cmath>
#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include "../../timer/Timer.h"

class Particles {

  private:

    uint32_t* screen;
    uint32_t width, height, offset_x, offset_y;

    Timer T;
    int last_step_time;
    double getStepTime();

    struct Particle {
      double x, y, sx, sy;
      Timer life;
      uint32_t color;
    };

    std::vector<Particle> particles;

    double def_life, def_life_variation;

    double def_speed, def_speed_variation, g;

    uint32_t def_color;

  public:

    Particles();

    Particles(uint32_t* screen, uint32_t width, uint32_t height);

    void init();

    void create(const uint32_t x, const uint32_t y, const uint32_t n);

    void step();

    void draw();

    void setOffset(int n_offset_x, int n_offset_y);

    void clear();
};

#endif
