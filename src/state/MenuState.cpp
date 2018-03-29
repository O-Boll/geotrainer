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
