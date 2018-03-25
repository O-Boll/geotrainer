#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "State.h"
#include "../gui/MenuGUI.h"

class MenuState : public State {

  private:

    MenuGUI m_gui;

    bool run_();

  public:

    MenuState(const StateConfig n_s_conf);

    virtual bool changeState() const;
    virtual StateConfig getStateConfig();

};

#endif
