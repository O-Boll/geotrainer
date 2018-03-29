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

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>

#include "State.h"
#include "../gui/GameGUI.h"
#include "../misc/MessySet.h"
#include "../timer/Timer.h"

class GameState : public State {

  protected:

    GameGUI g_gui;
    MessySet<int> questions;
    Timer timer;

    int correct_answer;
    int score;
    int tries;
    int anim_dest,
        anim_old_x,
        anim_old_y,
        anim_new_x,
        anim_new_y;
    double anim_time;

    virtual bool run_();
    virtual void run__() = 0;

  public:

    enum gmode {undefined = -1, menu = 0, arcade = 1, edu = 2, tt = 3};

    virtual ~GameState();


    virtual void init() = 0;
    virtual bool changeState() const;
    virtual StateConfig getStateConfig();

    int getMinHighScore(std::string f_name) const;
    std::string updateHighScore(std::string name, std::string f_name) const;

    bool answerExists() const;
    bool answerCorrect() const;
    void clearQuestions();
    void addQuestion(int q);
    void activateAllQuestions();
    int getUnusedQuestion() const; /* returns -1 if no such question exist */
    int numberOfUnusedQuestions() const;
    void generateNewQuestion();
    std::string getQuestionName(int q) const;
    int getQuestionXCoordinate(int q) const;
    int getQuestionYCoordinate(int q) const;

    void setCitySearch();
    void setRegionSearch();
    bool regionSearch() const;
    bool citySearch() const;
    void flashBeacon(int region_number, int time);
    void resetButtons();

    void printQuestion();
    virtual void printCorrectAnswer() = 0;
    virtual void printWrongAnswer() = 0;
    void printNoMoreQuestions();
    void printTimeLeft();
    void correctBeacon();
    void wrongBeacon();

};

#endif
