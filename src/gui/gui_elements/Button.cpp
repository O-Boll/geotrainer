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

#include "Button.h"

Button::Button() {}

Button::Button(Uint32*     n_screen,
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
               Typewriter* n_tw           )

  : body(n_screen,
         n_width,
         n_height,
         n_x,
         n_y,
         n_w,
         n_h,
         n_color,
         n_border_color,
         1              ),

    label(n_screen,
          n_width,
          n_height,
          n_tw     )      {


  color = n_color;
  alt_color = n_alt_color;
  label_color = 0xFFCCCCCC;
  button_down = button_active = false;
  toggle = none;
  setLabel(n_label);
}

bool Button::isOver(int x, int y) {
  bool is_over = false;
  if(   x >= body.getX()
     && x <  body.getX() + body.getWidth()
     && y >= body.getY()
     && y <  body.getY() + body.getHeight()
     && x >= body.getClippingX()
     && x <  body.getClippingX() + body.getClippingWidth()
     && y >= body.getClippingY()
     && y <  body.getClippingY() + body.getClippingHeight() )

    is_over = true;

  if(!is_over)
    pull();
  else
    push();
  return is_over;
}

void Button::activate() {
  button_active = true;
  label.setColor(0xFFCC0000);
}

void Button::deactivate() {
  button_active = false;
  label.setColor(label_color);
}

void Button::push() {
  body.setColor(alt_color);
  body.setShadowMode(2);
  label_offset_x = label_offset_y = 1;
  updateLabelPosition();
  button_down = true;
}

void Button::pull() {
  body.setColor(color);
  body.setShadowMode(1);
  label_offset_x = label_offset_y = 0;
  updateLabelPosition();
  button_down = false;
}

void Button::updateLabelPosition() {
  label.setBox(label_x + label_offset_x,
               label_y + label_offset_y,
               label.getTextWidth(),
               label.getTextHeight());
}

void Button::step() {
  label.step();
}

void Button::draw() const {
  body.draw();
  label.type();
}

void Button::moveTo(int n_x, int n_y) {
  body.moveTo(n_x, n_y);
  label_x = body.getX() + (body.getWidth() - label.getTextWidth() ) / 2;
  label_y = body.getY() + (body.getHeight() - label.getTextHeight()) / 2;
  updateLabelPosition();
}

int Button::getHeight() const {
  return body.getHeight();
}

void Button::setLabel(std::string n_label) {
  slabel = n_label;
  if(toggle == on)
    n_label += ": On";
  else if(toggle == off)
    n_label += ": Off";
  label.clearLines();
  /* make box big to calculate text width/height */
  label.setBox(body.getX(),
               body.getY(),
               body.getX() + body.getWidth(),
               body.getY() + body.getHeight());

  /* text width/height is calculated when a line is added */
  label.addLine(n_label);

  /* then shrink it to size */
  label_x = body.getX() + (body.getWidth() - label.getTextWidth() ) / 2;
  label_y = body.getY() + (body.getHeight() - label.getTextHeight()) / 2;
  label_offset_x = 0;
  label_offset_y = 0;
  label.setBox(label_x, label_y, label.getTextWidth(), label.getTextHeight());
  label.setColor(label_color);
}

void Button::setToggle(togglemode n_toggle) {
  toggle = n_toggle;
  if(toggle != none)
    setLabel(slabel);
}

void Button::setClipping(int n_x, int n_y, int n_w, int n_h ) {

  body.setClipping(n_x, n_y, n_w, n_h);
  label.setClipping(n_x, n_y, n_w, n_h);
}
