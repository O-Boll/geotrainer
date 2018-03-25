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
