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

#include "ButtonBox.h"

ButtonBox::ButtonBox() {
}

ButtonBox::ButtonBox(Uint32*       n_screen,
                     const int     n_width,
                     const int     n_height,
                     const int     n_x,
                     const int     n_y,
                     const int     n_w,
                     const int     n_h,
                     const Uint32  n_color,
                     const Uint32  n_alt_color,
                     const Uint32  n_border_color,
                     Typewriter*   n_tw           )

  : body(n_screen,
         n_width,
         n_height,
         n_x,
         n_y,
         n_w,
         n_h,
         n_color,
         n_border_color,
         2              )      {


  screen = n_screen;
  width = n_width;
  height = n_height;
  x = n_x;
  y = n_y;
  w = n_w;
  h = n_h;
  tw = n_tw;
  color = n_color;
  alt_color = n_alt_color;
  border_color = n_border_color;
  position = 3;
  spacing = 3;
}


void ButtonBox::addButton(const string n_label) {

  Typesetter temp_ts(screen, width, height, tw);
  temp_ts.addLine(n_label);
  int text_w = temp_ts.getTextWidth(),
      text_h = temp_ts.getTextHeight();

  Button n_b(screen,
             width,
             height,
             0, 0,
             text_w + 4, /* + 4 just to get some extra space */
             text_h,
             color,
             alt_color,
             border_color,
             n_label,
             tw           );

  n_b.setClipping(x + 1, y + 2, w - 2, h - 3);
  buttons.push_back(n_b);
}


void ButtonBox::setPosition(const int n) {
  if(n != none)
    position = n;
  for(int i = 0; i < buttons.size(); i++) {
    buttons[i].deactivate();
    if(i == position)
      buttons[i].activate();
  }
}

int ButtonBox::getPosition() const {
  return position;
}

int ButtonBox::size() const {
  return buttons.size();
}

void ButtonBox::step() {
  for(auto& b : buttons)
    b.step();
}

void ButtonBox::draw() const {

  body.draw();

  for(int i = 0; i < buttons.size(); i++)
    drawButtonAtPosition(buttons[i], i - position);

}

void ButtonBox::drawButtonAtPosition(Button b, const int n) const {
  int center_y = y + h / 2;
  int pos_y0 = center_y - b.getHeight() / 2;
  int button_offset = b.getHeight() + spacing;
  int total_height = button_offset * buttons.size();
  int y_position = pos_y0 + n * button_offset
                   - total_height
                   * ((h / 2 + b.getHeight() / 2 + n * button_offset)
                   / total_height);
  while(true) {
    if(y_position > y + h)
      break;
    b.moveTo(x + 4, y_position);
    b.draw();
    y_position += total_height;
  }
}


int ButtonBox::isOver(int mouse_x, int mouse_y) {
  int n = none;
  for(int i = 0; i < buttons.size(); i++)
    if(buttonIsOver(buttons[i], i - position, mouse_x, mouse_y))
      n = i;
  return n;
}


bool ButtonBox::buttonIsOver(Button& b,
                             const int n,
                             const int mouse_x,
                             const int mouse_y ) {

  int center_y = y + h / 2;
  int pos_y0 = center_y - b.getHeight() / 2;
  int button_offset = b.getHeight() + spacing;
  int total_height = button_offset * buttons.size();
  int y_position = pos_y0 + n * button_offset
                   - total_height
                   * ((h / 2 + b.getHeight() / 2 + n * button_offset)
                   / total_height);
  while(true) {
    if(y_position > y + h)
      break;
    b.moveTo(x + 4, y_position);
    if(b.isOver(mouse_x, mouse_y))
      return true;
    y_position += total_height;
  }
  return false;
}

