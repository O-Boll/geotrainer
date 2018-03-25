#include "TextBox.h"

TextBox::TextBox() {
}

TextBox::TextBox(Uint32*     n_screen,
                 int         n_width,
                 int         n_height,
                 int         n_x,
                 int         n_y,
                 int         n_w,
                 int         n_h,
                 Uint32      n_color,
                 Uint32      n_border_color,
                 int         n_shadow_mode,
                 Typewriter* tw             )

  : Box(n_screen,
        n_width,
        n_height,
        n_x,
        n_y,
        n_w,
        n_h,
        n_color,
        n_border_color,
        n_shadow_mode  ),

    ts(n_screen, n_width, n_height, tw) {

  spacing = 2;

  ts.setBox(n_x + spacing,
            n_y + spacing,
            n_w - 2 * spacing,
            n_h - 2 * spacing );

  ts.setClipping(n_x + spacing,
                 n_y + spacing,
                 n_w - 2 * spacing,
                 n_h - 2 * spacing);
}


void TextBox::addLine(std::string s, double life) {
  ts.addLine(s, life);
}


void TextBox::clearLines() {
  ts.clearLines();
}

void TextBox::step() {
  ts.step();
}

void TextBox::setSlowTyping(bool slow_typing) {
  ts.setSlowTyping(slow_typing);
}

void TextBox::draw() const {
  Box::draw();
  ts.type();
}
