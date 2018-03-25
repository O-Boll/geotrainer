#ifndef GAME_GUI_H
#define GAME_GUI_H

#include <string>

#include "GUI.h"
#include "particles/Particles.h"

class GameGUI : public GUI {

  private:

    int game_mode;
    std::vector<City> city_info;
    Img region_map;
    std::vector<string> region_info;
    std::vector<int> region_center_x, region_center_y;

    std::string map_name;

    int game_state; /* 1: menu; 2: game; */
    bool run_game;


////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS ETC.

  public:

    GameGUI();

    GameGUI(std::string map_name, int game_mode);

    ~GameGUI();


////////////////////////////////////////////////////////////////////////////////
// LOADING AND CLEARING METHODS

  public:

    void loadRegionMap(std::string f_name);

    void loadRegionInfo(std::string f_name);

    void loadCityCoordinates(std::string f_name);

    void loadCityNames(std::string f_name);



////////////////////////////////////////////////////////////////////////////////
// DRAWING METHODS

  public:

    void draw();

    void drawMenuScreen();

    void drawRegionMap();

    void drawMiniMap(int x, int y);

    void drawCities();

    void drawImg(const Img* i, int x, int y);


////////////////////////////////////////////////////////////////////////////////
// TEXT PRINTING, BEACONS AND PARTICLE EFFECTS

  private:

    Typesetter main_ts,

               time_ts;

    Particles particles;

  public:

    void printMain(std::string s, double life, Uint32 color);

    void clearMain();

    void printTime(int t, Uint32 color);

    void printTime(int t);

    void regionBeacon(int region_number, double time, Uint32 color);

    void cityBeacon(vector<int> city_numbers, double time, int symbol);

    void createParticles(uint32_t n);


////////////////////////////////////////////////////////////////////////////////
// IN-GAME INPUT

  private:

    int selected_region,

        chosen_region;

    std::vector<int> selected_cities,

                chosen_cities;

    int scroll_x,

        scroll_y,

        selected_x,

        selected_y,

        city_select_distance;

    bool lock_input,

         help_button_pressed,

         plus_button_pressed;

  public:

    char readInput(SDL_Keycode k);

    void handleEvents();

    void handleMouseMotion();

    void handleMouseButtonDown();

    bool helpButtonPressed() const;

    void resetHelpButton();

    bool plusButtonPressed() const;

    void resetPlusButton();


////////////////////////////////////////////////////////////////////////////////
// IN-GAME DIALOGS

  private:

    bool alert_dialog_on, input_dialog_on, yes_no_dialog_on;

    bool dialog_ok, dialog_no;

    int input_dialog_max_input_length;

    std::string input_dialog_input;

  public:

    void alertDialog(std::string message);

    void alertDialog(std::string message, std::string s);

    void inputDialog(std::string message);

    void inputDialog(std::string message, unsigned int max_length);

    void yesNoDialog(std::string message);

    void yesNoDialog(std::string message, std::string s);

    bool dialogOn();

    bool dialogOK();

    bool dialogNo();

    std::string dialogInput();

    void turnDialogOff();



////////////////////////////////////////////////////////////////////////////////
// GAME MECHANICS


    void startGame(std::string map_name);

    void step();

    int search_mode; /* 0: regions & cities; 1: regions only; 2: cities only; */

    void setScroll();

    std::string getMapName() const;

    std::string getRegionName(int region_number) const;

    int getRegionNumber(int rel_x, int rel_y) const;

    bool mouseOverRegion(int region_number) const;

    bool noChosenRegion() const;

    bool isSelectedRegion(int region_number) const;

    bool isChosenRegion(int region_number) const;

    int getChosenRegion() const;

    void deselectRegion();

    int getNumberOfRegions() const;

    int getRegionXCoordinate(int region_number) const;

    int getRegionYCoordinate(int region_number) const;

    std::string getCityName(int city_number) const;

    std::vector<int> getCityNumbers(int rel_x, int rel_y) const;

    bool mouseOverCity(int city_number) const;

    bool noChosenCities() const;

    bool isSelectedCity(int city_number) const;

    bool isChosenCity(int city_number) const;

    std::vector<int> getChosenCities() const;

    void setCitySelectDistance(int d);

    void deselectCities();

    int getNumberOfCities() const;

    int getCityXCoordinate(int city_number) const;

    int getCityYCoordinate(int city_number) const;

    void setSearchMode(int m);

    bool searchRegions() const;

    bool searchCities() const;

    void resetSelection();

    void lockInput();

    void unlockInput();

    bool isLocked() const;

    void setMousePosition(int x, int y);

    bool getCloseGUI() const;


////////////////////////////////////////////////////////////////////////////////
// MENU MECHANICS

    void startMenu();

    int getGameState() const;

};

#endif
