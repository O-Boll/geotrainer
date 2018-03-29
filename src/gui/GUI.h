#ifndef GUI_H
#define GUI_H

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
