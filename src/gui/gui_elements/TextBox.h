#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include <string>

#include "Box.h"
#include "../text/Typesetter.h"

class TextBox : public Box {

  private:

    Typesetter ts;

    int spacing;

  public:

    TextBox();

    TextBox(Uint32*     n_screen,
            int         n_width,
            int         n_height,
            int         n_x,
            int         n_y,
            int         n_w,
            int         n_h,
            Uint32      n_color,
            Uint32      n_border_color,
            int         n_shadow_mode,
            Typewriter* tw             );

    void addLine(std::string s, double life);

    void clearLines();

    void step();

    void setSlowTyping(bool slow_typing);

    void draw() const;
};

#endif
