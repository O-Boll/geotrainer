#ifndef STATE_FACTORY_H
#define STATE_FACTORY_H

#include "State.h"

struct StateFactory {

  static State* createState(const StateConfig sc);

};

#endif
