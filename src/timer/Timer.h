#ifndef TIMER_H
#define TIMER_H

#include <ctime>

using namespace std;

class Timer {

  private:

    clock_t start_clock;

    clock_t end_clock;

    bool frozen; /* when frozen, the timer is never expired */

    double interpolate(unsigned int mode) const;

  public:

    Timer();

    Timer(double seconds);

    void setTimer(double seconds);

    void freeze();

    void thaw();

    bool isExpired() const;

    int getElapsedSeconds() const;

    int getElapsedMilliseconds() const;

    int getSecondsLeft() const;

    int getMillisecondsLeft() const;

    double getLinearInterpolation() const;

    double getCubicInterpolation() const;

};

#endif
