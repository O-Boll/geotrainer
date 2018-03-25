#ifndef SOUNDS_H
#define SOUNDS_H

#include <SDL_mixer.h>

class Sounds {

  private:

    static Mix_Chunk* click;
    static Mix_Chunk* correct_answer;
    static Mix_Chunk* game_over;
    static Mix_Chunk* tick;
    static Mix_Chunk* wrong_answer;

  public:

    static void initSounds();
    static void exitSounds();

    static void mute();
    static void unmute();
    static bool isMuted();

    static void haltSound();

    static void playClickSound();
    static void playCorrectAnswerSound();
    static void playGameOverSound();
    static void playTickSound();
    static void playWrongAnswerSound();

};

#endif
