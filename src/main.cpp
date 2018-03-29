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

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "state/ArcadeState.h"
#include "state/EduState.h"
#include "state/MenuState.h"
#include "state/StateFactory.h"
#include "state/TTState.h"

void initSDL() {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_ShowCursor(0);
  TTF_Init();
  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048);
}

void exitSDL() {
  Mix_Quit();
  TTF_Quit();
  SDL_Quit();
}

int main(int argc, char **argv) {
  initSDL();
  GUI::initGUI(320, 180, 3);
  State* s = new MenuState(StateConfig());

  while(s->run()) {
    if(s->changeState()) {
      StateConfig sc = s->getStateConfig();
      delete s;
      s = StateFactory::createState(sc);
    }
    SDL_Delay(0);

    static int i = 0;
    if(i++ % 60 == 0)
       std::cout << s->getFrameRate() << std::endl;

  }
  delete s;
  GUI::exitGUI();
  exitSDL();
  return 0;
}
