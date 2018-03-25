#ifndef BUTTON_BOX_H
#define BUTTON_BOX_H

#include <vector>
#include <string>

#include <SDL.h>

#include "Button.h"
#include "../text/Typewriter.h"

class ButtonBox {

  public:

    enum {none = -1};

  private:

    Uint32* screen;

    int width, height;

    int x, y, w, h;

    Box body;

    Typewriter *tw;

    std::vector<Button> buttons;

    Uint32 color, alt_color, border_color;

    int position, spacing;

    void drawButtonAtPosition(Button b, int n) const;

    bool buttonIsOver(Button& b, int n, int mouse_x, int mouse_y);

  public:

    ButtonBox();

    ButtonBox(Uint32*     n_screen,
              int         n_width,
              int         n_height,
              int         n_x,
              int         n_y,
              int         n_w,
              int         n_h,
              Uint32      n_color,
              Uint32      n_alt_color,
              Uint32      n_border_color,
              Typewriter* n_tw           );

    void addButton(std::string n_label);

    void setPosition(int n);

    int getPosition() const;

    int size() const;

    void step();

    void draw() const;

    int isOver(int mouse_x, int mouse_y);

};

#endif
