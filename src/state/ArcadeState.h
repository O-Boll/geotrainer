#ifndef ARCADE_STATE_H
#define ARCADE_STATE_H

#include <string>

#include "GameState.h"

class ArcadeState : public GameState {

  private:

    int streak;
    int combo;
    int last_score_time;
    int last_frame_elapsed_seconds;
    bool out_of_time;

    virtual void run__();

  public:

    ArcadeState(StateConfig n_s_conf);

    virtual void init();

    void afterGame(std::string high_score);
    int calculateScore() const;

    virtual void printCorrectAnswer();
    virtual void printWrongAnswer();

};

#endif
