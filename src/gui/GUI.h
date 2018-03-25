#ifndef GUI_H
#define GUI_H

#include <string>

#include <SDL.h>

#include "img/Img.h"
#include "city/City.h"
#include "palette/Palette.h"
#include "gui_elements/Box.h"
#include "text/Typesetter.h"
#include "gui_elements/Button.h"
#include "gui_elements/ButtonBox.h"
#include "gui_elements/TextBox.h"
#include "../sound/Sounds.h"
#include "filter/MedianFilter.h"
#include "filter/CanvasFilter.h"

class GUI {

  private:

    static unsigned int frame_no;

  protected:

    static SDL_Window* win;
    static SDL_Renderer* ren;
    static SDL_Texture* tex;
    static SDL_Event event;

    static Palette palette;
    static bool slow_typing;

    static MedianFilter median_filter;
    static CanvasFilter canvas_filter;

    static Timer main_timer;

    static Typewriter def_tw, small_tw, tiny_tw;

    static int width;
    static int height;
    static int scale;
    static Uint32* s_screen;
    static Uint32* screen;
    static bool cont;

    int mouse_x, mouse_y;

    unsigned int getFrameNumber() const;

  public:

    virtual ~GUI();

    static void initGUI(int n_width, int n_height, int n_scale);

    static void exitGUI();

    void render(int offset_x, int offset_y);

    void render();

    void drawCursor();

    virtual void handleEvents() = 0;

    virtual void handleMouseMotion() = 0;

    virtual void handleMouseButtonDown() = 0;

    std::string getMapName() const;

    void setMousePosition(int x, int y);

    int getMouseXPosition() const;

    int getMouseYPosition() const;

    static bool getCloseGUI();

};

#endif
