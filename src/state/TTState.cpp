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

#include "TTState.h"
#include "../misc/StrFcns.h"

TTState::TTState(StateConfig n_s_conf) {
  s_conf = n_s_conf;
  g_gui = GameGUI(s_conf.map_name, s_conf.game_mode);
  init();
}

void TTState::init() {
  score = 0;
  tries = 0;
  correct_answer = -1;
  streak = 0;
  out_of_time = false;
  clearQuestions();
  activateAllQuestions();
  timer.setTimer(0.0);
  timer.freeze();
  g_gui.resetSelection();
  g_gui.alertDialog("Welcome to Time Trial and the "
                    + g_gui.getMapName()
                    + " map. Ready, set...",
                    "Press Return to start game.");
}

void TTState::run__() {
  static bool high_score_updated = false;
  static int current_min_high_score = INT_MIN;
  static std::string high_score;
  if (g_gui.dialogOK() && !timer.isExpired()) {
    g_gui.turnDialogOff();
    timer.setTimer(30.9);
    timer.thaw();
    high_score_updated = false;
    high_score = "";
    current_min_high_score = getMinHighScore("MAPS/" + g_gui.getMapName()
                                             + "/tths.txt");
    generateNewQuestion();
    printQuestion();
    g_gui.resetSelection();
  }
  else if(timer.isExpired()) {
    if(!high_score_updated && current_min_high_score < score) {
      if(!g_gui.dialogOn())
        g_gui.inputDialog(strfcns::itos(score)
             + " points is a new high score! Please enter your name:", 10);
      else if(g_gui.dialogOK()) {
        g_gui.turnDialogOff();
        high_score = updateHighScore(g_gui.dialogInput(),
                                     "MAPS/" + g_gui.getMapName()
                                     + "/tths.txt");
        high_score_updated = true;
      }
    }
    else {
      afterGame(high_score);
      high_score = "";
    }
  }
  else if(g_gui.dialogOn() == false) {
    if(answerExists() && answerCorrect()) {
      streak++;
      score++;
      printCorrectAnswer();
      generateNewQuestion();
      printQuestion();
      g_gui.resetSelection();
    }
    else if(answerExists() && !answerCorrect()) {
      streak = 0;
      score--;
      printWrongAnswer();
      g_gui.resetSelection();
    }
  }
  printTimeLeft();
}

void TTState::afterGame(std::string high_score) {
  if(g_gui.dialogOn()) {
    if(g_gui.dialogOK()) {
      init();
    }
    else if(g_gui.dialogNo()) {
      g_gui.startMenu();
    }
  }
  else {
    if(high_score.size() > 0) {
      g_gui.yesNoDialog(high_score);
    }
    else {
      std::string s_s = strfcns::itos(score);
      g_gui.yesNoDialog("Time is up! You scored " + s_s + " points.");
    }
  }
}

void TTState::printCorrectAnswer() {
  g_gui.clearMain();
  correctBeacon();
  std::string s = strfcns::itos(score);
  g_gui.printMain("Correct! +1 point. Total score: " + s + ".", 2.0, 0xFF33FF66);
}

void TTState::printWrongAnswer() {
  wrongBeacon();
  std::string s, name;
  if(citySearch()) name = g_gui.getCityName(g_gui.getChosenCities()[0]);
  else if(regionSearch()) name = g_gui.getRegionName(g_gui.getChosenRegion());
  s = "Wrong! -1 point. Total score: " + strfcns::itos(score) + ".";
  g_gui.printMain(s, 2.0, 0xFFFF0000);
}
