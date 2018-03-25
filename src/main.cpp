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
