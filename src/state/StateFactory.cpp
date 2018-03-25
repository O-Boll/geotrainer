#include "ArcadeState.h"
#include "EduState.h"
#include "MenuState.h"
#include "StateFactory.h"
#include "TTState.h"

State* StateFactory::createState(const StateConfig sc) {
  switch(sc.state) {
    case StateConfig::menu   :  return new MenuState(sc);
    case StateConfig::arcade :  return new ArcadeState(sc);
    case StateConfig::edu    :  return new EduState(sc);
    case StateConfig::tt     :  return new TTState(sc);
  }
}
