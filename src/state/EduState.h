#ifndef EDU_STATE_H
#define EDU_STATE_H

#include <string>

#include "GameState.h"

class EduState : public GameState {

  private:

    bool start_screen_on;
    bool instruction_screen_on;
    bool animation_on;
    int add_questions;
    std::string instructions;

    virtual void run__();

  public:

    EduState(StateConfig n_s_conf);

    virtual void init();

    virtual void printCorrectAnswer();
    virtual void printWrongAnswer();

};

#endif
