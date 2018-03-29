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

#include <limits>

#include "Timer.h"

using namespace std;

Timer::Timer() {
  start_clock = end_clock = clock();
  frozen = false;
}
#include <iostream>
Timer::Timer(double seconds) {
  start_clock = clock();
  if(seconds < 0.0)
    end_clock = std::numeric_limits<clock_t>::max();
  else {
    clock_t ticks = int(seconds * CLOCKS_PER_SEC);
    end_clock = start_clock + ticks;
  }
  frozen = false;
}

void Timer::setTimer(double seconds) {
  start_clock = clock();
  if(seconds < 0.0)
    end_clock = std::numeric_limits<clock_t>::max();
  else {
    clock_t ticks = int(seconds * CLOCKS_PER_SEC);
    end_clock = start_clock + ticks;
  }
}

void Timer::freeze() {
  frozen = true;
}

void Timer::thaw() {
  frozen = false;
}

bool Timer::isExpired() const {
  if(   !frozen
     && end_clock != std::numeric_limits<clock_t>::max() /* max value taken to mean inf */
     && clock() >= end_clock)
    return true;
  return false;
}

int Timer::getElapsedMilliseconds() const {
  int elapsed_ticks = clock() - start_clock;
  return (1000 * elapsed_ticks) / CLOCKS_PER_SEC;
}

int Timer::getElapsedSeconds() const {
  return getElapsedMilliseconds() / 1000;
}

int Timer::getMillisecondsLeft() const {
  int ticks_left = end_clock - clock();
  if (ticks_left < 0) { ticks_left = 0; }
  return (1000 * ticks_left) / CLOCKS_PER_SEC;
}

int Timer::getSecondsLeft() const {
  return getMillisecondsLeft() / 1000;
}

double Timer::interpolate(unsigned int mode) const {
  clock_t current_clock = clock();

  if     (current_clock <= start_clock){ return 0.0; }
  else if(current_clock >= end_clock)  { return 1.0; }

  /* delta <= 0 cannot happen, as this implies start_clock >= end_clock, which
     in turn implies that one of the two conditionals above is true, thus the
     function has already returned 0.0 or 1.0. Q.E.D. */

  double delta = double (end_clock - start_clock);
  double t = double (current_clock - start_clock);
  double interpolate = 0.0;

  if(mode == 0) {
    interpolate = t / delta;
  }
  else if(mode == 1) {
    t = t / delta;
    interpolate = 3.0 * t * t - 2.0 * t * t * t;
  }

  return interpolate;
}

double Timer::getLinearInterpolation() const {
  return interpolate(0);
}

double Timer::getCubicInterpolation() const {
  return interpolate(1);
}
