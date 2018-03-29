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

#include "Sounds.h"

Mix_Chunk* Sounds::click = 0;
Mix_Chunk* Sounds::correct_answer = 0;
Mix_Chunk* Sounds::game_over = 0;
Mix_Chunk* Sounds::tick = 0;
Mix_Chunk* Sounds::wrong_answer = 0;


void Sounds::initSounds() {
  click = Mix_LoadWAV("wav/click.wav");
  correct_answer = Mix_LoadWAV("wav/correct_answer.wav");
  game_over = Mix_LoadWAV("wav/game_over.wav");
  tick = Mix_LoadWAV("wav/tick.wav");
  wrong_answer = Mix_LoadWAV("wav/wrong_answer.wav");
}

void Sounds::exitSounds() {
  Mix_FreeChunk(click);
  Mix_FreeChunk(correct_answer);
  Mix_FreeChunk(game_over);
  Mix_FreeChunk(tick);
  Mix_FreeChunk(wrong_answer);
}

void Sounds::mute() {
  Mix_Volume(-1, 0);
}

void Sounds::unmute() {
  Mix_Volume(-1, 128);
}

bool Sounds::isMuted() {
  if(Mix_Volume(-1, -1) == 0)
    return true;
  return false;
}

void Sounds::haltSound() {
  Mix_HaltChannel(-1);
}

void Sounds::playClickSound() {
  Mix_PlayChannel(-1, click, 0);
}

void Sounds::playCorrectAnswerSound() {
  Mix_PlayChannel(-1, correct_answer, 0);
}

void Sounds::playGameOverSound() {
  //Mix_PlayChannel(-1, game_over, 0);
}

void Sounds::playTickSound() {
  Mix_PlayChannel(-1, tick, 0);
}

void Sounds::playWrongAnswerSound() {
  Mix_PlayChannel(-1, wrong_answer, 0);
}
