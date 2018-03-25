#ifndef STATE_H
#define STATE_H

#include "StateConfig.h"
#include "../timer/Timer.h"

class State {

  private:

    static int frame_rate;

  protected:

    StateConfig s_conf;

    virtual bool run_() = 0;

  public:

    virtual ~State();

    bool run();
    virtual bool changeState() const = 0;
    virtual StateConfig getStateConfig() = 0;
    int getFrameRate() const;

};

#endif
