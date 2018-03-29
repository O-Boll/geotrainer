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
