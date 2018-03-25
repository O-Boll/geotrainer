#include "MenuState.h"

MenuState::MenuState(const StateConfig n_s_conf) {
  s_conf = n_s_conf;
  m_gui.setGameMode(s_conf.game_mode);
  m_gui.setMenuItem(s_conf.menu_item);
}

bool MenuState::run_() {
  m_gui.handleEvents();
  m_gui.step();
  m_gui.draw();
  if (GUI::getCloseGUI())
    return false;
  return true;
}

bool MenuState::changeState() const {
  return m_gui.getStartGame();
}

StateConfig MenuState::getStateConfig() {
  s_conf.state = m_gui.getGameMode() + 1; /* ... + 1 for stupid reason, should be fixed */
  s_conf.game_mode = m_gui.getGameMode();
  s_conf.menu_item = m_gui.getMenuItem();
  s_conf.map_name = m_gui.getMapName();
  return s_conf;
}
