#ifndef BUTTON_H
#define BUTTON_H

#include <string>

#include <SDL.h>

#include "Box.h"
#include "../text/Typesetter.h"

class Button {

  public:

    enum togglemode {none, on, off};

  private:

    Box body;

    std::string slabel;

    Typesetter label;

    Uint32 color, alt_color, label_color;

    bool button_down, button_active;

    int label_x, label_y, label_offset_x, label_offset_y;

    togglemode toggle;

  public:

    Button();

    Button(Uint32*     n_screen,
           int         n_width,
           int         n_height,
           int         n_x,
           int         n_y,
           int         n_w,
           int         n_h,
           Uint32      n_color,
           Uint32      n_alt_color,
           Uint32      n_border_color,
           std::string n_label,
           Typewriter* n_tw           );

    bool isOver(int x, int y);

    void activate();

    void deactivate();

  private:

    void push();

    void pull();

    void updateLabelPosition();

  public:

    void step();

    void draw() const;

    void moveTo(int n_x, int n_y);

    int getHeight() const;

    void setLabel(std::string n_label);

    void setToggle(togglemode n_toggle);

    void setClipping(int n_x, int n_y, int n_w, int n_h );
};

#endif
