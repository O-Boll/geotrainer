#include <algorithm>

#include "ArcadeState.h"
#include "../misc/StrFcns.h"

ArcadeState::ArcadeState(StateConfig n_s_conf) {
  s_conf = n_s_conf;
  g_gui = GameGUI(s_conf.map_name, s_conf.game_mode);
  init();
}

void ArcadeState::init() {
  score = 0;
  tries = 0;
  correct_answer = -1;
  streak = combo = last_score_time = 0;
  out_of_time = false;
  clearQuestions();
  activateAllQuestions();
  timer.setTimer(0.0);
  timer.freeze();
  g_gui.resetSelection();
  g_gui.alertDialog("Welcome to Arcade Mode and the "
                    + g_gui.getMapName()
                    + " map. Ready, set...",
                    "Press Return to start game.");
}

void ArcadeState::run__() {
  static bool high_score_updated = false;
  static int current_min_high_score = INT_MIN;
  static std::string high_score;
  if(g_gui.dialogOK() && !timer.isExpired()) {
    g_gui.turnDialogOff();
    timer.setTimer(30.9);
    timer.thaw();
    last_frame_elapsed_seconds = timer.getElapsedSeconds();
    high_score_updated = false;
    high_score = "";
    current_min_high_score = getMinHighScore("MAPS/" + g_gui.getMapName()
                                             + "/ahs.txt");
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
                                     "MAPS/" + g_gui.getMapName() + "/ahs.txt");
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
      int last_score_elapsed_time = timer.getElapsedMilliseconds()
                                    - last_score_time;
      if (last_score_elapsed_time <= 2000) {
        combo++;
      } else {
        combo = 1;
      }
      last_score_time = timer.getElapsedMilliseconds();
      streak++;
      score += calculateScore();
      printCorrectAnswer();
      generateNewQuestion();
      printQuestion();
      g_gui.resetSelection();
    }
    else if(answerExists() && !answerCorrect()) {
      score -= 100;
      streak = 0;
      combo = 0;
      printWrongAnswer();
      g_gui.resetSelection();
    }

    /* clock ticking soundg */
    if(timer.getElapsedSeconds() != last_frame_elapsed_seconds)
      Sounds::playTickSound();
    last_frame_elapsed_seconds = timer.getElapsedSeconds();
  }
  printTimeLeft();
}

void ArcadeState::afterGame(std::string high_score) {
  if(g_gui.dialogOn()) {
    if(g_gui.dialogOK()) {
      init();
    }
    else if(g_gui.dialogNo()) {
      g_gui.startMenu();
    }
  }
  else {
    Sounds::playGameOverSound();
    if(high_score.size() > 0) {
      g_gui.yesNoDialog(high_score);
    }
    else {
      std::string s_s = strfcns::itos(score);
      g_gui.yesNoDialog("Time is up! You scored " + s_s + " points.");
    }
  }
}

int ArcadeState::calculateScore() const {
  return combo * (90 + 10 * streak);
}

void ArcadeState::printCorrectAnswer() {
  std::string s;
  g_gui.clearMain();
  correctBeacon();
  std::string s_s = strfcns::itos(score);
  std::string s_t = strfcns::itos(streak);
  std::string s_k = strfcns::itos(combo);
  std::string s_p = strfcns::itos(calculateScore());
  s = "Correct! Streak: " + s_t +
              ". Combo: " + s_k +
                    ". +" + s_p + " points. Total score: "
                          + s_s + ".";
  g_gui.printMain(s, 2.0, 0xFF33ff66);
  g_gui.createParticles(std::min(std::max(calculateScore(), 0), 2000));
}

void ArcadeState::printWrongAnswer() {
  wrongBeacon();
  std::string s, name;
  if(citySearch()) name = g_gui.getCityName(g_gui.getChosenCities()[0]);
  else if(regionSearch()) name = g_gui.getRegionName(g_gui.getChosenRegion());
  s = "Wrong! You chose "
      + name + ". -100 points. Total score: " + strfcns::itos(score) + ".";
  g_gui.printMain(s, 2.0, 0xFFFF0000);
}
