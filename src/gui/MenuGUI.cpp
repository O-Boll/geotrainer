#include <cstring>
#include <fstream>

#include "MenuGUI.h"

const vector<string> MenuGUI::help_text
  (
    {
      "Hello and welcome to GeoTrainer!",
      "1) Playing is simple. Choose your preferred settings in the menu, then click Start Game and follow the instructions on the screen. You will be asked to find cities and/or regions. You answer by clicking.",
      "2) There are three different game modes: Arcade, Educational (Edu) and Time Trial (TT). High scores are kept for Arcade and TT.",
      "3) If you get bored, pressing Esc always takes you back to the menu."
    }
  );

MenuGUI::MenuGUI() {

  left_box      = Box      (
                              s_screen,
                              width,
                              height,
                              5,
                              5,
                              width / 2 - 10,
                              height - 10,
                              0xFF003333,
                              0xFFCCCCCC,
                              1
                           );

  title         = Button   (
                              s_screen,
                              width,
                              height,
                              8,
                              8,
                              width / 2 - 16,
                              26,
                              0xFF006666,
                              0xFF006666,
                              0xFFCCCCCC,
                              "GeoTrainer",
                              &def_tw
                           );

  help_button   = Button   (
                              s_screen,
                              width,
                              height,
                              width / 2 - 32,
                              11,
                              18,
                              18,
                              0xFF006666,
                              0xFF003333,
                              0xFFCCCCCC,
                              "?",
                              &def_tw
                           );

  left_menu     = ButtonBox(
                              s_screen,
                              width,
                              height,
                              8,
                              36,
                              width / 2 - 16,
                              height - 62,
                              0xFF006666,
                              0xFF003333,
                              0xFFCCCCCC,
                              &small_tw
                           );

  quit_button   = Button   (
                              s_screen,
                              width,
                              height,
                              8,
                              156,
                              (width / 2 - 16) / 2 - 2,
                              16,
                              0xFF006666,
                              0xFF003333,
                              0xFFCCCCCC,
                              "Quit Game",
                              &small_tw
                           );

  settings_button
                = Button   (
                              s_screen,
                              width,
                              height,
                              8 + (width / 2 - 16) / 2 + 2,
                              156,
                              ((width / 2 - 16) - 2) / 2 - 1,
                              16,
                              0xFF006666,
                              0xFF003333,
                              0xFFCCCCCC,
                              "Settings",
                              &small_tw
                           );

  right_box     = Box      (
                              s_screen,
                              width,
                              height,
                              width / 2 + 5,
                              5,
                              width / 2 - 10,
                              height - 10,
                              0xFF003333,
                              0xFFCCCCCC,
                              1
                           );

  map_box       = Box      (
                              s_screen,
                              width,
                              height,
                              width / 2 + 8,
                              8,
                              width / 2 - 16,
                              82,
                              0xFF00FF00,
                              0xFFCCCCCC,
                              2
                           );

  arcade_button = Button   (
                              s_screen,
                              width,
                              height,
                              width / 2 + 8,
                              92,
                              45,
                              16,
                              0xFF006666,
                              0xFF003333,
                              0xFFCCCCCC,
                              "Arcade",
                              &small_tw
                           );

  edu_button    = Button   (
                              s_screen,
                              width,
                              height,
                              width / 2 + 58,
                              92,
                              44,
                              16,
                              0xFF006666,
                              0xFF003333,
                              0xFFCCCCCC,
                              "Edu",
                              &small_tw
                           );

  tt_button     = Button   (
                              s_screen,
                              width,
                              height,
                              width / 2 + 107,
                              92,
                              45,
                              16,
                              0xFF006666,
                              0xFF003333,
                              0xFFCCCCCC,
                              "TT",
                              &small_tw
                           );

  info_box      = TextBox  (
                              s_screen,
                              width,
                              height,
                              width / 2 + 8,
                              110,
                              width / 2 - 16,
                              44,
                              0xFF006666,
                              0xFFCCCCCC,
                              2,
                              &tiny_tw
                           );

  start_button  = Button   (
                              s_screen,
                              width,
                              height,
                              width / 2 + 8,
                              156,
                              width / 2 - 16,
                              16,
                              0xFF006666,
                              0xFF003333,
                              0xFFCCCCCC,
                              "Start Game",
                              &small_tw
                           );

  help_box      = Box      (
                              s_screen,
                              width,
                              height,
                              20,
                              20,
                              width - 40,
                              height - 40,
                              0xFF003333,
                              0xFFCCCCCC,
                              1
                           );

  help_box      = Box      (
                              s_screen,
                              width,
                              height,
                              20,
                              20,
                              width - 40,
                              height - 40,
                              0xFF003333,
                              0xFFCCCCCC,
                              1
                           );

  help_text_box = TextBox  (
                              s_screen,
                              width,
                              height,
                              23,
                              23,
                              width - 46,
                              height - 46,
                              0xFF006666,
                              0xFFCCCCCC,
                              2,
                              &tiny_tw
                           );
  for(auto s : help_text)
    help_text_box.addLine(s, -1);

  settings_box  = Box      (
                              s_screen,
                              width,
                              height,
                              20,
                              20,
                              width - 40,
                              height - 40,
                              0xFF003333,
                              0xFFCCCCCC,
                              1
                           );

  palette_menu = ButtonBox (
                              s_screen,
                              width,
                              height,
                              23,
                              23,
                              (width - 46) / 2 - 1,
                              height - 46,
                              0xFF006666,
                              0xFF003333,
                              0xFFCCCCCC,
                              &small_tw
                           );
  for(auto s : palette.getPaletteNames())
    palette_menu.addButton(s);

  canvas_filter_button
                = Button   (
                              s_screen,
                              width,
                              height,
                              width / 2 + 1,
                              23 + (height - 40 - 16 - 2 * 3) * 0 / 5,
                              (width - 46) / 2 - 1,
                              16,
                              0xFF006666,
                              0xFF003333,
                              0xFFCCCCCC,
                              "Canvas Filter",
                              &small_tw
                           );
  if(canvas_filter.isActive())
    canvas_filter_button.setToggle(Button::on);
  else
    canvas_filter_button.setToggle(Button::off);

  median_filter_button
                = Button   (
                              s_screen,
                              width,
                              height,
                              width / 2 + 1,
                              23 + (height - 40 - 16 - 2 * 3) * 1 / 5,
                              (width - 46) / 2 - 1,
                              16,
                              0xFF006666,
                              0xFF003333,
                              0xFFCCCCCC,
                              "Median Filter",
                              &small_tw
                           );
  if(median_filter.isActive())
    median_filter_button.setToggle(Button::on);
  else
    median_filter_button.setToggle(Button::off);

  slow_typing_button
                = Button   (
                              s_screen,
                              width,
                              height,
                              width / 2 + 1,
                              23 + (height - 40 - 16 - 2 * 3) * 2 / 5,
                              (width - 46) / 2 - 1,
                              16,
                              0xFF006666,
                              0xFF003333,
                              0xFFCCCCCC,
                              "Slow Typing",
                              &small_tw
                           );
  if(slow_typing)
    slow_typing_button.setToggle(Button::on);
  else
    slow_typing_button.setToggle(Button::off);

  mute_button   = Button   (
                              s_screen,
                              width,
                              height,
                              width / 2 + 1,
                              23 + (height - 40 - 16 - 2 * 3) * 3 / 5,
                              (width - 46) / 2 - 1,
                              16,
                              0xFF006666,
                              0xFF003333,
                              0xFFCCCCCC,
                              "Sound",
                              &small_tw
                           );
  Sounds::mute();
  if(Sounds::isMuted())
    mute_button.setToggle(Button::off);
  else
    mute_button.setToggle(Button::on);

  default_button   = Button   (
                              s_screen,
                              width,
                              height,
                              width / 2 + 1,
                              23 + (height - 40 - 16 - 2 * 3) * 4 / 5,
                              (width - 46) / 2 - 1,
                              16,
                              0xFF006666,
                              0xFF003333,
                              0xFFCCCCCC,
                              "Restore Defaults",
                              &small_tw
                           );

  settings_close_button
                = Button   (
                              s_screen,
                              width,
                              height,
                              width / 2 + 1,
                              23 + (height - 40 - 16 - 2 * 3) * 5 / 5,
                              (width - 46) / 2 - 1,
                              16,
                              0xFF006666,
                              0xFF003333,
                              0xFFCCCCCC,
                              "Close",
                              &small_tw
                           );

  submenu_mode = none;
  selected_menu_item = mini_map_number = 0;
  active_menu_item = -1;
  selected_palette_menu_item = 0;
  active_palette_menu_item = -1;
  active_game_mode_button = -1;
  selected_game_mode_button = 1;
  edu_button.activate();
  start_game = false;
  setMousePosition(width / 2, height / 2);

  std::string f_name = "maps/maps.txt";
  std::ifstream c_file(f_name);
  std::string line;
  while (std::getline(c_file, line)) {
    menu_maps.push_back(line);
    left_menu.addButton(line);
  }
  setPaletteMenuItem(palette.getId());
}

void MenuGUI::loadMapInfo(int n) {
  if(menu_maps.empty())
    return;
  info_box.clearLines();
  if(selected_game_mode_button != 1)
    loadHighScore(n);
  else {
    info_box.setSlowTyping(slow_typing);
    std::ifstream fs("maps/" + menu_maps[n] + "/" + "info.txt");
    if(fs.is_open()) {
      std::string info;
      if(getline(fs, info))
        info_box.addLine(info, -1);
      fs.close();
    }
  }
}

void MenuGUI::loadHighScore(int n) {
  info_box.clearLines();
  info_box.setSlowTyping(slow_typing);
  if(menu_maps.empty())
    return;
  std::string l1, l2;
  if(selected_game_mode_button == 0) {
    l1 = "a";
    l2 = "Arcade";
  }
  else if(selected_game_mode_button == 2) {
    l1 = "tt";
    l2 = "Time Trial";
  }
  else
    return;
  std::ifstream fs("maps/" + menu_maps.at(n) + "/" + l1 + "hs.txt");
  if(fs.is_open()) {
    std::string name, score;
    if(getline(fs, name) && getline(fs, score)) {
      info_box.addLine("1st: " + name + " " + score + "pts", -1);
      if(getline(fs, name) && getline(fs, score)) {
        info_box.addLine("2nd: " + name + " " + score + "pts", -1);
        if(getline(fs, name) && getline(fs, score))
          info_box.addLine("3rd: " + name + " " + score + "pts", -1);
      }
    }
    else
      info_box.addLine("No " + l2 + " High Score For " + menu_maps.at(n), -1);
    fs.close();
  }
  else
    info_box.addLine("No " + l2 + " High Score For " + menu_maps.at(n), -1);
}

bool MenuGUI::loadMiniMap(std::string f_name) {
  int mm_w = map_box.getWidth() - 2;
  int mm_h = map_box.getHeight() - 2;
  mini_map.loadBMPtoSizeKeepAspect(f_name.c_str(), mm_w, mm_h);
  return true;
}

bool MenuGUI::loadMiniMap(int n) {
  if(menu_maps.empty())
    return false;
  std::string f_name;
  f_name = "maps/" + menu_maps.at(n) + "/" + menu_maps.at(n) + "_regions.bmp";
  char *mm_str = new char[f_name.size() + 1];
  strcpy(mm_str, f_name.c_str());
  bool return_value = false;
  if(loadMiniMap(mm_str))
    return_value = true;
  delete[] mm_str;
  return return_value;
}

void MenuGUI::startGame(std::string map_name) {
  start_game = true;
}

void MenuGUI::step() {
  if(mini_map_number != (int) selected_menu_item || mini_map.isLoaded() == false) {
    mini_map_number = selected_menu_item;
    loadMiniMap(mini_map_number);
  }
  if(submenu_mode == none) {

    title.step();
    left_menu.step();
    help_button.step();
    quit_button.step();
    settings_button.step();
    arcade_button.step();
    edu_button.step();
    tt_button.step();
    info_box.step();
    start_button.step();

    active_menu_item = left_menu.isOver(mouse_x, mouse_y);
    left_menu.setPosition(selected_menu_item);
    help_button.isOver(mouse_x, mouse_y);
    quit_button.isOver(mouse_x, mouse_y);
    settings_button.isOver(mouse_x, mouse_y);
    if(arcade_button.isOver(mouse_x, mouse_y))
      active_game_mode_button = 0;
    else if(edu_button.isOver(mouse_x, mouse_y))
      active_game_mode_button = 1;
    else if(tt_button.isOver(mouse_x, mouse_y))
      active_game_mode_button = 2;
    else
      active_game_mode_button = -1;
    if(start_button.isOver(mouse_x, mouse_y))
      active_start_button = true;
    else
      active_start_button = false;
  }
  else if(submenu_mode == help) {
    help_text_box.step();
  }
  else if(submenu_mode == settings) {

    palette_menu.step();
    canvas_filter_button.step();
    median_filter_button.step();
    slow_typing_button.step();
    mute_button.step();
    default_button.step();
    settings_close_button.step();

    active_palette_menu_item = palette_menu.isOver(mouse_x, mouse_y);
    palette_menu.setPosition(selected_palette_menu_item);
    canvas_filter_button.isOver(mouse_x, mouse_y);
    median_filter_button.isOver(mouse_x, mouse_y);
    slow_typing_button.isOver(mouse_x, mouse_y);
    mute_button.isOver(mouse_x, mouse_y);
    default_button.isOver(mouse_x, mouse_y);
    settings_close_button.isOver(mouse_x, mouse_y);
  }
}

void MenuGUI::draw() {
  for(int i = 0; i < width; i++)
    for(int j = 0; j < height; j++)
      s_screen[width * j + i] =
        palette.getColor(selected_menu_item,
                         (i + main_timer.getElapsedMilliseconds() / 50) / 3,
                         (j + main_timer.getElapsedMilliseconds() / 50) / 3);
  left_box.draw();
  title.draw();
  help_button.draw();
  left_menu.draw();
  quit_button.draw();
  settings_button.draw();
  right_box.draw();
  drawMiniMap(map_box.getX() + 1, map_box.getY() + 1);
  map_box.draw();
  arcade_button.draw();
  edu_button.draw();
  tt_button.draw();
  info_box.draw();
  start_button.draw();
  if(submenu_mode == help) {
    drawShade();
    help_box.draw();
    help_text_box.draw();
  }
  else if(submenu_mode == settings) {
    drawShade();
    settings_box.draw();
    palette_menu.draw();
    canvas_filter_button.draw();
    median_filter_button.draw();
    slow_typing_button.draw();
    mute_button.draw();
    default_button.draw();
    settings_close_button.draw();
  }
  drawCursor();
  render();
}

void MenuGUI::drawShade() {
  for(int i = 0; i < width; i++)
    for(int j = 0; j < height; j++)
      if((i + j) % 2 == 0)
        s_screen[width * j + i] = 0xFF000000;
}

void MenuGUI::drawMiniMap(int x, int y) {
  for(int j = 0; j < mini_map.getHeight(); j++) {
    for(int i = 0; i < mini_map.getWidth(); i++) {
      if(i + x >= 0 && i + x < width && j + y >= 0 && j + y < height) {
        int region_number = getMiniMapRegionNumber(i, j);
        unsigned int flags = 0x0000;
        if(mini_map.isBorder(i, j, palette.getBorderMode()))
          flags += Palette::IS_BORDER;

        s_screen[(j + y) * width + i + x]
          = palette.getColor(region_number == 0 ?
                             selected_menu_item + 11 : region_number,
                             i, j, flags);
      }
    }
  }
}

void MenuGUI::setMenuItem(int n) {
  if(left_menu.size() > 0) {
    selected_menu_item = n % left_menu.size();
    loadMapInfo(selected_menu_item);
  }
}

void MenuGUI::setPaletteMenuItem(int n) {
  if(palette_menu.size() > 0) {
    selected_palette_menu_item = n % palette_menu.size();
    palette.setPalette(selected_palette_menu_item);
  }
}

void MenuGUI::setGameMode(int n) {
  selected_game_mode_button = n % 3;
  arcade_button.deactivate();
  edu_button.deactivate();
  tt_button.deactivate();
  if(selected_game_mode_button == 0)
    arcade_button.activate();
  else if(selected_game_mode_button == 1)
    edu_button.activate();
  else if(selected_game_mode_button == 2)
    tt_button.activate();
  loadMapInfo(selected_menu_item);
}

void MenuGUI::handleEvents() {
  while(SDL_PollEvent(&event)){
    if(event.type == SDL_QUIT)
      cont = false;
    else if(event.type == SDL_KEYDOWN) {
      SDL_Keycode cur_key = event.key.keysym.sym;
      if(submenu_mode == none) {
        if      (cur_key == SDLK_UP    ) {
          setMenuItem(selected_menu_item + left_menu.size() - 1);
          Sounds::playClickSound();
        }
        else if (cur_key == SDLK_DOWN  ) {
          setMenuItem(selected_menu_item + 1);
          Sounds::playClickSound();
        }
        else if (cur_key == SDLK_LEFT  ) {
          setGameMode(selected_game_mode_button + 2);
          Sounds::playClickSound();
        }
        else if (cur_key == SDLK_RIGHT ) {
          setGameMode(selected_game_mode_button + 1);
          Sounds::playClickSound();
        }
        else if (cur_key == SDLK_RETURN) {
          if(!menu_maps.empty())
            startGame(menu_maps.at(selected_menu_item));
          Sounds::playClickSound();
          break;
        }
      }
      else if(submenu_mode == help) {
        if(cur_key == SDLK_ESCAPE || cur_key == SDLK_RETURN) {
          submenu_mode = none;
          Sounds::playClickSound();
        }
      }
      else if(submenu_mode == settings) {
        if      (cur_key == SDLK_ESCAPE || cur_key == SDLK_RETURN) {
          submenu_mode = none;
          Sounds::playClickSound();
        }
        if      (cur_key == SDLK_UP    ) {
          setPaletteMenuItem(selected_palette_menu_item + palette_menu.size() - 1);
          Sounds::playClickSound();
        }
        else if (cur_key == SDLK_DOWN  ) {
          setPaletteMenuItem(selected_palette_menu_item + 1);
          Sounds::playClickSound();
        }
      }
    }
    else if(event.type == SDL_MOUSEMOTION)     { handleMouseMotion(); }
    else if(event.type == SDL_MOUSEBUTTONDOWN) { handleMouseButtonDown(); }
    else if(event.type == SDL_MOUSEWHEEL)      { handleMouseWheel(event.wheel.y); }
  }
}

void MenuGUI::handleMouseMotion() {
  int win_w, win_h;
  SDL_GetWindowSize(win ,&win_w, &win_h);
  mouse_x = (event.motion.x * width) / win_w;
  mouse_y = (event.motion.y * height) / win_h;
}

void MenuGUI::handleMouseButtonDown() {
  if(submenu_mode == none) {
    if(quit_button.isOver(mouse_x, mouse_y))
      cont = false;
    /* Toggle submenu mode to launch help or settings submenus when their
       respective buttons are clicked */
    if(help_button.isOver(mouse_x, mouse_y)) {
      submenu_mode = help;
      help_text_box.setSlowTyping(slow_typing);
      Sounds::playClickSound();
    }
    if(settings_button.isOver(mouse_x, mouse_y)) {
      submenu_mode = settings;
      Sounds::playClickSound();
    }
    /* When a map in the map menu is clicked, select it */
    if(active_menu_item != -1) {
      setMenuItem(active_menu_item);
      active_menu_item = -1;
      Sounds::playClickSound();
    }
    /* When a game mode button is clicked, select it */
    if(active_game_mode_button != -1) {
      setGameMode(active_game_mode_button);
      Sounds::playClickSound();
    }
    /* When a map in the map menu is clicked, select it */
    if(active_menu_item != -1 && active_menu_item < (int) left_menu.size()) {
      setMenuItem(active_menu_item);
      active_menu_item = -1;
      Sounds::playClickSound();
    }
    /* When a game mode button is clicked, select it */
    if(active_game_mode_button != -1) {
      setGameMode(active_game_mode_button);
      Sounds::playClickSound();
    }
    /* When the start button is clicked... */
    if(active_start_button) {
      if(!menu_maps.empty())
        startGame(menu_maps.at(selected_menu_item));
      Sounds::playClickSound();
    }
  }
  else if(submenu_mode == help) {
    submenu_mode = none;
    Sounds::playClickSound();
  }
  else if(submenu_mode == settings) {
    if(active_palette_menu_item != -1) {
      setPaletteMenuItem(active_palette_menu_item);
      Sounds::playClickSound();
    }
    if(median_filter_button.isOver(mouse_x, mouse_y)) {
      if(median_filter.isActive()) {
        median_filter.deactivate();
        median_filter_button.setToggle(Button::off);
      }
      else {
        median_filter.activate();
        median_filter_button.setToggle(Button::on);
      }
      Sounds::playClickSound();
    }
    if(canvas_filter_button.isOver(mouse_x, mouse_y)) {
      if(canvas_filter.isActive()) {
        canvas_filter.deactivate();
        canvas_filter_button.setToggle(Button::off);
      }
      else {
        canvas_filter.activate();
        canvas_filter_button.setToggle(Button::on);
      }
      Sounds::playClickSound();
    }
    if(slow_typing_button.isOver(mouse_x, mouse_y)) {
      if(slow_typing) {
        slow_typing = false;
        slow_typing_button.setToggle(Button::off);
      }
      else {
        slow_typing = true;
        slow_typing_button.setToggle(Button::on);
      }
      Sounds::playClickSound();
    }
    if(mute_button.isOver(mouse_x, mouse_y)) {
      if(Sounds::isMuted()) {
        Sounds::unmute();
        mute_button.setToggle(Button::on);
      }
      else {
        Sounds::mute();
        mute_button.setToggle(Button::off);
      }
      Sounds::playClickSound();
    }
    if(default_button.isOver(mouse_x, mouse_y)) {
      median_filter.deactivate();
      median_filter_button.setToggle(Button::off);
      canvas_filter.deactivate();
      canvas_filter_button.setToggle(Button::off);
      slow_typing = true;
      slow_typing_button.setToggle(Button::on);
      Sounds::mute();
      mute_button.setToggle(Button::off);
      Sounds::playClickSound();
    }
    if(settings_close_button.isOver(mouse_x, mouse_y)) {
      submenu_mode = none;
      Sounds::playClickSound();
    }
  }
}

void MenuGUI::handleMouseWheel(int y) {
  if(submenu_mode == none) {
    if(y > 0) {
      setMenuItem(selected_menu_item + left_menu.size() - 1);
      Sounds::playClickSound();
    }
    else {
      setMenuItem(selected_menu_item + 1);
      Sounds::playClickSound();
    }
  }
  else if(submenu_mode == settings) {
    if(y > 0) {
      setPaletteMenuItem(selected_palette_menu_item + palette_menu.size() - 1);
      Sounds::playClickSound();
    }
    else {
      setPaletteMenuItem(selected_palette_menu_item + 1);
      Sounds::playClickSound();
    }
  }
}

int MenuGUI::getMiniMapRegionNumber(int x, int y) const {
  int region_number = -1;
  if(x >= 0 && x < mini_map.getWidth()
            && y >= 0 && y < mini_map.getHeight()) {
    region_number = (int) (mini_map.getPixelAt(x, y) & 0x00FFFFFF);
  }
  if(region_number == 0x0000FF00)      { region_number = -1; }
  else if(region_number == 0x00009900) { region_number = -2; }
  return region_number;
}


std::string MenuGUI::getMapName() const {
  if(!menu_maps.empty())
    return menu_maps[selected_menu_item];
  return "";
}

int MenuGUI::getStartGame() const {
  return start_game;
}

int MenuGUI::getGameMode() const {
  return selected_game_mode_button;
}

int MenuGUI::getMenuItem() const {
  return selected_menu_item;
}
