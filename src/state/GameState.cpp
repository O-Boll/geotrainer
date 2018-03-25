#include <fstream>
#include <vector>

#include "GameState.h"
#include "../misc/StrFcns.h"

GameState::~GameState() {}

bool GameState::run_() {
  run__();
  g_gui.handleEvents();
  g_gui.step();
  g_gui.draw();
  return !GUI::getCloseGUI();
}

bool GameState::changeState() const {
  return g_gui.getCloseGUI();
}

StateConfig GameState::getStateConfig() {
  s_conf.state = StateConfig::menu;
  return s_conf;
}

int GameState::getMinHighScore(std::string f_name) const {
  int min_high_score = INT_MIN, n = 0;
  std::ifstream is(f_name.c_str());
  if(is.is_open()) {
    std::string name, s_score;
    while(getline(is, name) && getline(is, s_score)) { n++; }
    if(n >= 3 && s_score.size() != 0)
      min_high_score = strfcns::stoi(s_score);
    is.close();
  }
  return min_high_score;
}

string GameState::updateHighScore(std::string name, std::string f_name) const {
  std::string s_ret;
  if(!std::ifstream(f_name.c_str()))
    std::ofstream(f_name.c_str());
  std::ifstream is(f_name.c_str());
  if(is.is_open()) {
    bool score_saved = false;
    std::string _name, s_score, l;
    std::string pos[3] = {"1st", "2nd", "3rd"};
    int n = 0;
    while(getline(is, _name) && getline(is, s_score) && n < 3) {
      if(score > strfcns::stoi(s_score) && score_saved == false) {
        l += name + "\n" + strfcns::itos(score) + "\n";
        s_ret += pos[n] + ": " + name + " " + strfcns::itos(score) + "pts, ";
        n++;
        score_saved = true;
        if(n >= 3)
          break;
      }
      l += _name + "\n" + s_score + "\n";
      s_ret += pos[n] + ": " + _name + " " + s_score + "pts, ";
      n++;
    }
    if(n < 3 && score_saved == false) {
      l += name + "\n" + strfcns::itos(score) + "\n";
      s_ret += pos[n] + ": " + name + " " + strfcns::itos(score) + "pts, ";
    }
    if(s_ret.size() > 2) { /* Överflödig if-sats? */
      s_ret.erase(s_ret.end() - 2, s_ret.end());
      s_ret += ".";
    }
    is.close();
    std::ofstream os(f_name.c_str(), ios::trunc);
    if(os.is_open()) {
      os << l;
      os.close();
    }
  }
  return s_ret;
}

bool GameState::answerExists() const {
  if(   (regionSearch() && !g_gui.noChosenRegion())
     || (citySearch()   && !g_gui.noChosenCities()) ) {
    return true;

  }
  return false;
}

bool GameState::answerCorrect() const {
  int r = g_gui.getNumberOfRegions();
  if(correct_answer < r) { /* i.e. if we are looking for a region */
    if(g_gui.isChosenRegion(correct_answer)) {
      Sounds::playCorrectAnswerSound();
      return true;
    }
  }
  else {
    if(g_gui.isChosenCity(correct_answer - r)) {
      Sounds::playCorrectAnswerSound();
      return true;
    }
  }
  Sounds::playWrongAnswerSound();
  return false;
}

void GameState::clearQuestions() {
  questions.empty();
}

void GameState::addQuestion(int q) {
  int c = g_gui.getNumberOfCities();
  int r = g_gui.getNumberOfRegions();
  if(q >= 0 && q < c + r)
    questions.add(q);
}

void GameState::activateAllQuestions() {
  int c = g_gui.getNumberOfCities();
  int r = g_gui.getNumberOfRegions();
  for(int i = 0; i < c + r; i++)
    questions.add(i);
}

int GameState::getUnusedQuestion() const {
  int q = -1; /* default value */
  int c = g_gui.getNumberOfCities();
  int r = g_gui.getNumberOfRegions();
  int* unusedQuestions = new int[c + r];
  int n = 0;
  for(int i = 0; i < c + r; i++) {
    if(!questions.isMember(i)) {
      unusedQuestions[n] = i;
      n++;
    }
  }
  q = unusedQuestions[rand() % n];
  delete[] unusedQuestions;
  return q;
}

int GameState::numberOfUnusedQuestions() const {
  int c = g_gui.getNumberOfCities();
  int r = g_gui.getNumberOfRegions();
  int n = 0;
  for(int i = 0; i < c + r; i++) {
    if(!questions.isMember(i))
      n++;
  }
  return n;
}

std::string GameState::getQuestionName(int q) const {
  if(q == -1) /* i.e. if q is not a question */
    return "";
  int r = g_gui.getNumberOfRegions();
  if(q < r)
    return g_gui.getRegionName(q);
  else
    return g_gui.getCityName(q - r);
}

int GameState::getQuestionXCoordinate(int q) const {
  if(q == -1) /* i.e. if q is not a question */
    return 0;
  int r = g_gui.getNumberOfRegions();
  if(q < r)
    return g_gui.getRegionXCoordinate(q);
  else
    return g_gui.getCityXCoordinate(q - r);
}

int GameState::getQuestionYCoordinate(int q) const {
  if(q == -1) /* i.e. if q is not a question */
    return 0;
  int r = g_gui.getNumberOfRegions();
  if(q < r)
    return g_gui.getRegionYCoordinate(q);
  else
    return g_gui.getCityYCoordinate(q - r);
}

void GameState::generateNewQuestion() {
  if(questions.size() == 0) {
    correct_answer = -1; /* default value */
    return;
  }
  correct_answer = questions.pick();
  bool is_region = correct_answer < g_gui.getNumberOfRegions();
  if(is_region) /* if a region gets picked */
    setRegionSearch();
  else /* if a city gets picked */
    setCitySearch();
}

void GameState::setCitySearch() {
  g_gui.setSearchMode(2);
}

void GameState::setRegionSearch() {
  g_gui.setSearchMode(1);
}

bool GameState::regionSearch() const {
  return correct_answer < g_gui.getNumberOfRegions();
}

bool GameState::citySearch() const {
  return !regionSearch();
}

void GameState::flashBeacon(int q, int time) {
  if(q == -1) /* i.e. if q is not a question */
    return;
  int r = g_gui.getNumberOfRegions();
  if(q < r)
    g_gui.regionBeacon(q, time, 0x000000);
  else {
    std::vector<int> q_v;
    q_v.push_back(q - r);
    g_gui.cityBeacon(q_v, time, 0x000000);
  }
}

void GameState::resetButtons() {
  g_gui.resetHelpButton();
  g_gui.resetPlusButton();
}

void GameState::printQuestion() {
  std::string s;
  s = "Find " + getQuestionName(correct_answer) + "!";
  g_gui.printMain(s, 100000.0, 0xFFFFFF);
}

void GameState::printNoMoreQuestions() {
  int c = g_gui.getNumberOfCities();
  int r = g_gui.getNumberOfRegions();
  g_gui.printMain("All cities (" + strfcns::itos(r)
                  + ") cities and all regions ("
                  + strfcns::itos(c) + ") have already been added!",
                    2.0, 0xff0000);
}

void GameState::printTimeLeft() {
  int seconds_left = timer.getSecondsLeft();
  if (seconds_left >= 10) {
    g_gui.printTime(seconds_left);
  }
  else {
    g_gui.printTime(seconds_left, 0xff0000);
  }
}

void GameState::correctBeacon() {
  if (citySearch()) {
    std::vector<int> city_v;
    int r = g_gui.getNumberOfRegions();
    city_v.push_back(correct_answer - r);
    g_gui.cityBeacon(city_v, 1.0, 1);
    city_v.clear();
  }
  else if (regionSearch()) {
    g_gui.regionBeacon(g_gui.getChosenRegion(), 1.0, 0x000000);
  }
}

void GameState::wrongBeacon() {
  if (citySearch()) {
    std::vector<int> v = g_gui.getChosenCities();
    g_gui.cityBeacon(v, 1.0, 1);
    v.clear();
  }
  else if (regionSearch()) {
    g_gui.regionBeacon(g_gui.getChosenRegion(), 1.0, 0xff0000);
  }
}
