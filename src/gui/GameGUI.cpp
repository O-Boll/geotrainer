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

#include <fstream> 

#include "GameGUI.h"
#include "../misc/StrFcns.h"

GameGUI::GameGUI() {}

GameGUI::GameGUI(std::string n_map_name, int n_game_mode) {

  main_ts = Typesetter(s_screen, width, height, &def_tw);
  main_ts.setBox(5, 0, width - 10, height);
  main_ts.setSlowTyping(slow_typing);
  time_ts = Typesetter(s_screen, width, height, &def_tw);
  time_ts.setBox(5, height - 25, 50, 25);

  particles = Particles(s_screen, width, height);

  selected_region = -1; chosen_region = -1;
  mouse_x = 0; mouse_y = 0;
  scroll_x = 0; scroll_y = 0;
  selected_x = 0; selected_y = 0;
  city_select_distance = 10;
  run_game = true;
  help_button_pressed = false;
  plus_button_pressed = false;
  setSearchMode(0);
  unlockInput();
  turnDialogOff();
  setMousePosition(width / 2, height / 2);
  game_mode = n_game_mode;
  map_name = n_map_name;
  startGame(n_map_name);
}

GameGUI::~GameGUI() {
  Sounds::haltSound();
}

void GameGUI::startGame(std::string map_name) {
  resetSelection();
  std::string f_name;
  f_name = "MAPS/" + map_name + "/" + map_name + "_regions.bmp";
  loadRegionMap(f_name);
  f_name = "MAPS/" + map_name + "/" + map_name + "_regions.txt";
  loadRegionInfo(f_name);
  f_name = "MAPS/" + map_name + "/" + map_name + "_cities.bmp";
  loadCityCoordinates(f_name);
  f_name = "MAPS/" + map_name + "/" + map_name + "_cities.txt";
  loadCityNames(f_name);
  /* center mouse position */
  setMousePosition(width / 2, height / 2);
  scroll_x = -(mouse_x * (region_map.getWidth() - width)) / width;
  scroll_y = -(mouse_y * (region_map.getHeight() - height)) / height;

  run_game = true;
}

void GameGUI::loadRegionMap(std::string f_name) {
  region_map.loadRegionBMP(f_name.c_str(), region_center_x, region_center_y);
}

void GameGUI::loadRegionInfo(std::string f_name) {
  region_info.clear();
  std::ifstream c_file(f_name);
  std::string line;
  while (std::getline(c_file, line))
    region_info.push_back(line);
}

void GameGUI::loadCityCoordinates(std::string f_name) {
  city_info.clear();
  Img* coord_map = new Img();
  coord_map->loadBMP(f_name.c_str());
  if(coord_map == 0)
    return;
  Uint32* pixels = coord_map->getPixels();
  int s = coord_map->getWidth() * coord_map->getHeight();
  int n_coords = 0;
  for(int i = 0; i < s; i++) {
    if((pixels[i] & 0x00FFFFFF) != 0x00FFFFFF) { n_coords++; }
  }
  while((int) city_info.size() < n_coords)
    city_info.push_back(City(0, 0, ""));
  for(int i = 0; i < s; i++) {
    Uint32 n = pixels[i] & 0x00FFFFFF;
    if(n != 0x00FFFFFF) {
      int x = i % coord_map->getWidth();
      int y = i / coord_map->getWidth();
      city_info[n].setCoordinates(x, y);
    }
  }
  delete coord_map;
}

void GameGUI::loadCityNames(std::string f_name) {
  std::ifstream c_file(f_name.c_str());
  if(!c_file)
    return;
  std::string line;
  int n = 0;
  while (std::getline(c_file, line)) {
    if(n < (int) city_info.size())
      city_info[n].setName(line);
    else
      city_info.push_back(City(0, 0, line));
    n++;
  }
}

void GameGUI::step() {
  main_ts.step();
  time_ts.step();
  palette.step();
  particles.setOffset(scroll_x, scroll_y);
  particles.step();
}

void GameGUI::draw() {
  drawRegionMap();
  drawCities();
  particles.draw();

  if(mouse_y < main_ts.getTextHeight() + 10) {
    main_ts.type();
  }
  else {
    main_ts.type();
  }
  if(   mouse_y > height - time_ts.getTextHeight() - 25
     && mouse_x <          time_ts.getTextWidth()  + 25)
    time_ts.type();
  else
    time_ts.type();

  drawCursor();
  render(-scale * scroll_x, -scale * scroll_y);
}

void GameGUI::drawCities() {
  for(int i = 0; i < (int) city_info.size(); i++) {
    City c = city_info[i];
    int x = c.getXCoordinate() + scroll_x;
    int y = c.getYCoordinate() + scroll_y;
    unsigned int flags = 0x0000;
    if(isSelectedCity(i) && searchCities()) {
      flags += Palette::CITY_IS_SELECTED;
    }
    if(mouseOverCity(i) && searchCities()) {
      flags += Palette::CITY_IS_ACTIVE;
    }
    Img *c_sym = palette.getCitySymbol(i, flags);
    if(c_sym != 0) {
      int offset = c_sym->getWidth() / 2;
      drawImg(c_sym, x - offset, y - offset);
    }
  }
}

void GameGUI::drawImg(const Img *Im, int x, int y) {
  if(Im == 0) { return; }
  int high = y + Im->getHeight();
  if(high > height) { high = height; }
  int start_v = 0;
  int low = y;
  if(low < 0) { start_v = -low; low = 0; }
  int left = x;
  int start_u = 0;
  if(left < 0) { start_u = -left; left = 0; }
  int right = x + Im->getWidth();
  if(right > width) { right = width; }
  int v = start_v;
  int u_add = 1;
  for(int cy = low; cy < high; cy++) {
    int u = start_u;
    for(int cx = left; cx < right; cx++) {
      Uint32 color = Im->getPixelAt(u, v);
      if(color != 0xFF00FF00) { s_screen[cy * width + cx] = color, s_screen[cy * width + cx]; }
      u += u_add;
    }
    v++;
  }
}

void GameGUI::drawRegionMap() {
  int x = scroll_x; int y = scroll_y;
  for(int j = 0; j < region_map.getHeight(); j++) {
    for(int i = 0; i < region_map.getWidth(); i++) {
      if(i + x >= 0 && i + x < width && j + y >= 0 && j + y < height) {
        int cur_x = i + x;
        int cur_y = j + y;
        int region_number = getRegionNumber(cur_x, cur_y);
        unsigned int flags = 0x0000;
        if(isSelectedRegion(region_number) && searchRegions()) {
          flags += Palette::IS_SELECTED;
        }
        else if(mouseOverRegion(region_number) && searchRegions()) {
          flags += Palette::IS_ACTIVE;
        }
        if(region_map.isBorder(i, j, palette.getBorderMode())) {
          flags += Palette::IS_BORDER;
        }
        s_screen[(j + y) * width + i + x] = palette.getColor(region_number, i, j, flags);
      }
    }
  }
}

char GameGUI::readInput(SDL_Keycode k) {
  if     (k == SDLK_0) return '0';
  else if(k == SDLK_1) return '1';
  else if(k == SDLK_2) return '2';
  else if(k == SDLK_3) return '3';
  else if(k == SDLK_4) return '4';
  else if(k == SDLK_5) return '5';
  else if(k == SDLK_6) return '6';
  else if(k == SDLK_7) return '7';
  else if(k == SDLK_8) return '8';
  else if(k == SDLK_9) return '9';
  else if(k == SDLK_a) return 'A';
  else if(k == SDLK_b) return 'B';
  else if(k == SDLK_c) return 'C';
  else if(k == SDLK_d) return 'D';
  else if(k == SDLK_e) return 'E';
  else if(k == SDLK_f) return 'F';
  else if(k == SDLK_g) return 'G';
  else if(k == SDLK_h) return 'H';
  else if(k == SDLK_i) return 'I';
  else if(k == SDLK_j) return 'J';
  else if(k == SDLK_k) return 'K';
  else if(k == SDLK_l) return 'L';
  else if(k == SDLK_m) return 'M';
  else if(k == SDLK_n) return 'N';
  else if(k == SDLK_o) return 'O';
  else if(k == SDLK_p) return 'P';
  else if(k == SDLK_q) return 'Q';
  else if(k == SDLK_r) return 'R';
  else if(k == SDLK_s) return 'S';
  else if(k == SDLK_t) return 'T';
  else if(k == SDLK_u) return 'U';
  else if(k == SDLK_v) return 'V';
  else if(k == SDLK_w) return 'W';
  else if(k == SDLK_x) return 'X';
  else if(k == SDLK_y) return 'Y';
  else if(k == SDLK_z) return 'Z';
  else if(k == SDLK_SPACE) return ' ';
  else if(k == SDLK_COMMA) return ',';
  else if(k == SDLK_PERIOD) return '.';
  /* ATT GÖRA: KOMPLETTERA OVANSTÅENDE LISTA AV KEYCODES */
  else if(k == SDLK_BACKSPACE) return 1;
  return 0;
}

void GameGUI::handleEvents() {
  while(SDL_PollEvent(&event)){
    if(event.type == SDL_QUIT)
      cont = false;
    else if (event.type == SDL_KEYDOWN) {
      SDL_Keycode cur_key = event.key.keysym.sym;
      if       (cur_key == SDLK_ESCAPE ) { startMenu(); break; }
      else if (dialogOn()) {
        if     (cur_key == SDLK_RETURN ) { dialog_ok = true; }
        else if(cur_key == SDLK_ESCAPE ) { dialog_no = true; }
        if(input_dialog_on) {
          char c = readInput(cur_key);
          if(c == 1) {
            if(input_dialog_input.size() > 0)
              input_dialog_input.erase(input_dialog_input.end() - 1,
                                       input_dialog_input.end());
          }
          else if(c != 0) {
            if(input_dialog_input.size() < input_dialog_max_input_length)
              input_dialog_input += c;
            else if(input_dialog_max_input_length > 0)
              input_dialog_input[input_dialog_max_input_length - 1] = c;
          }
          if(c != 0) {
            main_ts.removeLine(main_ts.getNumberOfLines() - 1);
            printMain(input_dialog_input, 100000.0, 0xFFFFFFFF);
          }
        }
      }
      else if (isLocked()              ) { }
      else if (cur_key == SDLK_h       ) { help_button_pressed = true;    }
      else if (cur_key == SDLK_PLUS ||
               cur_key == SDLK_KP_PLUS ) { plus_button_pressed = true;    }
    }
    if(isLocked()) { }
    else if(event.type == SDL_MOUSEMOTION    ) { handleMouseMotion(); }
    else if(event.type == SDL_MOUSEBUTTONDOWN && dialogOn() == false) {
      handleMouseButtonDown();
      chosen_region = selected_region;
      selected_region = -1;
      chosen_cities.clear();
      chosen_cities = selected_cities;
    }
  }
}

void GameGUI::setMousePosition(int x, int y) {
  GUI::setMousePosition(x, y);
  setScroll();
}

void GameGUI::handleMouseMotion() {
  int win_w, win_h;
  SDL_GetWindowSize(win ,&win_w, &win_h);
  mouse_x = (event.motion.x * width) / win_w;
  mouse_y = (event.motion.y * height) / win_h;
  setScroll();
}

void GameGUI::setScroll() {
    scroll_x = -(mouse_x * (region_map.getWidth() - width)) / width;
    scroll_y = -(mouse_y * (region_map.getHeight() - height)) / height;
}

void GameGUI::handleMouseButtonDown() {
  selected_x = mouse_x - scroll_x; selected_y = mouse_y - scroll_y;

  int region_number = getRegionNumber(mouse_x, mouse_y);
  if(region_number >= 0 && region_number == selected_region) {
    selected_region = -1;
  }
  else if(region_number >= 0 && region_number < (int) region_info.size()) {
    selected_region = region_number;
  }
  else { selected_region = -1; }
  selected_cities.clear();
  selected_cities = getCityNumbers(mouse_x, mouse_y);
}

int GameGUI::getRegionNumber(int rel_x, int rel_y) const {
  int region_number = -1;
  int x = rel_x - scroll_x;
  int y = rel_y - scroll_y;
  if(x >= 0 && x < region_map.getWidth()
            && y >= 0 && y < region_map.getHeight()) {
    region_number = (int) ((region_map.getPixelAt(x, y) << 8) >> 8);
  }
  if(region_number == 0xFF00)      { region_number = -1; }
  else if(region_number == 0x9900) { region_number = -2; }
  return region_number;
}

bool GameGUI::mouseOverRegion(int region_number) const {
  if(region_number >= 0 && region_number == getRegionNumber(mouse_x, mouse_y))
    return true;
  return false;
}

std::string GameGUI::getRegionName(int region_number) const {
  if(region_number >= 0 && region_number < (int) region_info.size())
    return region_info[region_number];
  return 0;
}

int GameGUI::getRegionXCoordinate(int region_number) const {
  return (region_center_x[region_number] * width) / region_map.getWidth();
}

int GameGUI::getRegionYCoordinate(int region_number) const {
  return (region_center_y[region_number] * height) / region_map.getHeight();
}

std::vector<int> GameGUI::getCityNumbers(int rel_x, int rel_y) const {
  std::vector<int> c_numbers;
  int max_dist = city_select_distance;
  int x = rel_x - scroll_x;
  int y = rel_y - scroll_y;
  for(int i = 0; i < (int) city_info.size(); i++) {
    City c = city_info[i];
    int sqr_dist = (x - c.getXCoordinate()) * (x - c.getXCoordinate()) +
                   (y - c.getYCoordinate()) * (y - c.getYCoordinate());
    if(sqr_dist <= max_dist * max_dist) { c_numbers.push_back(i); }
  }
  return c_numbers;
}

bool GameGUI::mouseOverCity(int city_number) const {
  std::vector<int> temp_v = getCityNumbers(mouse_x, mouse_y);
  for(int i = 0; i < temp_v.size(); i++)
    if(temp_v[i] == city_number)
      return true;
  return false;
}

bool GameGUI::noChosenCities() const {
  return chosen_cities.empty();
}

bool GameGUI::isSelectedCity(int city_number) const {
  for(int i = 0; i < selected_cities.size(); i++)
    if(selected_cities[i] == city_number)
      return true;
  return false;
}

bool GameGUI::isChosenCity(int city_number) const {
  for(int i = 0; i < chosen_cities.size(); i++)
    if(chosen_cities[i] == city_number)
      return true;
  return false;
}

std::vector<int> GameGUI::getChosenCities() const {
  std::vector<int> cc_copy = chosen_cities;
  return cc_copy;
}

void GameGUI::deselectCities() {
  selected_cities.clear();
  chosen_cities.clear();
}

std::string GameGUI::getCityName(int city_number) const {
  if(city_number >= 0 && city_number < (int) city_info.size())
    return city_info[city_number].getName();;
  return 0;
}

int GameGUI::getCityXCoordinate(int city_number) const {
  return (city_info[city_number].getXCoordinate() * width)
         / region_map.getWidth();
}

int GameGUI::getCityYCoordinate(int city_number) const {
  return (city_info[city_number].getYCoordinate() * height)
         / region_map.getHeight();
}

void GameGUI::alertDialog(std::string message, std::string s) {
  turnDialogOff(); /* reset */
  printMain(message + " " + s, 100000.0, 0xFFFFFFFF);
  alert_dialog_on = true;
}

void GameGUI::alertDialog(std::string message) {
  alertDialog(message, " Press Return to continue.");
}

void GameGUI::inputDialog(std::string message, unsigned int max_length) {
  turnDialogOff(); /* reset */
  printMain(message, 100000.0, 0xFFFFFFFF);
  input_dialog_on = true;
  input_dialog_input = "";
  input_dialog_max_input_length = max_length;
  printMain(input_dialog_input, 100000.0, 0xFFFFFFFF);
}

void GameGUI::inputDialog(std::string message) {
  inputDialog(message, 100000.0);
}

void GameGUI::yesNoDialog(std::string message, std::string s) {
  turnDialogOff(); /* reset */
  printMain(message + " " + s, 100000.0, 0xFFFFFFFF);
  yes_no_dialog_on = true;
}

void GameGUI::yesNoDialog(std::string message) {
  yesNoDialog(message, " Press Return to continue or Esc to exit.");
}

bool GameGUI::dialogOK() {
  return dialog_ok;
}

std::string GameGUI::dialogInput() {
 return input_dialog_input;
}

bool GameGUI::dialogNo() {
  return dialog_no && yes_no_dialog_on;
}

void GameGUI::turnDialogOff() {
  clearMain();
  alert_dialog_on = input_dialog_on
                  = yes_no_dialog_on = dialog_ok = dialog_no = false;
}

bool GameGUI::dialogOn() {
  return alert_dialog_on || input_dialog_on || yes_no_dialog_on;
}

bool GameGUI::helpButtonPressed() const {
  return help_button_pressed;
}

void GameGUI::resetHelpButton() {
  help_button_pressed = false;
}

bool GameGUI::plusButtonPressed() const {
  return plus_button_pressed;
}

void GameGUI::resetPlusButton() {
  plus_button_pressed = false;
}

void GameGUI::printMain(std::string s, double life, Uint32 color) {
  main_ts.addLine(s, life, color);
}

void GameGUI::clearMain() {
  main_ts.clearLines();
}

void GameGUI::printTime(int t, Uint32 color) {
  time_ts.clearLines(); time_ts.addLine(strfcns::itos(t), 100000.0, color);
}

void GameGUI::printTime(int t) {
  time_ts.clearLines(); time_ts.addLine(strfcns::itos(t));
}

void GameGUI::regionBeacon(int region_number, double time, Uint32 color) {

  palette.setBeacon(region_number, time, color);
}

void GameGUI::cityBeacon(std::vector<int> city_numbers, double time, int symbol) {

  palette.setCityBeacon(city_numbers, time, symbol);
}

void GameGUI::createParticles(uint32_t n) {
  particles.create(selected_x, selected_y, n);
}

std::string GameGUI::getMapName() const {
  return map_name;
}

bool GameGUI::noChosenRegion() const {
  return chosen_region == -1;
}

bool GameGUI::isSelectedRegion(int region_number) const {
                    // != -1 ???
  return region_number >= 0 && selected_region == region_number;
}

bool GameGUI::isChosenRegion(int region_number) const {
                    // != -1 ???
  return region_number >= 0 && chosen_region == region_number;
}

int GameGUI::getChosenRegion() const {
  return chosen_region;
}

void GameGUI::deselectRegion() {
  selected_region = -1;
  chosen_region = -1;
}

int GameGUI::getNumberOfRegions() const {
  return region_info.size();
}

int GameGUI::getNumberOfCities() const {
  return city_info.size();
}

int GameGUI::getGameState() const {
  return game_state;
}

void GameGUI::setCitySelectDistance(int d) {
  city_select_distance = d;
}

void GameGUI::setSearchMode(int m) {
  search_mode = m;
}

bool GameGUI::searchRegions() const {
  if(search_mode == 0 || search_mode == 1)
    return true;
  return false;
}

bool GameGUI::searchCities() const {
  if(search_mode == 0 || search_mode == 2)
    return true;
  return false;
}

void GameGUI::resetSelection() {
  selected_region = -1;
  chosen_region = -1;
  selected_cities.clear();
  chosen_cities.clear();
}

void GameGUI::lockInput() {
  lock_input = true;
}

void GameGUI::unlockInput() {
  lock_input = false;
}

bool GameGUI::isLocked() const {
  if(lock_input )
    return true;
  return false;
}

bool GameGUI::getCloseGUI() const {
  return !run_game;
}

void GameGUI::startMenu() {
  regionBeacon(selected_region, 0.0, 0);
  cityBeacon(selected_cities, 0.0, 0);
  resetSelection();
  run_game = false;
}
