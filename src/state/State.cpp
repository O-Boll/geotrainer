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
