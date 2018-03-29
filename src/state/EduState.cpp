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

#include "EduState.h"
#include "../misc/StrFcns.h"

EduState::EduState(StateConfig n_s_conf) {
  s_conf = n_s_conf;
  g_gui = GameGUI(s_conf.map_name, s_conf.game_mode);
  init();
}

void EduState::init() {
  score = 0;
  tries = 0;
  correct_answer = -1;
  clearQuestions();
  start_screen_on = true;
  animation_on = false;
  string adjectives[6] = {"neat", "pretty", "juicy", "funky", "lovely", "nice"};
  g_gui.alertDialog("Welcome to " + g_gui.getMapName() + "! " +
                    "Whoa, what a " + adjectives[rand() % 6] + " map! " +
                    "Wanna see if you can learn something from it? " +
                    "Let's dig in!");
  instructions = (std::string)
                 "First you will be shown a few cities and/or regions. " +
                 "Your will then be asked to find them one at a time on the map. " +
                 "This is done by clicking. Press h for help, " +
                 "+ for adding more cities and/or regions, " +
                 "Esc for quitting.";
  anim_time = 0.5;
}

void EduState::run__() {
  static bool add_new_question, generate_new_question, continue_screen_on, help_flag;
  if((start_screen_on && g_gui.dialogOK()) /* display instructions first */
      || continue_screen_on) {
    g_gui.turnDialogOff();
    start_screen_on = false;
    continue_screen_on = false;
    instruction_screen_on = true;
    g_gui.alertDialog(instructions);
  }
  else if(instruction_screen_on && g_gui.dialogOK()) { /* after instructions, start off with a few questions */
    g_gui.turnDialogOff();
    instruction_screen_on = false;
    animation_on = true;
    add_questions = min(5, g_gui.getNumberOfCities()
                           + g_gui.getNumberOfRegions()); /* start with (at most) five questions */
    add_new_question = true;
  }
  else if(!instruction_screen_on) {
    if(add_questions > 0) {
      generate_new_question = true; /* now we know that we have to generate a new question later */
      if(!g_gui.isLocked())
        g_gui.lockInput();
      if(add_new_question) {
        add_new_question = false;
        anim_dest = getUnusedQuestion();
        if(anim_dest == -1) /* i.e. if all questions are already activated */
          add_questions = 0;
        else { /* add the new question q then start animation */
          addQuestion(anim_dest);
          anim_old_x = g_gui.getMouseXPosition();
          anim_old_y = g_gui.getMouseYPosition();
          anim_new_x = getQuestionXCoordinate(anim_dest);
          anim_new_y = getQuestionYCoordinate(anim_dest);
          timer.setTimer(anim_time);
        }
      }
      if(!add_new_question) {
        if(g_gui.dialogOn()) {
          if(g_gui.dialogOK()) {
            flashBeacon(anim_dest, 0); /* turns beacon off */
            g_gui.turnDialogOff();
            add_questions--;
            add_new_question = true;
          }
        }
        else {
          double k = timer.getCubicInterpolation();
          g_gui.setMousePosition(anim_old_x + k * (anim_new_x - anim_old_x),
                               anim_old_y + k * (anim_new_y - anim_old_y));
          if(k == 1.0) {
            g_gui.alertDialog("This is " + getQuestionName(anim_dest) + ". Try to remember its location.");
            flashBeacon(anim_dest, 100000.0);
          }
        }

      }
    }
    if(add_questions <= 0 && add_new_question) { /* i.e. stop generating questions */
      g_gui.resetSelection();
      add_new_question = false;
      g_gui.unlockInput();
    }
    if(add_questions <= 0 && !add_new_question) { /* i.e. no more animations: time to play */

      if(generate_new_question) {
        generate_new_question = false;
        help_flag = false;
        generateNewQuestion();
        printQuestion();
      }
      if(answerExists() && answerCorrect()) {
        tries++;
        if(!help_flag)
          score++;
        help_flag = false;
        printCorrectAnswer();
        generateNewQuestion();
        printQuestion();
        g_gui.resetSelection();
      }
      else if(answerExists() && !answerCorrect()) {
        tries++;
        printWrongAnswer();
        g_gui.resetSelection();
      }
      else if(g_gui.helpButtonPressed()) {
        resetButtons();
        help_flag = true;
        flashBeacon(correct_answer, 1.0);
      }
      else if(g_gui.plusButtonPressed()) {
        resetButtons();
        if(numberOfUnusedQuestions() == 0)
          printNoMoreQuestions();
        else {
          instructions = "Let's kick it up a notch and add some more cities and/or regions!";
          add_questions = 4;
          continue_screen_on = true;
        }

      }

    }
  }
}

void EduState::printCorrectAnswer() {
  std::string s;
  g_gui.clearMain();
  correctBeacon();
  double k = 100.0 * double(score) / double(tries);
  std::string percent =   strfcns::itos(int(k)) + "."
                        + strfcns::itos(int(k*10)- int(k) * 10) + "%";
  s = "Correct! " + percent + " right answers w/o help.";
  g_gui.printMain(s, 2.0, 0xFF33FF66);
}

void EduState::printWrongAnswer() {
  wrongBeacon();
  std::string s, name;
  if(citySearch()) name = g_gui.getCityName(g_gui.getChosenCities()[0]);
  else if(regionSearch()) name = g_gui.getRegionName(g_gui.getChosenRegion());
  double k = 100.0 * double(score) / double(tries);
  std::string percent =   strfcns::itos(int(k)) + "."
                        + strfcns::itos(int(k*10) - int(k) * 10) + "%";
  s = "Wrong! You chose "
      + name + ". " + percent + " right answers w/o help.";
  g_gui.printMain(s, 2.0, 0xFFFF0000);
}
