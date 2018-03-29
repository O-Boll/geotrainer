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

#include <cmath>

#include "State.h"

int State::frame_rate = 0;

State::~State() {}

bool State::run() {

  /* We need a timer to calculate the frame rate below */
  static Timer timer;

  bool run_return = run_();

  /* We calculate and keep track of the frame rate here */
  static int last_t = 0;
  static int last_frate = 0;
  int current_t = timer.getElapsedMilliseconds();
  int delta_t = current_t - last_t;
  delta_t == 0 ? 1 : delta_t;
  /* We use exponential smoothing with factor a to calculate the frame rate */
  double a = 0.8;
  double dfrate = double(last_frate) * a + (1000.0 / double(delta_t)) * (1.0 - a);
  frame_rate = int(std::round(dfrate));
  last_t = current_t;
  last_frate = frame_rate;

  return run_return;
}

int State::getFrameRate() const {
  return frame_rate;
}
