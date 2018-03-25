#ifndef BOX_H
#define BOX_H

#include <SDL.h>

using namespace std;

class Box {

  private:

    Uint32* screen; /* this is where we draw the box */

    int width, height; /* width and height of screen */

    int x, y, w, h;

    int clip_x, clip_y, clip_w, clip_h; /* for clipping */

    Uint32 color, border_color;

    int shadow_mode; /* 0 = no shadow, 1 = outside shadow, 2 = inside shadow */

  public:

    Box();

    Box(Uint32* n_screen,
        int     n_width,
        int     n_height,
        int     n_x,
        int     n_y,
        int     n_w,
        int     n_h,
        Uint32  n_color,
        Uint32  n_border_color,
        int     n_shadow_mode);

    void setClipping(int n_clip_x,
                     int n_clip_y,
                     int n_clip_w,
                     int n_clip_h);

    virtual void draw() const;

  private:

    void drawBorder() const;

    void drawOutsideShadow() const;

    void drawInsideShadow() const;

  public:

    void setColor(Uint32 n_color);

    void setShadowMode(int n_shadow_mode);

    void moveTo(int n_x, int n_y);

    int getX() const;

    int getY() const;

    int getWidth() const;

    int getHeight() const;

    int getClippingX() const;

    int getClippingY() const;

    int getClippingWidth() const;

    int getClippingHeight() const;

};

#endif

