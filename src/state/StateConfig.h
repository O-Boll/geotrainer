#ifndef STATE_CONFIG_H
#define STATE_CONFIG_H

#include <string>

struct StateConfig {

  enum state_enum {menu = 0, arcade = 1, edu = 2, tt = 3};

  int state;
  int game_mode;
  int menu_item;
  std::string map_name;

  StateConfig();

};

#endif
