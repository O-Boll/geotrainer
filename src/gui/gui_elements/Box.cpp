#include <algorithm>

#include "Box.h"

using std::max;
using std::min;

Box::Box() {
  screen = nullptr;
  width = 0;
  height = 0;
  x = y = w = h = 0;
  clip_x = clip_y = clip_w = clip_h = 0;
  color = border_color = 0;
  shadow_mode = 0;
}

Box::Box(Uint32* n_screen,
         int     n_width,
         int     n_height,
         int     n_x,
         int     n_y,
         int     n_w,
         int     n_h,
         Uint32  n_color,
         Uint32  n_border_color,
         int     n_shadow_mode  ) {

  screen = n_screen;
  width = n_width;
  height = n_height;
  x = n_x;
  y = n_y;
  w = n_w;
  h = n_h;
  clip_x = n_x ;
  clip_y = n_y ;
  clip_w = n_w + 1; /* + 1 otherwise shadow is clipped */
  clip_h = n_h + 1;
  color = n_color;
  border_color = n_border_color;
  shadow_mode = n_shadow_mode;

}

void Box::setClipping(int n_clip_x,
                      int n_clip_y,
                      int n_clip_w,
                      int n_clip_h) {

  clip_x = n_clip_x;
  clip_y = n_clip_y;
  clip_w = n_clip_w;
  clip_h = n_clip_h;

}


void Box::draw() const {

  if(color != 0xFF00Ff00)

    for(int i = max(0, max(x, clip_x));
            i < min(x + w, min(width, clip_x + clip_w));
            i++)

      for(int j = max(0, max(y, clip_y));
              j < min(y + h, min(height, clip_y + clip_h));
              j++)

        if(   !((i == x || i == x + w - 1)
           &&   (j == y || j == y + h - 1)))

          screen[j * width + i] = color;


  if(border_color != 0xFF00FF00)

    drawBorder();

  if(shadow_mode == 1)

    drawInsideShadow();

  else if(shadow_mode == 2)

    drawOutsideShadow();

}


void Box::drawBorder() const {
  if(   y >= max(0, clip_y)
     && y < min(height, clip_y + clip_h))

    for(int i = max(0, max(x + 1, clip_x));
            i < min(x + w - 1, min(width, clip_x + clip_w));
            i++)

      screen[width * y + i] = border_color;


  if(   y + h - 1 >= max(0, clip_y)
     && y + h - 1 < min(height, clip_y + clip_h))
    for(int i = max(0, max(x + 1, clip_x));
            i < min(x + w - 1, min(width, clip_x + clip_w));
            i++)

      screen[width * (y + h - 1) + i] = border_color;


  if(   x >= max(0, clip_x)
     && x < min(width, clip_x + clip_w))

    for(int j = max(0, max(y + 1, clip_y));
            j < min(y + h - 1, min(height, clip_y + clip_h));
            j++)

      screen[width * j + x] = border_color;


  if(   x + w - 1 >= max(0, clip_x)
     && x + w - 1 < min(width, clip_x + clip_w))

    for(int j = max(0, max(y + 1, clip_y));
            j < min(y + h - 1, min(height, clip_y + clip_h));
            j++)

      screen[width * j + x + w - 1] = border_color;
}


void Box::drawOutsideShadow() const {

  if(   y + 1 >= max(0, clip_y)
     && y + 1 < min(height, clip_y + clip_h))

    for(int i = max(clip_x, max(0, x + 1));
            i < min(clip_x + clip_w, min(x + w - 1, width));
            i++)

      screen[width * (y + 1) + i] = 0xFF000000;


  if(   x + 1 >= max(0, clip_x)
     && x + 1 <  min(width, clip_x + clip_w))

    for(int j = max(clip_y, max(0, y + 2));
            j < min(clip_y + clip_h, min(y + h - 1, height));
            j++)

      screen[width * j + x + 1] = 0xFF000000;
}


void Box::drawInsideShadow() const {

  if(   x + w >= max(0, clip_x)
     && x + w < min(width, clip_x + clip_w))

    for(int j = max(clip_y, max(0, y + 2));
            j < min(clip_y + clip_h, min(y + h, height));
            j++)

      screen[width * j + x + w] = 0xFF000000;


  if(   y + h >= max(0, clip_y)
     && y + h < min(height, clip_y + clip_h))

    for(int i = max(clip_x, max(0, x + 2));
            i < min(clip_x + clip_w, min(x + w, width));
            i++)

      screen[width * (y + h) + i] = 0xFF000000;


  if(   x + w - 1 >= max(0, clip_x)
     && x + w - 1 <  min(clip_x + clip_w, width)
     && y + h - 1 >= max(0, clip_y)
     && y + h - 1 <  min(height, clip_y + clip_h))

    screen[width * (y + h - 1) + x + w - 1] = 0xFF000000;

}

void Box::setColor(Uint32 n_color) {
  color = n_color;
}

void Box::setShadowMode(int n_shadow_mode) {
  shadow_mode = n_shadow_mode;
}

void Box::moveTo(int n_x, int n_y) {
  int offset_x = n_x - x,
      offset_y = n_y - y;
  x = n_x;
  y = n_y;
}

int Box::getX() const {
  return x;
}

int Box::getY() const {
  return y;
}

int Box::getWidth() const {
  return w;
}

int Box::getHeight() const {
  return h;
}

int Box::getClippingX() const {
  return clip_x;
}

int Box::getClippingY() const {
  return clip_y;
}

int Box::getClippingWidth() const {
  return clip_w;
}

int Box::getClippingHeight() const {
  return clip_h;
}
