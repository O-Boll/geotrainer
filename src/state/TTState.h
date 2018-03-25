#ifndef TT_STATE_H
#define TT_STATE_H

#include <string>

#include "GameState.h"

class TTState : public GameState {

  private:

    int streak;
    bool out_of_time;

    virtual void run__();

  public:

    TTState(StateConfig n_s_conf);

    virtual void init();

    void afterGame(std::string high_score);
    int calculateScore() const;

    virtual void printCorrectAnswer();
    virtual void printWrongAnswer();

};

#endif
