#ifndef MENU_GUI_H
#define MENU_GUI_H

#include <string>
#include <vector>

#include "GUI.h"

class MenuGUI : public GUI {

  private:

    enum {none, help, settings} submenu_mode;

    int active_game_mode_button; /* = mouse over */
    int selected_game_mode_button;
    bool active_start_button;

    std::vector<string> menu_maps;
    int selected_menu_item;
    int active_menu_item; /* = mouse over */
    int selected_palette_menu_item;
    int active_palette_menu_item;
    Img mini_map;
    int mini_map_number;
    bool start_game;


////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS

  public:

    MenuGUI();


////////////////////////////////////////////////////////////////////////////////
// GUI ELEMENTS

  private:

    /*
      The left_box box occupies the left hand side of the menu. It has
      the following layout:
       ______________________________
      |      title    help_button    |
      |  __________________________  |
      | |                          | |
      | |        left_menu         | |
      | |__________________________| |
      | quit_button  settings_button |
      |______________________________|

      1) The title is implemented as an unclickable button with the
         text GeoTrainer.
      2) Clicking the help_botton button launches the help submenu.
      3) The button box left_menu displays and lets the player choose
         from the various maps that are available.
      4) Clicking the quit_button button exits the game.
      5) Clicking the setting_button button launches the settings
         submenu.
    */

    Box left_box;
      Button title;
      Button help_button;
      ButtonBox left_menu;
      Button quit_button;
      Button settings_button;

    /*
      The right_box box occupies the right hand side of the menu. It has
      the following layout:
       ______________________________________
      |  __________________________________  |
      | |                                  | |
      | |             map_box              | |
      | |__________________________________| |
      | arcade_button  edu_button  tt_button |
      |  __________________________________  |
      | |                                  | |
      | |             info_box             | |
      | |__________________________________| |
      |             start_button             |
      |______________________________________|

      1) The map_box box displays a miniature version of the selected map
         (i.e. a minimap).
      2) Clicking the arcade_botton button toggles the arcade game mode.
      3) Clicking the edu_botton button toggles the educational game mode.
      4) Clicking the tt_botton button toggles the time trial game mode.
      5) The info_box box displays information about the selected map
         such as high score and general map info.
      6) Clicking the start_button button launches a game on the selected
    */

    Box right_box;
      Box map_box;
      TextBox info_box;
      Button arcade_button;
      Button edu_button;
      Button tt_button;
      Button start_button;

    /*
      The help_box box has the following layout:
       ______________________________
      |  __________________________  |
      | |                          | |
      | |      help_text_box       | |
      | |__________________________| |
      |______________________________|

      1) The help_text_box text box displays information about how to play
         the game. This information is stored as strings in the help_text
         vector.
    */

    Box help_box;
      TextBox help_text_box;

      static const vector<string> help_text;

    /*
      The settings_box box has the following layout:
       ______________________________
      |  __________________________  |
      | |                          | |
      | |          ...             | |
      | |__________________________| |
      |______________________________|

    */

    Box settings_box;
      ButtonBox palette_menu;
      Button canvas_filter_button;
      Button median_filter_button;
      Button slow_typing_button;
      Button mute_button;
      Button default_button;
      Button settings_close_button;

////////////////////////////////////////////////////////////////////////////////
// METHODS FOR LOADING AND CLEARING

  public:

    void loadMenuMaps();

    void loadMapInfo(int n);

    void loadHighScore(int n);

    bool loadMiniMap(std::string f_name);

    bool loadMiniMap(int n);

    void loadRegionMap(std::string f_name);

    void loadRegionInfo(std::string f_name);


////////////////////////////////////////////////////////////////////////////////
// METHODS FOR DRAWING

  public:

    void draw();

    void drawShade();

    void drawMiniMap(int x, int y);


////////////////////////////////////////////////////////////////////////////////
// MENU INPUT

  public:

    void setMenuItem(int n);

    void setPaletteMenuItem(int n);

    void setGameMode(int n);

    void handleEvents();

    void handleMouseMotion();

    void handleMouseButtonDown();

    void handleMouseWheel(int y);


////////////////////////////////////////////////////////////////////////////////
// STARTING GAMES

  public:

    void startGame(std::string map_name);

    int search_mode; /* 0: regions & cities; 1: regions only; 2: cities only; */

    std::string getMapName() const;


////////////////////////////////////////////////////////////////////////////////
// MENU MECHANICS

  public:

    void step();

    int getMiniMapRegionNumber(int x, int y) const;

    int getStartGame() const;

    int getGameMode() const;

    int getMenuItem() const;

    bool getCloseGUI() const;


};

#endif
