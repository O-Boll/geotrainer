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

#include "GUI.h"

unsigned int  GUI::frame_no    = 0;

CanvasFilter  GUI::canvas_filter;
MedianFilter  GUI::median_filter;

Palette       GUI::palette     = Palette();
bool          GUI::slow_typing = true;

Timer         GUI::main_timer  = Timer();

Typewriter    GUI::def_tw      = Typewriter(),
              GUI::small_tw    = Typewriter(),
              GUI::tiny_tw     = Typewriter();

int           GUI::width,
              GUI::height,
              GUI::scale;

Uint32*       GUI::s_screen    = nullptr;
Uint32*       GUI::screen      = nullptr;


SDL_Window*   GUI::win         = nullptr;
SDL_Renderer* GUI::ren         = nullptr;
SDL_Texture*  GUI::tex         = nullptr;
SDL_Event     GUI::event;

bool          GUI::cont        = true;

unsigned int GUI::getFrameNumber() const {
  return frame_no;
}

GUI::~GUI() {}

void GUI::initGUI(int n_width, int n_height, int n_scale) {
  width = n_width;
  height = n_height;
  scale = n_scale;
  s_screen = new Uint32[width * height];
  screen = new Uint32[(scale * width) * (scale * height)];
  win = SDL_CreateWindow("GeoTrainer",
                         100,
                         100,
                         scale * width,
                         scale * height,
                         SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);// | SDL_WINDOW_FULLSCREEN_DESKTOP);
  ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED); // | SDL_RENDERER_PRESENTVSYNC);
  tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, scale * width, scale * height);
  SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_NONE);

  median_filter = MedianFilter(screen, scale * width, scale * height);
  median_filter.setSmallScreen(s_screen, width, height, scale);
  canvas_filter = CanvasFilter(screen, scale * width, scale * height);
  canvas_filter.loadCanvas("img/paper.bmp");

  def_tw   = Typewriter("ttf/tahoma.ttf", 18);
  small_tw = Typewriter("ttf/tahoma.ttf", 12);
  tiny_tw  = Typewriter("ttf/tahoma.ttf", 10);

  palette = Palette();

  Sounds::initSounds();
}

void GUI::exitGUI() {
  Sounds::exitSounds();
  delete[] screen;
  delete[] s_screen;
  SDL_DestroyTexture(tex);
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
}

void GUI::render(int offset_x, int offset_y) {
  Uint32 x, y, s_x = 0, s_y, t_width = scale * width;
  Uint32* p = screen, * s_p = s_screen;
  for(y = 0; y < height; y++) {
    for(s_y = 0; s_y < scale; s_y++) {
      for(x = 0; x < t_width; x++) {
        *(p++) = *s_p;
        if(++s_x == scale) {
          s_x = 0;
          s_p++;
        }
      }
      if(s_y + 1 < scale)
        s_p -= width;
    }
  }

  median_filter.apply();
  canvas_filter.setOffset(offset_x, offset_y);
  canvas_filter.apply();
  SDL_UpdateTexture(tex, NULL, screen, scale * width * sizeof (Uint32));
  SDL_RenderCopy(ren, tex, NULL, NULL);
  SDL_RenderPresent(ren);
  frame_no++;
}

void GUI::render() {
  render(0, 0);
}

void GUI::drawCursor() {
  for(int n = mouse_x - 10 > 0 ? mouse_x - 10 : 0;
          n < (mouse_x + 10 < width ? mouse_x + 10 : width);
          n++)

    s_screen[mouse_y * width + n] = 0xFF000000;

  for(int n = mouse_y - 10 > 0 ? mouse_y - 10 : 0;
          n < (mouse_y + 10 < height ? mouse_y + 10 : height);
          n++)

    s_screen[n * width + mouse_x] = 0xFF000000;
}

void GUI::setMousePosition(int x, int y) {
  int win_w, win_h;
  SDL_GetWindowSize(win ,&win_w, &win_h);
  SDL_WarpMouseInWindow(win, int((x * win_w) / width), int((y * win_h) / height));
  mouse_x = x;
  mouse_y = y;
}

int GUI::getMouseXPosition() const {
  return mouse_x;
}

int GUI::getMouseYPosition() const {
  return mouse_y;
}

bool GUI::getCloseGUI() {
  return !cont;
}
